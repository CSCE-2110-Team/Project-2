#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Facility.h"
#include <string>
#include <vector>
#include <list>
using namespace std;

class HashTable {
private:
  struct HashNode {
  string key; //Facility ID
  Facility facility;
};

vector<list<HashNode>> table; //lists allow for shared buckets
int capacity;
int entriesCount;
//counts number of facilities
int collisionCount;
//counts how many times new entry was inserted into a bucket that is already used.
int hashFunction(const string& key) const;

public:
  HashTable(int cap = 19);
  bool insert(const Facility& fac);
  bool lookup(const string& id, Facility& foundFac) const;
  //copies mathching facility from ID into foundFac
  int getCapacity() const {return capacity;}
  int getEntriesCount() const {return entriesCount;}
  int getCollisionCount() const {return collisionCount;}
};

#endif
