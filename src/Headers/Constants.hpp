#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>

std::string ITEM_FILE = "items.csv";
std::string CLIENT_FILE = "clients.csv";
std::string VEHICLE_FILE = "vehicles.csv";
std::string CLIENTS_PER_CARRIER_FILE = "clients_per_carrier.csv";
std::string ITEMS_PER_VEHICLE_FILE = "items_per_vehicle.csv";

const int ONLY_VEHIICLES = 0;
const int ONLY_iTEMS = 1;
const int BOTH = 2;

#endif // __CONSTANTS_H__