
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Each department is a node in the tree
struct DepartmentNode {
    string name;
    vector<DepartmentNode*> children;

    DepartmentNode(string departmentName) {
        name = departmentName;
    }
};

class DepartmentTree {
private:
    DepartmentNode* root;

    DepartmentNode* searchHelper(
        DepartmentNode* current,
        string name
    );

    void displayHelper(
        DepartmentNode* current,
        int level
    );

    void preorderHelper(DepartmentNode* current);

public:
    DepartmentTree();

    void loadDepartments(string filename);

    void addDepartment(string parentName, string departmentName);

    bool searchDepartment(string name);

    void displayHierarchy();

    void preorderTraversal();
};

#endif
