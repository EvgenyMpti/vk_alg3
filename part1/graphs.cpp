#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <limits>
#include <numeric>

#include "graphs.h"

void dfsComp(int startNode, const Graph& graph, std::vector<bool>& visited) {
    std::stack<int> st;
    st.push(startNode);
    visited[startNode] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        // Идем по соседям
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v); // добавляем для дальнейшего обхода
            }
        }
    }
}

int countConn(const Graph& graph) {
    int n = graph.size();
    if (n == 0) 
        return 0;

    std::vector<bool> visited(n, false);
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            count++;
            dfsComp(i, graph, visited);
        }
    }
    return count;
}

// visited: 0 - не посещен, 1 - в очереди; parent: родителя узла
bool bfsCycle(int startNode, const Graph& graph, std::vector<int>& visited, std::vector<int>& parent) {
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = 1; // посещенный
    parent[startNode] = -1; // нет родителя

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (visited[v] == 0) { // Если сосед не посещен
                visited[v] = 1;
                parent[v] = u;
                q.push(v);
            }
            else if (v != parent[u]) {
                return true; // Нашли обратное ребро
            }
        }
    }
    return false;
}

bool hasCycle(const Graph& graph) {
    int n = graph.size();
    if (n == 0) 
        return false;
    
    std::vector<int> visited(n, 0); // 0 - не посещен, 1 - посещен
    std::vector<int> parent(n, -1); // Храним родителя

    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            if (bfsCycle(i, graph, visited, parent)) {
                return true;
            }
        }
    }
    return false;
}

bool isTree(const Graph& graph) {
    int n = graph.size();
    if (n == 0) 
        return true;

    std::vector<int> visited(n, 0); // 0 - не посещен, 1 - посещен
    std::vector<int> parent(n, -1);
    int components = 0;
    bool cycle_found = false;

    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            components++;
            if (components > 1) {
                return false; // граф не связный
            }
            // Проверяем наличие цикла в текущей компоненте
            std::queue<int> q;
            q.push(i);
            visited[i] = 1;
            parent[i] = -1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : graph[u]) {
                    if (visited[v] == 0) {
                        visited[v] = 1;
                        parent[v] = u;
                        q.push(v);
                    }
                    else if (v != parent[u]) {
                        cycle_found = true;
                        break;
                    }
                }
                if (cycle_found) break;
            }
        }
        if (cycle_found) 
            return false;
    }

    return components == 1 && !cycle_found;
}

std::map<int, long long> dijkstra(const WeightedGraph& graph, int startNode) {
    int n = graph.size();
    std::map<int, long long> dist;
    for (int i = 0; i < n; ++i) {
        dist[i] = std::numeric_limits<long long>::max(); // inf
    }

    if (startNode >= n || startNode < 0) 
        return dist;

    dist[startNode] = 0;

    // расстояние, вершина
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
    pq.push({ 0, startNode });

    while (!pq.empty()) {
        long long d = pq.top().first; // текущее кратчайшее расстояние
        int u = pq.top().second; // текущая вершина
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        // обработка ребер
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != std::numeric_limits<long long>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

bool bfsBipart(int startNode, const Graph& graph, std::vector<int>& colors) {
    std::queue<int> q;
    q.push(startNode);
    colors[startNode] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int current = colors[u];

        for (int v : graph[u]) {
            if (colors[v] == 0) { // сосед не раскрашен
                colors[v] = -current; // красим в противоположный
                q.push(v);
            }
            else if (colors[v] == current) {
                return false; // граф не двудольный
            }
        }
    }
    return true;
}

bool isBipart(const Graph& graph) {
    int n = graph.size();
    if (n == 0) 
        return true;
    std::vector<int> colors(n, 0); // 0 - не окрашен, 1 - цвет 1, -1 - цвет 2

    for (int i = 0; i < n; ++i) {
        if (colors[i] == 0) { // вершина еще не входит в проверенные
            if (!bfsBipart(i, graph, colors)) {
                return false;
            }
        }
    }
    return true;
}
