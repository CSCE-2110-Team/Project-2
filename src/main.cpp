#include <iostream>
#include "Department.h"
using namespace std;

int main() {
  int selection = 0;
DepartmentTree departmentTree;

departmentTree.loadDepartments("departments.txt");
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
    cout << "10. Exit" << endl;

    cout << "Enter choice: ";
    cin >> selection;
    cout << endl;
    if (selection == 1) {

    }
    else if (selection == 2) {

    }
    else if (selection == 3) {

    }
    else if (selection == 4) {

    }
    else if (selection == 5) {

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
    else if (selection == 10) {
      cout << "Exiting... " << endl
    }
    else {
      cout << "Please make a valid selection" << endl;
    }
  }
  
  return 0;
}
