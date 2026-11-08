#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

//struct to organize buildings and their next node. Used for linked list / adjacency list.
struct BuildingNode {
    std::string buildingName = "";
    BuildingNode* next = nullptr;
};

class CampusGraph {
private:
    //Memory, stores all the buildings. The pointer is to the 'head' of the list, and is one of the existing buildings. All tailing nodes after that are adjacencies.
    std::vector<BuildingNode*> CampusBuildings;
public:
    //functions to make memory not funky
    CampusGraph() = default;
    ~CampusGraph();
    CampusGraph(const CampusGraph&) = delete;
    CampusGraph& operator=(const CampusGraph&) = delete; 

    //Graph functions
    BuildingNode* getBuilding(const std::string& buildingName) const;
    bool hasBuilding(const BuildingNode* nodeInQuestion) const;
    bool addBuilding(const std::string& buildingName);
    bool addPath(BuildingNode* from, BuildingNode* to);
};

#endif
