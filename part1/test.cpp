#include "gtest/gtest.h"
#include <vector>
#include <map>
#include <limits>

#include "graphs.h"

Graph createGraph() {
    Graph g(11);
    // Компонента 1 (0, 1, 2)
    g[0].push_back(1); 
    g[0].push_back(2);
    g[1].push_back(0); 
    g[1].push_back(2);
    g[2].push_back(0); 
    g[2].push_back(1);
    // Компонента 2 (3, 4, 5, 6)
    g[3].push_back(5); 
    g[3].push_back(6);
    g[4].push_back(5); 
    g[4].push_back(6);
    g[5].push_back(3); 
    g[5].push_back(4); 
    g[5].push_back(6);
    g[6].push_back(3); 
    g[6].push_back(4); 
    g[6].push_back(5);
    // Компонента 3 (7, 8, 9, 10)
    g[7].push_back(10);
    g[8].push_back(9); 
    g[8].push_back(10);
    g[9].push_back(8);
    g[10].push_back(7); 
    g[10].push_back(8);
    return g;
}

Graph createCycle() {
    Graph g(6);
    g[0].push_back(1); 
    g[0].push_back(2);
    g[1].push_back(0); 
    g[1].push_back(3);
    g[2].push_back(0); 
    g[2].push_back(3); 
    g[2].push_back(5); // Ребро 3-6 (2-5)
    g[3].push_back(1); 
    g[3].push_back(2); 
    g[3].push_back(4); // Ребро 4-5 (3-4)
    g[4].push_back(3); 
    g[4].push_back(5); // Ребро 5-6 (4-5)
    g[5].push_back(2); 
    g[5].push_back(4); // Ребро 6-3, 6-5 (5-2, 5-4)
    return g;
}

Graph createTree() {
    Graph g(6);
    g[0].push_back(1); 
    g[0].push_back(2); 
    g[0].push_back(3);
    g[1].push_back(0);
    g[2].push_back(0);
    g[3].push_back(0); 
    g[3].push_back(4); 
    g[3].push_back(5);
    g[4].push_back(3);
    g[5].push_back(3);
    return g;
}

WeightedGraph createWeighted() {
    WeightedGraph wg(4);
    wg[0].push_back({ 1, 1 }); 
    wg[0].push_back({ 2, 5 });
    wg[1].push_back({ 0, 1 }); 
    wg[1].push_back({ 2, 2 }); 
    wg[1].push_back({ 3, 3 });
    wg[2].push_back({ 0, 5 }); 
    wg[2].push_back({ 1, 2 }); 
    wg[2].push_back({ 3, 1 });
    wg[3].push_back({ 1, 3 }); 
    wg[3].push_back({ 2, 1 });
    return wg;
}

Graph createBipart() {
    Graph g(6);
    g[0].push_back(3); 
    g[0].push_back(4); // 1->4, 1->5
    g[1].push_back(3); 
    g[1].push_back(5); // 2->4, 2->6
    g[2].push_back(4); 
    g[2].push_back(5); // 3->5, 3->6
    g[3].push_back(0); 
    g[3].push_back(1); // 4->1, 4->2
    g[4].push_back(0); 
    g[4].push_back(2); // 5->1, 5->3
    g[5].push_back(1); 
    g[5].push_back(2); // 6->2, 6->3
    return g;
}

Graph createNonBipart() {
    Graph g(3);
    g[0].push_back(1); 
    g[0].push_back(2);
    g[1].push_back(0); 
    g[1].push_back(2);
    g[2].push_back(0); 
    g[2].push_back(1);
    return g;
}


TEST(GraphTest, CountConn) {
    Graph graph = createGraph();
    EXPECT_EQ(countConn(graph), 3);

    Graph single(4); // 0-1-2-3
    single[0].push_back(1); 
    single[1].push_back(0);
    single[1].push_back(2); 
    single[2].push_back(1);
    single[2].push_back(3); 
    single[3].push_back(2);
    EXPECT_EQ(countConn(single), 1);

    Graph multi(5); // 0-1, 2-3, 4
    multi[0].push_back(1); 
    multi[1].push_back(0);
    multi[2].push_back(3); 
    multi[3].push_back(2);
    EXPECT_EQ(countConn(multi), 3);

    Graph empty(0);
    EXPECT_EQ(countConn(empty), 0);

    Graph singleNodeGraph(1);
    EXPECT_EQ(countConn(singleNodeGraph), 1);
}

TEST(GraphTest, HasCycle) {
    Graph cycle = createCycle();
    EXPECT_TRUE(hasCycle(cycle));

    Graph graph = createGraph();
    EXPECT_TRUE(hasCycle(graph));

    Graph tree = createTree();
    EXPECT_FALSE(hasCycle(tree));

    Graph forest(6); // Два дерева 0-1-2 и 3-4-5
    forest[0].push_back(1);
    forest[1].push_back(0);
    forest[1].push_back(2);
    forest[2].push_back(1);
    forest[3].push_back(4); 
    forest[4].push_back(3);
    forest[4].push_back(5); 
    forest[5].push_back(4);
    EXPECT_FALSE(hasCycle(forest));

    Graph empty(0);
    EXPECT_FALSE(hasCycle(empty));

    Graph single(1);
    EXPECT_FALSE(hasCycle(single));
}

TEST(GraphTest, IsTree) {
    Graph tree = createTree();
    EXPECT_TRUE(isTree(tree));

    Graph cycle = createCycle();
    EXPECT_FALSE(isTree(cycle));

    Graph graph = createGraph(); // Несвязный + циклы
    EXPECT_FALSE(isTree(graph));

    Graph forest(6); // Несвязный
    forest[0].push_back(1); 
    forest[1].push_back(0);
    forest[1].push_back(2); 
    forest[2].push_back(1);
    forest[3].push_back(4); 
    forest[4].push_back(3);
    forest[4].push_back(5); 
    forest[5].push_back(4);
    EXPECT_FALSE(isTree(forest));

    Graph empty(0);
    EXPECT_TRUE(isTree(empty));

    Graph single(1);
    EXPECT_TRUE(isTree(single));
}

TEST(GraphTest, Dijkstra) {
    WeightedGraph wg = createWeighted();
    std::map<int, long long> expected_a = { {0, 0}, {1, 1}, {2, 3}, {3, 4} };
    EXPECT_EQ(dijkstra(wg, 0), expected_a);

    std::map<int, long long> expected_b = { {0, 4}, {1, 3}, {2, 1}, {3, 0} };
    EXPECT_EQ(dijkstra(wg, 3), expected_b);

    // Тест с несвязной вершиной
    WeightedGraph wg_disconn = createWeighted();
    wg_disconn.resize(5);
    std::map<int, long long> expected_c = {
        {0, 0}, {1, 1}, {2, 3}, {3, 4}, {4, std::numeric_limits<long long>::max()}
    };
    EXPECT_EQ(dijkstra(wg_disconn, 0), expected_c);

    WeightedGraph empty(0);
    EXPECT_TRUE(dijkstra(empty, 0).empty()); // Ожидаем пустую карту

    WeightedGraph single(1);
    std::map<int, long long> expected_d = { {0, 0} };
    EXPECT_EQ(dijkstra(single, 0), expected_d);
}

TEST(GraphTest, IsBipart) {
    Graph bipart = createBipart();
    EXPECT_TRUE(isBipart(bipart));

    Graph nonBipart = createNonBipart(); // Треугольник
    EXPECT_FALSE(isBipart(nonBipart));

    Graph graph = createGraph(); // Первая компонента - треугольник
    EXPECT_FALSE(isBipart(graph));

    Graph tree = createTree(); // Любое дерево двудольно
    EXPECT_TRUE(isBipart(tree));

    Graph forest(6); // Лес двудольных графов (деревьев)
    forest[0].push_back(1); 
    forest[1].push_back(0);
    forest[1].push_back(2); 
    forest[2].push_back(1);
    forest[3].push_back(4); 
    forest[4].push_back(3);
    forest[4].push_back(5); 
    forest[5].push_back(4);
    EXPECT_TRUE(isBipart(forest));

    Graph empty(0);
    EXPECT_TRUE(isBipart(empty));

    Graph single(1);
    EXPECT_TRUE(isBipart(single));

    Graph odd(5); // Цикл C5 (0-1-2-3-4-0) - не двудольный
    odd[0].push_back(1); 
    odd[1].push_back(0);
    odd[1].push_back(2); 
    odd[2].push_back(1);
    odd[2].push_back(3); 
    odd[3].push_back(2);
    odd[3].push_back(4); 
    odd[4].push_back(3);
    odd[4].push_back(0); 
    odd[0].push_back(4);
    EXPECT_FALSE(isBipart(odd));

    Graph even(6); // Цикл C6 (0-1-2-3-4-5-0) - двудольный
    even[0].push_back(1); 
    even[1].push_back(0);
    even[1].push_back(2); 
    even[2].push_back(1);
    even[2].push_back(3); 
    even[3].push_back(2);
    even[3].push_back(4); 
    even[4].push_back(3);
    even[4].push_back(5); 
    even[5].push_back(4);
    even[5].push_back(0); 
    even[0].push_back(5);
    EXPECT_TRUE(isBipart(even));
}


 int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
 }
