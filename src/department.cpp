
#include "department.h"
#include <fstream>

// Constructor
DepartmentTree::DepartmentTree() {
    root = new DepartmentNode("University");
}

// Search helper (recursive)
DepartmentNode* DepartmentTree::searchHelper(
    DepartmentNode* current,
    string name
) {
    if (current == nullptr) {
        return nullptr;
    }

    if (current->name == name) {
        return current;
    }

    for (DepartmentNode* child : current->children) {
        DepartmentNode* result = searchHelper(child, name);

        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

// Load departments from file
void DepartmentTree::loadDepartments(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string parentName;
    string departmentName;

    while (getline(file, parentName, '|') &&
           getline(file, departmentName)) {

        DepartmentNode* parent = searchHelper(root, parentName);

        if (parent == nullptr) {
            cout << "Parent department not found: "
                 << parentName << endl;
            continue;
        }

        parent->children.push_back(
            new DepartmentNode(departmentName)
        );
    }

    file.close();

    cout << "Departments loaded successfully!" << endl;
}

// Add a department
void DepartmentTree::addDepartment(
    string parentName,
    string departmentName
) {
    DepartmentNode* parent = searchHelper(root, parentName);

    if (parent == nullptr) {
        cout << "Parent department not found." << endl;
        return;
    }

    if (searchHelper(root, departmentName) != nullptr) {
        cout << "Department already exists." << endl;
        return;
    }

    parent->children.push_back(
        new DepartmentNode(departmentName)
    );

    cout << "Department added successfully!" << endl;
}

// Search for a department
bool DepartmentTree::searchDepartment(string name) {
    DepartmentNode* result = searchHelper(root, name);

    if (result != nullptr) {
        cout << "Department found: " << result->name << endl;
        return true;
    }

    cout << "Department not found." << endl;
    return false;
}

// Display hierarchy helper
void DepartmentTree::displayHelper(
    DepartmentNode* current,
    int level
) {
    if (current == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        cout << "  ";
    }

    cout << current->name << endl;

    for (DepartmentNode* child : current->children) {
        displayHelper(child, level + 1);
    }
}

// Display department hierarchy
void DepartmentTree::displayHierarchy() {
    displayHelper(root, 0);
}

// Preorder traversal helper
void DepartmentTree::preorderHelper(DepartmentNode* current) {
    if (current == nullptr) {
        return;
    }

    cout << current->name << endl;

    for (DepartmentNode* child : current->children) {
        preorderHelper(child);
    }
}

// Run preorder traversal
void DepartmentTree::preorderTraversal() {
    cout << "Preorder Traversal:" << endl;
    preorderHelper(root);
}
