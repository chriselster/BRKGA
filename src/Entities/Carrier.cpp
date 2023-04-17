#include "Carrier.hpp"

Carrier::Carrier(std::vector<std::string> values) : id(std::stoi(values[0])),
                                                    minimumCapacity(std::stof(values[1])),
                                                    costPerAdditionalCustomer(std::stof(values[2])),
                                                    deadFreightCost(std::stof(values[3])),
                                                    maxDistanceBetweenClientsFactor(std::stof(values[4]))
{
}

Carrier::Carrier(float minimumCapacity, float costPerAdditionalCustomer, float discountPerCapacityIncrease, float maxDistanceBetweenCustomers) : minimumCapacity(minimumCapacity),
                                                                                                                                                 costPerAdditionalCustomer(costPerAdditionalCustomer),
                                                                                                                                                 deadFreightCost(discountPerCapacityIncrease),
                                                                                                                                                 maxDistanceBetweenClientsFactor(maxDistanceBetweenCustomers)
{
}

Carrier::Carrier()
{
    id = 0;
    minimumCapacity = 0;
    costPerAdditionalCustomer = 0;
    deadFreightCost = 0;
    maxDistanceBetweenClientsFactor = 0;
}

Carrier::~Carrier()
{
}

void Carrier::addClient(int clientId)
{
    clientIds.insert(clientId);
}

void Carrier::addFare(int vehicleType, double fare)
{
    if (farePerVehicleTypePerKm.size() <= vehicleType)
        farePerVehicleTypePerKm.resize(vehicleType + 1, 0.0);
    farePerVehicleTypePerKm[vehicleType] = fare;
}

void Carrier::addVehicle(Vehicle *vehicle)
{
    vehicles.push_back(vehicle);
}

void Carrier::print()
{
    std::cout << "Carrier " << id << " with " << clientIds.size() << " clients" << std::endl;
    std::cout << std::endl;
    std::cout << "Clients: " << std::endl;
    for (auto &client : clientIds)
    {
        std::cout << client << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Vehicles: " << std::endl;

    for (auto &vehicle : vehicles)
    {
        vehicle->print();
    }
}

bool Carrier::canAttend(Item *item)
{
    if (clientIds.find(item->clientId) == clientIds.end())
        return false;
    for (auto &vehicle : vehicles)
    {
        if (vehicle->canTake(item))
            return true;
    }
    return false;
}

std::priority_queue<std::pair<double, Vehicle *>> Carrier::getAvailableVehicles(Item *item)
{
    std::priority_queue<std::pair<double, Vehicle *>> availableVehicles;
    for (auto &vehicle : vehicles)
    {
        if (vehicle->canTake(item))
        {
            availableVehicles.push(std::make_pair(calculateTripCostDelta(item, vehicle), vehicle));
        }
    }
    return availableVehicles;
}

double Carrier::calculateTripCostDelta(Item *item, Vehicle *vehicle)
{
    double cost = 0;
    bool paidDeadFreight = vehicle->usedCapacity() != 0 && vehicle->usedCapacity() < minimumCapacity;
    if (paidDeadFreight && vehicle->usedCapacity() + item->weight >= minimumCapacity)
    {
        cost -= deadFreightCost;
    }
    if (vehicle->alreadyVisited(item->clientId))
    {
        return cost;
    }
    // TODO: recalcular rota
    if (proximityClients.find(item->clientId) != proximityClients.end())
    {
        cost += costPerAdditionalCustomer;
    }

    double distance = item->distanceTo(&position);
    cost += distance * vehicle->costPerKm;
    return cost;
}

void Carrier::attendItem(Item *item, Vehicle *vehicle)
{
    vehicle->take(item);
}

void Carrier::addProximityClient(int clientId, Vehicle *vehicle)
{
    clientIds.insert(clientId);
    proximityClients[clientId].push_back(vehicle);
}

void Carrier::reset()
{
    for (auto &vehicle : vehicles)
    {
        vehicle->reset();
    }
    proximityClients.clear();
}