#include "cs4050.h"
#include "Bellman-Ford.h"
#include "Util.h"
#include <limits>
#include <iostream>

const float INF = std::numeric_limits<float>::infinity();

void ShortestPaths(
    Vertex *V, int countV, 
    Edge *E, int countE, 
    int t,
    float d[],
    int successor[])
{
    // Step 1: Initialize distances and successors
    for (int i = 0; i < countV; ++i) {
        d[i] = INF;         // Set initial distances to infinity
        successor[i] = -1;  // Initialize successors as -1 (no successor)
    }
    d[t - 1] = 0;  // Set distance to target `t` to 0

    // Debug: Initial state
    std::cout << "Initial distances and successors:\n";
    for (int i = 0; i < countV; ++i) {
        std::cout << "Vertex " << i + 1 << ": distance = " << (d[i] == INF ? "INF" : std::to_string(d[i])) 
                  << ", successor = " << successor[i] << "\n";
    }

    // Step 2: Relax edges |V| - 1 times
    for (int i = 0; i < countV - 1; ++i) {
        std::cout << "\nIteration " << i + 1 << " of edge relaxation:\n";
        for (int j = 0; j < countE; ++j) {
            int u = E[j].from - 1;  // Adjusting for 1-based index
            int v = E[j].to - 1;    // Adjusting for 1-based index
            float weight = E[j].weight;

            // Debug: Edge information
            std::cout << "Relaxing edge (" << u + 1 << " -> " << v + 1 << ") with weight " << weight << "\n";

            // Relax the edge if a shorter path is found
            if (d[u] != INF && d[u] + weight < d[v]) {
                d[v] = d[u] + weight; // Update the distance
                successor[v] = u;     // Update the successor

                // Debug: Update details
                std::cout << "Updated distance of vertex " << v + 1 << " to " << d[v] 
                          << " via vertex " << u + 1 << "\n";
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    std::cout << "\nChecking for negative-weight cycles:\n";
    for (int j = 0; j < countE; ++j) {
        int u = E[j].from - 1; // Adjusting for 1-based index
        int v = E[j].to - 1;   // Adjusting for 1-based index
        float weight = E[j].weight;

        if (d[u] != INF && d[u] + weight < d[v]) {
            std::cerr << "Graph contains a negative-weight cycle\n";
            return;
        }
    }

    // Debug: Final distances and successors
    std::cout << "\nFinal distances and successors:\n";
    for (int i = 0; i < countV; ++i) {
        std::cout << "successor (" << i + 1 << ")=" << (successor[i] == -1 ? "NULL" : std::to_string(successor[i] + 1)) 
                  << " distance to t=" << (d[i] == INF ? "INF" : std::to_string(d[i])) << "\n";
    }
}
