#include "TSPInstance.hpp"

TSPInstance::TSPInstance()
{
}

TSPInstance::~TSPInstance()
{
}

void TSPInstance::setUp()
{
	readEntities();
	readAcceptedClientsPerCarrier();
	readAcceptedItemsPerVeichle();
	readFaresPerCarrier();
	addVehiclesToCarriers();
	addItemsToClients();
}

void TSPInstance::readEntities()
{
	carriers = CsvReader::from_csv<Carrier>("carriers.csv");
	clients = CsvReader::from_csv<Client>("clients.csv");
	items = CsvReader::from_csv<Item>("items.csv");
	vehicles = CsvReader::from_csv<Vehicle>("vehicles.csv");

	// sort all
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
	CsvReader reader = CsvReader("clients_per_carrier.csv");

	for (std::vector<std::string> row : reader.rows)
	{
		int carrierId = std::stoi(row[0]);
		int clientId = std::stoi(row[1]);

		carriers[carrierId - 1].addClient(&clients[clientId - 1]);
	}
}

void TSPInstance::readAcceptedItemsPerVeichle()
{
	CsvReader reader = CsvReader("items_per_vehicle.csv");

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

void TSPInstance::readFaresPerCarrier()
{
	CsvReader reader = CsvReader("fares.csv");

	for (std::vector<std::string> row : reader.rows)
	{
		int vehicleType = std::stoi(row[0]);
		double fare = std::stod(row[1]);
		int carrierId = std::stoi(row[2]);

		carriers[carrierId - 1].addFare(vehicleType, fare);
	}
}

void TSPInstance::addVehiclesToCarriers()
{
	for (auto &vehicle : vehicles)
	{
		carriers[vehicle.carrierId - 1].addVehicle(&vehicle);
	}
}

void TSPInstance::addItemsToClients()
{
	for (auto &item : items)
	{
		clients[item.clientId - 1].addItem(&item);
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

uint TSPInstance::evaluate(std::vector<int> cromossome)
{
	return 1;
}

uint TSPInstance::size()
{
	return items.size();
}

void TSPInstance::printStatistics() {}