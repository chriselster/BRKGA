#include "TSPInstance.hpp"
#include "VectorSelector.cpp"
#include "Constants.hpp"

TSPInstance::TSPInstance()
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
	setTestFolder();
	clients = CsvReader::from_csv<Client>(addFolder(CLIENT_FILE));
	items = CsvReader::from_csv<Item>(addFolder(ITEM_FILE));
	vehicles = CsvReader::from_csv<Vehicle>(addFolder(VEHICLE_FILE));
	carriers = std::vector<Carrier>();
	createCarriers();
	sortEntities();
}

std::string TSPInstance::addFolder(std::string filename)
{
	return testFolder + filename;
}

void TSPInstance::setTestFolder()
{
	std::fstream file;
	file.open("parameters.txt", std::ios::in);
	std::string line;
	std::getline(file, line);
	std::string delimiter = "= ";
	std::string testFolder = line.substr(line.find(delimiter) + delimiter.length());
	this->testFolder = testFolder + "/";
}

void TSPInstance::createCarriers()
{
	for (auto &vehicle : vehicles)
	{
		while (carriers.size() <= vehicle.carrierId)
		{
			carriers.push_back(Carrier(carriers.size()));
		}
		carriers[vehicle.carrierId].addVehicle(&vehicle);
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
	CsvReader reader = CsvReader(addFolder(CLIENTS_PER_CARRIER_FILE));

	for (std::vector<std::string> row : reader.rows)
	{
		int carrierId = std::stoi(row[0]);
		int clientId = std::stoi(row[1]);

		carriers[carrierId].addClient(clientId);
	}
}

void TSPInstance::readAcceptedItemsPerVeichle()
{
	CsvReader reader = CsvReader(addFolder(ITEMS_PER_VEHICLE_FILE));

	for (std::vector<std::string> row : reader.rows)
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
		Client *client = &clients[item.clientId];
		client->addItem(&item);
		item.setDestination(client->getPosition());
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

double TSPInstance::evaluate(std::vector<double> cromossome)
{
	fitness = 0;
	for (int i = 0; i < items.size(); i++)
	{
		attendItem(i, cromossome[i]);
	}
	return fitness;
}

uint TSPInstance::size()
{
	return items.size();
}

void TSPInstance::printStatistics()
{
	for (auto &vehicle : vehicles)
	{
		std::cout << "Vehicle " << vehicle.id << " has " << vehicle.remainingCapacity << " remaining capacity" << std::endl;
	}
	std::cout << std::endl;
	for (auto &item : items)
	{
		if (item.wasAttended())
			std::cout << "\033[1;32mItem " << item.id << " was attended by vehicle " << item.vehicle->id << "\033[0m" << std::endl;
		else
			std::cout << "\033[1;31mItem " << item.id << " was not attended.\033[0m"
					  << " Position: " << item.destination.toString() << std::endl;
	}
}

void TSPInstance::attendItem(int itemId, double vehicleSelector)
{
	std::vector<std::pair<double, Vehicle *>> availableVehicles = getAvailableVehicles(itemId);
	if (availableVehicles.empty())
	{
		fitness += PENALTY;
		return;
	}

	Item *item = &items[itemId];
	VectorSelector selector = VectorSelector(availableVehicles);
	Vehicle *selectedVehicle = selector(vehicleSelector).second;
	fitness += selector(vehicleSelector).first;
	attendItem(item, selectedVehicle);
}

std::vector<std::pair<double, Vehicle *>> TSPInstance::getAvailableVehicles(int itemId)
{
	std::vector<std::pair<double, Vehicle *>> availableVehicles;
	for (auto &carrier : carriers)
	{
		if (carrier.canAttend(&items[itemId]))
		{
			std::priority_queue<std::pair<double, Vehicle *>> vehicles = carrier.getAvailableVehicles(&items[itemId]);
			while (!vehicles.empty())
			{
				availableVehicles.push_back(vehicles.top());
				vehicles.pop();
			}
		}
	}
	sort(availableVehicles.begin(), availableVehicles.end());
	return availableVehicles;
}

void TSPInstance::attendItem(Item *item, Vehicle *vehicle)
{
	Carrier *carrier = &carriers[vehicle->carrierId];
	carrier->attendItem(item, vehicle);
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