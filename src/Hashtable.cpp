#include "HashTable.h"
#include <cctype>
using namespace std;

HashTable::HashTable(int cap) : capacity(cap), entriesCount(0), collisionCount(0) {
  table.resize(capacity);
}

int HashTable::hashFunction(const string& key) const {
  int hash = 0;
  for (char ch : key) {
    hash = (hash * 31) + ch; //prevents collisions from IDs that have the same numbers in different order
  }
  return hash % capacity; //makes the bucket index valid
}

bool HashTable::insert(const Facility& fac) {
  string normKey = fac.id;
  for (char& ch : normKey) {
    ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
  }
  int idx = hashFunction(normKey);

  for (const auto& node : table[idx]) {
    if (node.key == normKey) {
      return false; //if it finds a duplicate it is rejected
    }
  }
  if (!table[idx].empty()) {
    //adds to collision count if the bucket is not currently empty, then adds the new ID to the ist of that bucket
    collisionCount++;
  }
  table[idx].push_back(HashNode{normKey, fac});
  entriesCount++;
  return true;
  }

bool HashTable::lookup(const string& id, Facility& foundFac) const {
  int first = static_cast<int>(id.find_first_not_of(" \t\r\n"));
  string normKey = (first < 0) ? "" :
    id.substr(first, id.find_last_not_of(" \t\r\n") - first + 1);//ignores parts of input like whitespace
  for (char& ch : normKey) {
    ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
  }
  int idx = hashFunction(normKey);
  for (const auto& node : table[idx]) {
    if (node.key == normKey) {
      foundFac = node.facility;
      return true;
    }
  }
  return false;
}
    
  

