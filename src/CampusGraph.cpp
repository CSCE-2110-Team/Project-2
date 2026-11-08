#include "CampusGraph.h"

CampusGraph::~CampusGraph() {
    // free linked list up and stuff.
}

BuildingNode* CampusGraph::getBuilding(const std::string& buildingName) const {
    //loop through all buildingNodes.
    for (BuildingNode* b : CampusBuildings) {
        //We found it; return it.
        if (b->buildingName == buildingName) return b;
    }
    //We didn't find it; return nullptr.
    return nullptr;
}

bool CampusGraph::addBuilding(const std::string& buildingName) {
    //if it already exists, don't add it again. failed addition; return false.
    if (getBuilding(buildingName) != nullptr) return false;
    
    //create new buildingNode from name.
    BuildingNode* newBuilding = new BuildingNode;
    newBuilding->buildingName = buildingName;
    
    //push into vector. successful addition; return true.
    CampusBuildings.push_back(newBuilding);
    return true;
}
bool CampusGraph::addPath(BuildingNode* from, BuildingNode* to) {
    return false; //placeholder
}
