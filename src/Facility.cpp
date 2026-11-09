#include "Facility.h"
#include "HashTable.h"
#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

void loadFacilities(const string& path, HashTable& hashTable, vector<Facility>& facilities) {
    ifstream inputFile(path);
    if (!inputFile.is_open()) {
        cout << "Error opening facilities file: " << path << endl;
        return;
    }

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;
    string line;
    while (getline(inputFile, line)) {
        lineNumber++;
        int first = static_cast<int>(line.find_first_not_of(" \t\r\n"));
        string record = (first < 0) ? "" : line.substr(first, line.find_last_not_of(" \t\r\n") - first + 1);
        if (record.empty() || record[0] == '#') {//ignores blank lines
            continue;
        }

        vector<string> fields;
        int fieldStart = 0;
        while (true) {
            int delimiter = static_cast<int>(record.find('|', fieldStart));
            if (delimiter < 0) {
                fields.push_back(record.substr(fieldStart));
                break;
            }
            fields.push_back(record.substr(fieldStart, delimiter - fieldStart));
            fieldStart = delimiter + 1;
        }//each record is seperated by a | so by searching for those we can split each record

        if (fields.size() != 4) {
            cout << "Record does not contain the correct number of fields." << lineNumber << endl;
            rejected++;
            continue;
        }//if line is not formatted correctly it is rejected

        vector<string> values;
        for (const string& field : fields) {
            int fieldFirst = static_cast<int>(field.find_first_not_of(" \t\r\n"));
            values.push_back((fieldFirst < 0) ? "" : field.substr(fieldFirst, field.find_last_not_of(" \t\r\n") - fieldFirst + 1));
        }

        string id = values[0];
        for (char& ch : id) {
            ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
        }
        if (id.size() != 4 || id[0] != 'F' || !isdigit(static_cast<unsigned char>(id[1])) || !isdigit(static_cast<unsigned char>(id[2])) || !isdigit(static_cast<unsigned char>(id[3])) || values[1].empty() || values[2].empty() || values[3].empty()) {
            cout << "Invalid Facility ID " << lineNumber << endl;
            rejected++;
            continue;//verifies the facility record ID is formatted correctly
        }

        Facility facility = {id, values[1], values[2], values[3]};
        if (!hashTable.insert(facility)) {
            cout << "Duplicate Facility ID." << lineNumber << endl;
            rejected++;
            continue;
        }

        facilities.push_back(facility);
        accepted++;
    }

    cout << path << ": " << accepted << " accepted, " << rejected << " rejected." << endl;
}
