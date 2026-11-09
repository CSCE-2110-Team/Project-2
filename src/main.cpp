#include <iostream>
#include "CampusGraph.h"
using namespace std;

int main() {
  int selection = 0;
  CampusGraph graph;

  cout << "Input data directory (Type nothing to default to data/): ";
  string directory;
  if (not getline(cin, directory)) directory = "data/";
  if (directory.empty()) directory = "data/"; 
  graph.loadBuildings(directory);
  graph.loadConnections(directory);

  while (selection != 10) {
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

    }
    else if (selection == 2) {

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

    }
    else if (selection == 7) {

    }
    else if (selection == 8) {

    }
    else if (selection == 9) {

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
