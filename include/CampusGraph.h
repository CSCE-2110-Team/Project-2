#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

//structs to organize buildings. Used for adjacency listing.
struct BuildingNode {
    std::string buildingName = "";
    std::vector<BuildingNode*> neighbors;
};

class CampusGraph {
private:
    //Memory, stores all the buildingsNodes
    std::vector<BuildingNode*> CampusBuildings;
public:
    //functions to make memory not funky
    CampusGraph() = default;
    ~CampusGraph();
    CampusGraph(const CampusGraph&) = delete;
    CampusGraph& operator=(const CampusGraph&) = delete; 

    //Graph functions
    const std::vector<BuildingNode*>& getBuildings() const {return CampusBuildings; }
    BuildingNode* getBuilding(const std::string& buildingName) const;
    bool hasBuilding(const BuildingNode* nodeInQuestion) const;
    bool addBuilding(const std::string& buildingName);
    bool addPath(BuildingNode* from, BuildingNode* to);
};

#endif
