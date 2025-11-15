#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm> 

const float float_max = std::numeric_limits<float>::max();
using Vertex = size_t;
using Graph = std::vector<std::unordered_map<Vertex, float>>;

float bfs(const Graph& gr, Vertex source, Vertex sink, std::vector<Vertex>& path) {
    std::vector<std::pair<Vertex, float>> used(gr.size(), { sink, -1 });
    used[source] = { source, float_max };
    std::queue<Vertex> q;
    q.push(source);

    while (q.size()) {
        Vertex front = q.front();
        q.pop();

        for (auto a : gr[front]) {
            if (a.second > 0 && used[a.first].second == -1) {
                q.push(a.first);
                std::pair<Vertex, float> mr = { front, std::min(used[front].second, a.second) };
                used[a.first] = mr;
            }
        }
        if (front == sink) {
            path.clear();

            for (Vertex current = sink; current != source; current = used[current].first) {
                path.push_back(current);
            }
            path.push_back(source);
            std::reverse(path.begin(), path.end());

            return used[sink].second;
        }
    }

    return 0;
}


float fordFulkerson(const Graph& gr, Vertex source, Vertex sink) {
    Graph residualGraph = gr;
    std::vector<Vertex> path;
    float max_flow = 0.0f;
    float path_flow;

    while ((path_flow = bfs(residualGraph, source, sink, path)) > 0) {
        max_flow += path_flow;

        for (size_t i = 0; i < path.size() - 1; ++i) {
            Vertex u = path[i];
            Vertex v = path[i + 1];

            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }
    }

    return max_flow;
}

int main() {
    int num_vertices = 6;
    Vertex source = 0;
    Vertex sink = 5;

    Graph graph(num_vertices);

    graph[0][1] = 10;
    graph[0][2] = 3;
    graph[1][3] = 4;
    graph[1][4] = 8;
    graph[1][2] = 2;
    graph[2][4] = 9;
    graph[3][5] = 6;
    graph[4][3] = 6;
    graph[4][5] = 10;

    float max_flow = fordFulkerson(graph, source, sink);

    std::cout << "max: " << max_flow << std::endl;

    return 0;
}
