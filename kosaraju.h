#ifndef KOSARAJU_H_
#define KOSARAJU_H_

#include "graph.h"
#include <vector>
#include <algorithm>

namespace graph {

namespace {

enum class Colors {
    White,
    Gray,
    Black
};

void FillOrderDfs(const Graph& g, Vertex u, std::vector<Colors>& colors, std::vector<Vertex>& finish_order) {
    colors[u] = Colors::Gray;
    for (const Vertex& v : g.GetAdjacents(u)) {
        if (colors[v] == Colors::White) {
            FillOrderDfs(g, v, colors, finish_order);
        }
    }
    colors[u] = Colors::Black;
    finish_order.push_back(u);
}

void CollectSccDfs(const Graph& g, Vertex u, std::vector<Colors>& colors, Verticies& component) {
    colors[u] = Colors::Gray;
    component.push_back(u);
    for (const Vertex& v : g.GetAdjacents(u)) {
        if (colors[v] == Colors::White) {
            CollectSccDfs(g, v, colors, component);
        }
    }
    colors[u] = Colors::Black;
}

}

std::vector<Verticies> Kosaraju(const Graph& g) {
    if (g.empty()) {
        return {};
    }

    std::vector<Vertex> finish_order;
    finish_order.reserve(g.size());
    std::vector<Colors> colors(g.size(), Colors::White);
    
    for (Vertex i = 0; i < g.size(); ++i) {
        if (colors[i] == Colors::White) {
            FillOrderDfs(g, i, colors, finish_order);
        }
    }

    Graph g_inverted = g.GetInvertedGraph();

    std::vector<Verticies> strongly_connected_components;
    std::fill(colors.begin(), colors.end(), Colors::White);

    for (size_t i = 0; i < g.size(); ++i) {
        Vertex u = finish_order[g.size() - 1 - i];
        if (colors[u] == Colors::White) {
            Verticies current_scc;
            CollectSccDfs(g_inverted, u, colors, current_scc);
            strongly_connected_components.push_back(current_scc);
        }
    }

    return strongly_connected_components;
}

}

#endif // KOSARAJU_H_
