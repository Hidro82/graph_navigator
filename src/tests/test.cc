#include "../graph/graphAlgorithms.h"
#include "gtest/gtest.h"

void printVec(const std::vector<int> &vec) {
    for (const int &i : vec) std::cout << i << ' ';
    std::cout << '\n';
}

bool vecEqual(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    int size = vec1.size() == vec2.size() ? vec1.size() : -1;
    if (size == -1) return false; 
    for (int i = 0; i < size; ++i) if (vec1.at(i) != vec2.at(i)) return false;
    return true;
}

TEST(DFS, Unweighted_Undirected_1) {
  std::vector<int> res{1, 3, 2, 4};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Unweighted_Undirected_2_1) {
  std::vector<int> res{1, 2, 3};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Unweighted_Undirected_2_2) {
  std::vector<int> res{4, 5};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 4);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Weighted_Undirected_1) {
  std::vector<int> res{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/WU_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Unweighted_Directed_1) {
  std::vector<int> res{1, 2, 3, 5};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Unweighted_Directed_2) {
  std::vector<int> res{4, 5, 2, 3, 6};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 4);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(DFS, Unweighted_Directed_3) {
  std::vector<int> res{8, 5, 1, 6, 2, 3, 4, 7, 9};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_3.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.DepthFirstSearch(graph, 8);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Undirected_1) {
  std::vector<int> res{1, 3, 2, 4};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Undirected_2_1) {
  std::vector<int> res{1, 2, 3};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Undirected_2_2) {
  std::vector<int> res{4, 5};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 4);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Weighted_Undirected_1) {
  std::vector<int> res{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/WU_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Directed_1) {
  std::vector<int> res{1, 2, 3, 5};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_1.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 1);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Directed_2) {
  std::vector<int> res{4, 5, 2, 3, 6};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_2.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 4);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(BFS, Unweighted_Directed_3) {
  std::vector<int> res{8, 5, 1, 6, 7, 2, 9, 3, 4,};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_3.txt");
  GraphAlgorithms algos;
  std::vector<int>&& vec = algos.BreadthFirstSearch(graph, 8);
  printVec(vec);
  ASSERT_TRUE(vecEqual(vec, res));
}

TEST(Dijkstra, Unweighted_Undirected_1) {
  std::pair<int, std::vector<int>> res{3, {1, 3, 2, 4}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_1.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 4);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Unweighted_Undirected_2_1) {
  std::pair<int, std::vector<int>> res{2, {1, 2, 3}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 3);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Unweighted_Undirected_2_2) {
  std::pair<int, std::vector<int>> res{0, {}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UU_2.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 4);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Weighted_Undirected_1) {
  std::pair<int, std::vector<int>> res{29, {1, 2}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/WU_1.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 8);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Unweighted_Directed_1) {
  std::pair<int, std::vector<int>> res{2, {1, 2, 5}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_1.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 5);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Unweighted_Directed_2) {
  std::pair<int, std::vector<int>> res{1, {2, 5}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_2.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 2, 5);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}

TEST(Dijkstra, Unweighted_Directed_3) {
  std::pair<int, std::vector<int>> res{2, {1, 7, 5}};
  Graph graph;
  graph.LoadGraphFromFile("tests/files/UD_3.txt");
  GraphAlgorithms algos;
  auto&& path = algos.GetShortestPathBetweenVertices(graph, 1, 5);
  printf("%d\n", path.first);
  printVec(path.second); 
  ASSERT_TRUE(path.first == res.first && vecEqual(path.second, res.second));
}


TEST(Prim, Unweighted_Directed_test_1) {
  Graph right_answer;
  right_answer.LoadGraphFromFile("tests/files/WU_2_prim_answer.txt");
  std::vector<std::vector<int>> r_answer = right_answer.getGraph();
  
  Graph task;
  task.LoadGraphFromFile("tests/files/WU_2.txt");
  
  GraphAlgorithms algos_answer;
  std::vector<std::vector<int>> a_answer = algos_answer.GetLeastSpanningTree(task);

  for (long unsigned int i=0; i < r_answer.size(); i++ ){
    for (long unsigned int j=0; j < r_answer[i].size(); j++){
      ASSERT_TRUE(r_answer[i][j] == a_answer[i][j]);
    }
  }
}

TEST(TSM, TsmConstructor) {
  Graph task;
  task.LoadGraphFromFile("tests/files/WU_2.txt");
  GraphAlgorithms interface;

  TsmResult result = interface.SolveTravelingSalesmanProblem(task);
  ASSERT_DOUBLE_EQ(result.distance, 79.0);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}