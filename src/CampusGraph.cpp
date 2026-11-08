#include "CampusGraph.h"

CampusGraph::~CampusGraph() {
    // free linked list up and stuff.
}

BuildingNode* CampusGraph::getBuilding(const std::string& buildingName) const {
    for (BuildingNode* b : CampusBuildings) {
        if (b->buildingName == buildingName) return b;
    }
    return nullptr;
}

bool CampusGraph::addBuilding(const std::string& buildingName) {
    return false; //placeholder
}

bool CampusGraph::addPath(BuildingNode* from, BuildingNode* to) {
    return false; //placeholder
}
