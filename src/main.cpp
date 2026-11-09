#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "Facility.h"
#include "HashTable.h"
#include "CampusGraph.h"
#include "department.h"
using namespace std;

int main(int argc, char* argv[]) {
  int selection = -1;
  HashTable hashTable(19);
    vector<Facility> facilities;
    loadFacilities("data/facilities.txt", hashTable, facilities);

  string directory = "data/";
  if (argc >= 2) directory = argv[1];
  if (not directory.empty() and directory.back() != '/') directory += '/'; //Guard against a / not being included. 

  CampusGraph graph;
  graph.loadBuildings(directory);
  graph.loadConnections(directory);

  DepartmentTree departmentTree;
  departmentTree.loadDepartments("departments.txt"); //This needs to be reworked to accept a data/ input.
    
  while (selection != 0) {
    cout << "===== Smart Campus Navigation and Facility Analytics System =====" << endl;
    cout << endl;
    cout << "1. View all Facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" << endl;
    cout << "4. Display graph counts and degrees" << endl;
    cout << "5. Find reachable buildings (BFS)" << endl;
    cout << "6. Add department" << endl;
    cout << "7. Search department" << endl;
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "0. Exit" << endl;

    cout << "Enter choice: ";
    
    string line;
    if (not getline(cin, line)) break;
    try {selection = stoi(line);}
    catch(...) {selection = -1;}
    
    cout << endl;
    if (selection == 1) {
      if (facilities.empty()) {
        cout << "Please load facilities" << endl;
      } 
      else {
        for (const Facility& facility : facilities) {
          cout << facility.id << " | " << facility.name << " | " << facility.building << " | " << facility.category << endl;
        }
              cout << "Total facilities: " << facilities.size() << endl;
      }
    }
    else if (selection == 2) {
      cout << "Enter facility ID: ";
        string id;
        getline(cin, id);

        int first = static_cast<int>(id.find_first_not_of(" \t\r\n"));
        if (first < 0) {
          cout << "Facility ID can not be blank." << endl;
            continue;
        }
        id = id.substr(first, id.find_last_not_of(" \t\r\n") - first + 1);
        for (char& ch : id) {
          ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
        }

        if (id.size() != 4 || id[0] != 'F' || !isdigit(static_cast<unsigned char>(id[1])) || !isdigit(static_cast<unsigned char>(id[2])) || !isdigit(static_cast<unsigned char>(id[3]))) {
          cout << "Invalid ID." << endl;
          continue;
        }

        Facility match;
        if (hashTable.lookup(id, match)) {
          cout << "Found: " << match.name << " | " << match.building << " | " << match.category << '\n';
        } 
        else {
          cout << "No facility found with ID " << id << "Please try again" << endl;
        }
    }
    else if (selection == 3) {
      graph.displayGraph();
    }
    else if (selection == 4) {
      graph.displayCounts();
    }
    else if (selection == 5) {
      graph.displayReachable();
    }
    else if (selection == 6) {
      string parent, department;

      cout << "Enter parent department: ";
      cin.ignore();
      getline(cin, parent);

      cout << "Enter new department name: ";
      getline(cin, department);

      departmentTree.addDepartment(parent, department);
    }

    else if (selection == 7) {
      string name;

      cout << "Enter department name to search: ";
      cin.ignore();
      getline(cin, name);

      departmentTree.searchDepartment(name);
    }

    else if (selection == 8) {
      departmentTree.displayHierarchy();
    }

    else if (selection == 9) {
      departmentTree.preorderTraversal();
    }
    else if (selection == 0) {
      cout << "Exiting... " << endl;
    }
    else {
      cout << "Please make a valid selection" << endl;
    }
  }
  
  return 0;
}
