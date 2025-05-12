#pragma once

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <utility>
#include <limits>
#include <stack>

// Список смежности
using Graph = std::vector<std::vector<int>>; // вершина
using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>; // вершина, вес

// Поиск компонент связности
int countConn(const Graph& graph); // O(V + E)
void dfsComp(int startNode, const Graph& graph, std::vector<bool>& visited);

// Поиск цикла
bool hasCycle(const Graph& graph); // O(V + E)
bool bfsCycle(int startNode, const Graph& graph, std::vector<int>& visited, std::vector<int>& parent); 

// Является ли граф деревом
bool isTree(const Graph& graph); // O(V + E)

// Алгоритм Дейкстры (вершина -> расстояние)
std::map<int, long long> dijkstra(const WeightedGraph& graph, int startNode); // O(E * log V)

// Проверка графа на двудольность
bool isBipart(const Graph& graph); // O(V + E)
bool bfsBipart(int startNode, const Graph& graph, std::vector<int>& colors); 
