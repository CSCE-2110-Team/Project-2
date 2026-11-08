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
    //Stop if they're the same node; return false.
    if (from == to) return false;
    
    //if either doesn't exist in the graph, don't add a path to either; return false.
    if not (hasBuilding(from) and hasBuilding(to)) return false;
    
    //Check if they're already pathed to eachother. Don't double up; return false.
    //Note: if I was being thorough, I'd check both and not just from's adjacencies. But that scenario shouldn't occur.
    BuildingNode* currentNode = from->next;
    while (currentNode != nullptr){
        if (currentNode->buildingName == to->buildingName) return false;
        currentNode = currentNode->next;
    }
    
    //Create new buildingNode for 'to' named after 'from'
    BuildingNode* fromNode = new BuildingNode;
    fromNode->buildingName = from->buildingName;
    
    //Create new buildingNode for 'from' named after 'to'
    BuildingNode* toNode = new BuildingNode;
    toNode->buildingName = to->buildingName;
    
    //Go to end of from's linked list and append toNode.
    currentNode = from;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = toNode;
    
    //Go to end of to's linked list and append fromNode.
    currentNode = to;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = fromNode;
    
    //Successful; return true.
    return true;
}

