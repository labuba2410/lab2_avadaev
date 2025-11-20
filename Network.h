#pragma once

#include <vector>
#include <map>
#include <set>
#include <queue>
#include "Pipe.h"
#include "CS.h"

struct Connection {
    int pipeId;
    int startCSId;
    int endCSId;
    int diameter;

    Connection(int pipeId, int startCSId, int endCSId, int diameter)
        : pipeId(pipeId), startCSId(startCSId), endCSId(endCSId), diameter(diameter) {
    }
};

class GasNetwork {
private:
    std::map<int, std::vector<Connection>> adjacencyList; 
    std::map<int, bool> usedPipes; 

public:
    GasNetwork();

    bool addConnection(int pipeId, int startCSId, int endCSId, int diameter);
    bool removeConnection(int pipeId);
    void displayNetwork() const;
    std::vector<int> topologicalSort() const;
    bool isAcyclic() const;

    const std::map<int, std::vector<Connection>>& getAdjacencyList() const { return adjacencyList; }
    const std::map<int, bool>& getUsedPipes() const { return usedPipes; }
    bool isPipeUsed(int pipeId) const;
    std::vector<int> findAvailablePipes(const std::map<int, Pipe>& pipes, int diameter) const;
};