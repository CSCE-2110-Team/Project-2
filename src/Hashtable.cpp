#include "HashTable.h"
#include <cctype>
using namespace std;

HashTable::HashTable(int cap) : capacity(cap), entriesCount(0), collisionCount(0) {
  table.resize(capacity);
}

int HashTable::hashFunction(const string& key) const {
  int hash = 0;
  for (char ch : key) {
    hash = (hash * 31) + ch //prevents collisions from IDs that have the same numbers in different order
  }
  return hash % capacity; //makes the bucket index valid
  
