#include "CampusGraph.h"
#include <iostream>
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
    //placeholder
}
