#include "TSPInstance.hpp"

TSPInstance::TSPInstance(RunArguments &_args) : args(_args)
{
	carriers = std::vector<Carrier>();
}

TSPInstance::~TSPInstance()
{
}

void TSPInstance::setUp()
{
	readEntities();
	readAcceptedClientsPerCarrier();
	readAcceptedItemsPerVeichle();
	addItemsToClients();
}

void TSPInstance::readEntities()
{

	clients = CsvReader::from_csv<Client>(addFolder(CLIENT_FILE));
	items = CsvReader::from_csv<Item>(addFolder(ITEM_FILE));
	vehicles = CsvReader::from_csv<Vehicle>(addFolder(VEHICLE_FILE));
	carriers = std::vector<Carrier>();
	sortEntities();
	createCarriers();
}

std::string TSPInstance::addFolder(std::string filename)
{
	return args.input_file_location + filename;
}

std::string TSPInstance::parseLine(std::fstream &file)
{
	std::string line;
	std::getline(file, line);
	std::string delimiter = "= ";
	std::string parsed = line.substr(line.find(delimiter) + delimiter.length());
	return parsed;
}

void TSPInstance::createCarriers()
{
	for (Vehicle &vehicle : vehicles)
	{
		while (carriers.size() <= vehicle.carrierId)
		{
			carriers.push_back(Carrier(carriers.size()));
		}
		carriers[vehicle.carrierId].addVehicle(&vehicle);
	}
}

void TSPInstance::updateCarrierPointers()
{
	for (Vehicle &vehicle : vehicles)
	{
		carriers[vehicle.carrierId].updatePointer(&vehicle);
	}
}

void TSPInstance::sortEntities()
{
	std::sort(carriers.begin(), carriers.end(), [](Carrier &a, Carrier &b)
			  { return a.id < b.id; });
	std::sort(clients.begin(), clients.end(), [](Client &a, Client &b)
			  { return a.id < b.id; });
	std::sort(items.begin(), items.end(), [](Item &a, Item &b)
			  { return a.id < b.id; });
	std::sort(vehicles.begin(), vehicles.end(), [](Vehicle &a, Vehicle &b)
			  { return a.id < b.id; });
}

void TSPInstance::readAcceptedClientsPerCarrier()
{
	for (std::vector<std::string> row : CsvReader(addFolder(CLIENTS_PER_CARRIER_FILE)).rows)
	{
		int carrierId = std::stoi(row[0]);
		int clientId = std::stoi(row[1]);

		carriers[carrierId].addClient(clientId);
	}
}

void TSPInstance::readAcceptedItemsPerVeichle()
{
	for (std::vector<std::string> row : CsvReader(addFolder(ITEMS_PER_VEHICLE_FILE)).rows)
	{
		int vehicleType = std::stoi(row[0]);
		int itemType = std::stoi(row[1]);

		for (auto &vehicle : vehicles)
		{
			if (vehicle.type == vehicleType)
			{
				vehicle.addAcceptedItem(itemType);
			}
		}
	}
}

void TSPInstance::addItemsToClients()
{
	for (auto &item : items)
	{
		Client client = clients[item.clientId];
		client.addItem(&item);
		item.setDestination(client.getPosition());
	}
}

void TSPInstance::print()
{
	for (auto &carrier : carriers)
	{
		carrier.print();
	}

	for (auto &client : clients)
	{
		client.print();
	}
}

long double TSPInstance::evaluate(std::vector<long double> cromossome)
{
	fitness = 0;
	updateCarrierPointers();
	reset();
	if (args.decoderType == ONLY_VEHIICLES)
	{
		for (int i = 0; i < items.size(); i++)
		{
			attendItem(i, cromossome[i]);
		}
	}
	else if (args.decoderType == ONLY_ITEMS)
	{
		for (int i = 0; i < items.size(); i++)
		{
			std::vector<Item *> unnatended = unnatendedItems();
			VectorSelector<Item *> selector = VectorSelector<Item *>(unnatended);
			attendItem(selector(cromossome[i])->id, 0);
		}
	}
	else
	{
		for (int i = 0; i < items.size(); i++)
		{
			std::vector<Item *> unnatended = unnatendedItems();
			VectorSelector<Item *> selector = VectorSelector<Item *>(unnatended);
			attendItem(selector(cromossome[i])->id, cromossome[i + items.size()]);
		}
	}
	return fitness;
}

std::vector<Item *> TSPInstance::unnatendedItems()
{
	std::vector<Item *> unnatendedItems;
	for (auto &item : items)
	{
		if (!item.wasAttended())
		{
			unnatendedItems.push_back(&item);
		}
	}
	return unnatendedItems;
}

unsigned int TSPInstance::size()
{
	return items.size();
}

void TSPInstance::printStatistics(std::fstream &file)
{
	long double totoalCost = 0;
	for (auto &vehicle : vehicles)
	{
		long double tripCost = vehicle.tripCost();
		file << "Vehicle " << vehicle.id << " has " << vehicle.remainingCapacity << " remaining capacity" << std::endl;
		file << "\tTrip cost: " << tripCost << std::endl
			 << std::endl;
		totoalCost += tripCost;
	}

	file << "Total cost: " << totoalCost << std::endl
		 << std::endl;

	for (auto &item : items)
	{
		if (item.wasAttended())
			file << "Item " << item.id << " was attended by vehicle " << item.vehicle->id << std::endl;
		else
			file << "Item " << item.id << " was not attended."
				 << " Position: " << item.destination.toString() << std::endl;
	}
}

void TSPInstance::attendItem(int itemId, long double vehicleSelector)
{
	std::vector<std::pair<long double, Vehicle *>> availableVehicles = getAvailableVehicles(itemId);
	if (availableVehicles.empty())
	{
		fitness += PENALTY;
		return;
	}

	VectorSelector<std::pair<long double, Vehicle *>> selector = VectorSelector<std::pair<long double, Vehicle *>>(availableVehicles);
	std::pair<long double, Vehicle *> selection = selector(vehicleSelector);

	Vehicle *selectedVehicle = selection.second;
	fitness += selection.first;

	Item *item = &items[itemId];
	selectedVehicle->take(item);
}

std::vector<std::pair<long double, Vehicle *>> TSPInstance::getAvailableVehicles(int itemId)
{
	std::vector<std::pair<long double, Vehicle *>> availableVehicles;
	for (auto &carrier : carriers)
	{
		if (carrier.canAttend(&items[itemId]))
		{
			std::priority_queue<std::pair<long double, Vehicle *>> availableVehiclesInCarrier = carrier.getAvailableVehicles(&items[itemId]);
			while (!availableVehiclesInCarrier.empty())
			{
				availableVehicles.push_back(availableVehiclesInCarrier.top());
				availableVehiclesInCarrier.pop();
			}
		}
	}
	sort(availableVehicles.begin(), availableVehicles.end());
	return availableVehicles;
}

void TSPInstance::reset()
{
	fitness = 0;
	for (auto &carrier : carriers)
	{
		carrier.reset();
	}
	for (auto &item : items)
	{
		item.reset();
	}
}

void TSPInstance::validate()
{
	bool valid = true;
	for (auto &item : items)
	{
		if (!item.wasAttended())
		{
			valid = false;
			std::cout << "Item " << item.id << " was not attended." << std::endl;
		}
	}
	for (auto &vehicle : vehicles)
	{
		if (vehicle.remainingCapacity < 0)
		{
			valid = false;
			std::cout << "Vehicle " << vehicle.id << " has " << vehicle.remainingCapacity << " remaining capacity" << std::endl;
		}
		if (!vehicle.canVisitAllClients())
		{
			valid = false;
			std::cout << "Vehicle " << vehicle.id << " can't visit all clients" << std::endl;
		}
		if (vehicle.hasIncorrectPoints())
		{
			valid = false;
			std::cout << "Vehicle " << vehicle.id << " has incorrect points" << std::endl;
		}
	}
	if (valid)
	{
		std::cout << "Solution is valid" << std::endl;
	}
	else
	{
		std::cout << "Solution is not valid" << std::endl;
	}
}

void TSPInstance::loadSolution(std::string solutionFile)
{
	std::vector<std::vector<int>> rows = read_csv<int>(solutionFile, false);

	for (std::vector<int> row : rows)
	{
		int itemId = row[0];
		int vehicleId = row[1];

		Item *item = &items[itemId];
		Vehicle *vehicle = &vehicles[vehicleId];
		vehicle->take(item);
	}
}