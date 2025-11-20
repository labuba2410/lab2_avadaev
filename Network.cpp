#include "Network.h"
#include <iostream>
#include <algorithm>

GasNetwork::GasNetwork() {}

bool GasNetwork::addConnection(int pipeId, int startCSId, int endCSId, int diameter) {

    if (startCSId == endCSId) {
        std::cout << "Error: Cannot connect CS to itself!\n";
        return false;
    }

 
    if (usedPipes.find(pipeId) != usedPipes.end()) {
        std::cout << "Error: Pipe " << pipeId << " is already used in the network!\n";
        return false;
    }


    Connection conn(pipeId, startCSId, endCSId, diameter);
    adjacencyList[startCSId].push_back(conn);
    usedPipes[pipeId] = true;


    if (!isAcyclic()) {
        
        removeConnection(pipeId);
        std::cout << "Error: Connection creates a cycle in the network!\n";
        return false;
    }

    return true;
}

bool GasNetwork::removeConnection(int pipeId) {
    if (usedPipes.find(pipeId) == usedPipes.end()) {
        return false;
    }


    for (auto& pair : adjacencyList) {
        auto& connections = pair.second;
        connections.erase(
            std::remove_if(connections.begin(), connections.end(),
                [pipeId](const Connection& conn) { return conn.pipeId == pipeId; }),
            connections.end()
        );
    }

   
    auto it = adjacencyList.begin();
    while (it != adjacencyList.end()) {
        if (it->second.empty()) {
            it = adjacencyList.erase(it);
        }
        else {
            ++it;
        }
    }

    usedPipes.erase(pipeId);
    return true;
}

void GasNetwork::displayNetwork() const {
    if (adjacencyList.empty()) {
        std::cout << "Network is empty.\n";
        return;
    }

    std::cout << "=== GAS TRANSPORT NETWORK ===\n";
    for (const auto& pair : adjacencyList) {
        std::cout << "CS " << pair.first << " -> ";
        for (const auto& conn : pair.second) {
            std::cout << "CS " << conn.endCSId << " (Pipe " << conn.pipeId << ", Diameter " << conn.diameter << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "=============================\n";
}

std::vector<int> GasNetwork::topologicalSort() const {
    std::vector<int> result;
    std::map<int, int> inDegree;
    std::queue<int> zeroInDegree;

    for (const auto& pair : adjacencyList) {
      
        inDegree[pair.first];
        for (const auto& conn : pair.second) {
            inDegree[conn.endCSId]++;
        }
    }

    for (const auto& pair : inDegree) {
        if (pair.second == 0) {
            zeroInDegree.push(pair.first);
        }
    }

 
    while (!zeroInDegree.empty()) {
        int csId = zeroInDegree.front();
        zeroInDegree.pop();
        result.push_back(csId);

        if (adjacencyList.find(csId) != adjacencyList.end()) {
            for (const auto& conn : adjacencyList.at(csId)) {
                inDegree[conn.endCSId]--;
                if (inDegree[conn.endCSId] == 0) {
                    zeroInDegree.push(conn.endCSId);
                }
            }
        }
    }

    if (result.size() != inDegree.size()) {
        return std::vector<int>(); 
    }

    return result;
}

bool GasNetwork::isAcyclic() const {
    return !topologicalSort().empty();
}

bool GasNetwork::isPipeUsed(int pipeId) const {
    return usedPipes.find(pipeId) != usedPipes.end();
}

std::vector<int> GasNetwork::findAvailablePipes(const std::map<int, Pipe>& pipes, int diameter) const {
    std::vector<int> availablePipes;

    for (const auto& pair : pipes) {
        const Pipe& pipe = pair.second;
        if (pipe.getDiameter() == diameter && !isPipeUsed(pipe.getId()) && !pipe.getStatus()) {
            availablePipes.push_back(pipe.getId());
        }
    }

    return availablePipes;
}