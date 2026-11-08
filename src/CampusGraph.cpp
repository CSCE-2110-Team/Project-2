#include "CampusGraph.h"
#include <cctype>

CampusGraph::~CampusGraph() {
    //Loop through all buildingNodes and delete them.
    for (BuildingNode* b : CampusBuildings) delete b;
}

//helper function to normalize strings.
static std::string normalize(const std::string& str) {
    //Get the first and last chars that aren't whitespace.
    std::size_t firstChar = str.find_first_not_of(" \t\n\r\f\v");
    std::size_t lastChar = str.find_last_not_of(" \t\n\r\f\v");

    //If either doesn't return a position, return an empty string.
    if (firstChar == std::string::npos or lastChar == std::string::npos) return "";    
    
    //trim the string from the first Char for lastChar-firstChar+1 chars. (difference in position, +1 to include last char.)
    std::string trimmed = str.substr(firstChar, lastChar-firstChar+1);

    //Loop through characters
    for (char &c : trimmed){
        c = std::tolower(static_cast<unsigned char>(c));
    }

    //String is normalized; return it.
    return trimmed;
}

BuildingNode* CampusGraph::getBuilding(const std::string& buildingName) const {
    //normalize name.
    const std::string& normalizedName = normalize(buildingName);
    //loop through all buildingNodes.
    for (BuildingNode* b : CampusBuildings) {
        //We found it; return it.
        if (b->buildingName == normalizedName) return b;
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
    //normalize name.
    const std::string& normalizedName = normalize(buildingName);
    
    //if it already exists, don't add it again. failed addition; return false.
    //Note: this causes a double normalization of the name. Which doesn't cause problems but is unneccessary.
    if (getBuilding(buildingName) != nullptr) return false;
    
    //create new buildingNode from name.
    BuildingNode* newBuilding = new BuildingNode;
    newBuilding->buildingName = normalizedName;
    
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
