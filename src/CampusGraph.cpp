/*

@file CampusGraph.cpp
@brief Source file for the CampusGraph class. Handles Buildings, their connections, and searching through them.
@author Wesley Jackson

 */

#include "CampusGraph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cctype>

CampusGraph::~CampusGraph() {
    //Loop through all buildingNodes and delete them.
    for (BuildingNode* b : CampusBuildings) delete b;
}

//helper functions to normalize strings.
std::string trimstr(const std::string& str) {
    //Get the first and last chars that aren't whitespace.
    std::size_t firstChar = str.find_first_not_of(" \t\n\r\f\v");
    std::size_t lastChar = str.find_last_not_of(" \t\n\r\f\v");

    //If either doesn't return a position, return an empty string.
    if (firstChar == std::string::npos or lastChar == std::string::npos) return "";    
    
    std::size_t length = lastChar-firstChar+1; //(difference in position, +1 to include last char.)
    
    //return substring of length, starting at firstChar
    return str.substr(firstChar, length);
}
    
std::string lowerstr(std::string str) {
    //Loop through characters
    for (char &c : str){
        c = std::tolower(static_cast<unsigned char>(c));
    }

    //String is lowercase; return it.
    return str;
}

BuildingNode* CampusGraph::getBuilding(const std::string& buildingName) const {
    //normalize name.
    const std::string normalizedName = trimstr(lowerstr(buildingName));
    //loop through all buildingNodes.
    for (BuildingNode* b : CampusBuildings) {
        //We found it; return it.
        if (lowerstr(b->buildingName) == normalizedName) return b;
    }
    //We didn't find it; return nullptr.
    return nullptr;
}

//This function was mostly copied from the one above.
bool CampusGraph::hasBuilding(const BuildingNode* nodeInQuestion) const {
    //loop through all buildingNodes directly in the vector.
    for (BuildingNode* b : CampusBuildings) {
        //We found it; return true.
        if (b == nodeInQuestion) return true;
    }
    //We didn't find it; return false.
    return false;
}

bool CampusGraph::addBuilding(const std::string& buildingName) {
    //trim name.
    const std::string trimmedName = trimstr(buildingName);
    
    //if it's a blank string; return false.
    if (trimmedName.empty()) return false;
    
    //if it already exists, don't add it again. failed addition; return false.
    //Note: this causes a double trimming of the name. Which doesn't cause problems but is unneccessary.
    if (getBuilding(buildingName) != nullptr) return false;
    
    //create new buildingNode from name.
    BuildingNode* newBuilding = new BuildingNode;
    newBuilding->buildingName = trimmedName;
    
    //push into vector. successful addition; return true.
    CampusBuildings.push_back(newBuilding);
    return true;
}

bool CampusGraph::addPath(BuildingNode* from, BuildingNode* to) {
    //Stop if they're the same node; return false.
    if (from == to) return false;
    
    //if either doesn't exist in the graph, don't add a path to either; return false.
    if (not (hasBuilding(from) and hasBuilding(to))) return false;
    
    //Make sure 'to' isn't already a neighbor of 'from'
    //NOTE: if I were being thorough, i'd also check 'from' isn't a neighbor of 'to'. But that shouldn't happen anyway.
    for(BuildingNode* b : from->neighbors){
        if (b == to) return false;
    }
    
    //Make 'from' and 'to' neighbors.
    from->neighbors.push_back(to);
    to->neighbors.push_back(from);
    
    //Successful; return true.
    return true;
}

void CampusGraph::displayGraph() const {
    //Make sure we actually have a graph to display.
    if (CampusBuildings.empty()) {
        std::cout << "(no buildings)" << std::endl;
        return;
    }
    
    for (BuildingNode* b : CampusBuildings) {
        std::cout << b->buildingName << std::endl;
        
        //Make sure the buildingNode has connections to display.
        if (b->neighbors.empty()) {
            std::cout << "- (no connections)" << std::endl;
            continue;
        }
        
        //Print every connected building.
        for (BuildingNode* n : b->neighbors) std::cout << "- " << n->buildingName << std::endl;
    }
}

void CampusGraph::displayCounts() const {
    //Make sure we actually have a graph to display.
    if (CampusBuildings.empty()) {
        std::cout << "(no buildings)" << std::endl;
        return;
    }
    
    //Print size of array with the buildings. Duh.
    std::cout << "Total Buildings: " << CampusBuildings.size() << std::endl; 
    
    //Get degree of every buildingNode and the sum at the same time.
    std::size_t degreeSum = 0;
    std::vector<std::pair<BuildingNode*, std::size_t>> buildingDegrees;
    for (BuildingNode* b : CampusBuildings) {
        std::size_t bDegree = b->neighbors.size();
        buildingDegrees.push_back({b, bDegree});
        degreeSum += bDegree;
    }
    
    //For any undirected graph, the amount of connections is the sum of all degrees divided by two.
    std::cout << "Total Connections: " << degreeSum/2 << std::endl;
    
    //Print all of the degrees we stored earilier while getting a sum. If we printed this first we wouldn't have to store it but this is prettier.
    for (const std::pair<BuildingNode*, std::size_t>& bd : buildingDegrees)
    {
        std::cout << bd.first->buildingName << " | Degree: " << bd.second << std::endl;
    }
}

void CampusGraph::displayReachable() const {
    //Build queue and visited. Pair is node, distance.
    std::queue<std::pair<BuildingNode*, int>> visitQueue;
    std::vector<std::pair<BuildingNode*, int>> distances;
    
    //Get user input.
    std::cout << "Input starting building name: ";
    std::string name;
    std::getline(std::cin, name);
    name = trimstr(name);
    
    //Validating that the user isn't mute.
    if (name.empty()) {
        std::cout << "Invalid name (No name given)" << std::endl;
        return;
    }
    
    //Validating that the user isn't crazy and the node exists.
    BuildingNode* start = getBuilding(name);
    if (start == nullptr) {
        std::cout << "Invalid name (Building Name does not exist)" << std::endl;
        return;
    }
    
    //Establish the first node in the queue.
    std::pair<BuildingNode*, int> startPair = {start,0};
    distances.push_back(startPair);
    visitQueue.push(startPair);
    
    //Go thorugh queue until it's empty.
    while (not visitQueue.empty()) {
        std::pair<BuildingNode*, int>& currentPair = visitQueue.front();
        
        //loop through all of the neighbors of the current node in question.
        for (BuildingNode* b : currentPair.first->neighbors) {
            bool valid = true;
            
            //If it's already in the distance vector, it's already been seen, pass it over.
            for (std::pair<BuildingNode*, int>& bd : distances) {
                if (bd.first == b) {
                    valid = false;
                    break;
                }
            }
            if (not valid) continue;
            
            //This is a new node, add it to the queue, and record the distance.
            std::pair<BuildingNode*, int> newQueue = {b,currentPair.second + 1};
            distances.push_back(newQueue);
            visitQueue.push(newQueue);
        }
        visitQueue.pop();
    }
    
    //Report back to the user like the good script we are.
    std::cout << "Reachable buildings from " << start->buildingName << std::endl;
    for (std::pair<BuildingNode*, int>& bd : distances) {
        std::cout << bd.first->buildingName << " (distance " << bd.second << ")" << std::endl;
    }
    std::cout << "Reachable: " << distances.size() << " of " << CampusBuildings.size() << " buildings" << std::endl; 
}

void CampusGraph::loadBuildings(const std::string& directory) {
    //Open the file.
    const std::string path = directory + "/buildings.txt";
    std::ifstream file(path);
    
    //Are you sure it's open?
    bool fileloaded = file.is_open();
    if (not fileloaded) {
        std::cout << "Error: Couldn't open " << path << std::endl;
    }
    
    //Read through every line in the file, accepting or rejecting buildings.
    int accepted = 0;
    int rejected = 0;
    int lineNum = 0;
    std::string line;
    //Unloaded files are banished to the future.
    if (not fileloaded) goto afterWhile;
    while (std::getline(file, line)) {
        lineNum++;
        line = trimstr(line);
        
        //Skip blank lines and comments.
        if (line.empty() or line[0] == '#') continue;
        
        //Buildings should be a SINGLE entry. not something like Library|Gym
        if (line.find('|') != std::string::npos) {
            std::cout << "Warning: invalid field count from " << path << " on line " << lineNum << ". Offending line: \"" << line << "\"" << std::endl;
            rejected++;
            continue;
        }
        
        //addBuilding decides if its accepted or rejected here. Pretty much only rejects duplicates.
        if (addBuilding(line)) {
            accepted++;
        } else {
            rejected++;
            std::cout << "Warning: duplicate building from " << path << " on line " << lineNum << ". Duplicate building: \"" << line << "\"" << std::endl;
        }
    }
    //Rejoice, the future is here. Unloaded files are back.
    afterWhile:
    std::cout << path << " loaded. Accepted: " << accepted << ", rejected: " << rejected << "." << std::endl;
}

void CampusGraph::loadConnections(const std::string& directory) {
    //Open the file.
    const std::string path = directory + "/connections.txt";
    std::ifstream file(path);
    
    //Are you sure it's open?
    bool fileloaded = file.is_open();
    if (not fileloaded) {
        std::cout << "Error: Couldn't open " << path << std::endl;
    }
    
    //Read through every line in the file, accepting or rejecting buildings.
    int accepted = 0;
    int rejected = 0;
    int lineNum = 0;
    std::string line;
    //Unloaded files are banished to the future.
    if (not fileloaded) goto afterWhile;
    while (std::getline(file, line)) {
        lineNum++;
        line = trimstr(line);
        
        //Skip blank lines and comments.
        if (line.empty() or line[0] == '#') continue;
        
        //Get bar position
        std::size_t bar = line.find('|');
        
        //Connections should be a TWO entries. Something like Library|Gym.
        //If find and rfind don't agree, there's more than one bar. Kill it with hammers.
        if (bar == std::string::npos or bar != line.rfind('|')) {
            std::cout << "Warning: invalid field count from " << path << " on line " << lineNum << ". Offending line: \"" << line << "\"" << std::endl;
            rejected++;
            continue;
        }
        
        //split into two names.
        const std::string fromName = line.substr(0, bar);
        const std::string toName = line.substr(bar + 1);
        
        //get appropriate nodes
        BuildingNode* from = getBuilding(fromName);
        BuildingNode* to = getBuilding(toName);
        
        if (from == nullptr) {
            rejected++;
            std::cout << "Warning: Invalid 'from' building from " << path << " on line " << lineNum << ". Invalid building: \"" << fromName << "\"" << std::endl;
            continue;
        } else if (to == nullptr) {
            rejected++;
            std::cout << "Warning: Invalid 'to' building from " << path << " on line " << lineNum << ". Invalid building: \"" << toName << "\"" << std::endl;
            continue;
        } else if (from == to) {
            rejected++;
            std::cout << "Warning: self connection from " << path << " on line " << lineNum << ". Offending line: \"" << line << "\"" << std::endl;
            continue;
        }
        
        //addPath decides if its accepted or rejected here. Pretty much only rejects duplicates.
        if (addPath(from, to)) {
            accepted++;
        } else {
            rejected++;
            std::cout << "Warning: duplicate path from " << path << " on line " << lineNum << ". Duplicate path: \"" << line << "\"" << std::endl;
        }
    }
    //Rejoice, the future is here. Unloaded files are back.
    afterWhile:
    std::cout << path << " loaded. Accepted: " << accepted << ", rejected: " << rejected << "." << std::endl;
}
