#include <iostream>
#include "graph.h"
#include "kosaraju.h"

int main() {
	graph::Graph g(8);
	g.AddEdge(0, 1);
	g.AddEdge(1, 2);
	g.AddEdge(2, 0);
	g.AddEdge(1, 3);
    g.AddEdge(6, 7);
    g.AddEdge(7, 6);

    std::vector<graph::Verticies> sccs = graph::Kosaraju(g);

    std::cout << "Strongly Connected Components:\n";
    int component_count = 1;
    for (const auto& component : sccs) {
        std::cout << "Component " << component_count++ << ": ";
        for (graph::Vertex v : component) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
	
	return 0;
}
