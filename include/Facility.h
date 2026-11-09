#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>
using namespace std;
class HashTable;

struct Facility {
  string id;
  string name;
  string building;
  string category;
};

void loadFacilities(const string& path, HashTable& hashTable, vector<Facility>& facilities);
#endif
