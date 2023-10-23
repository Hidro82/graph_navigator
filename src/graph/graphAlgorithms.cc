#include "graphAlgorithms.h"
#include "../libs/containers/s21_containers.hpp"
#include <limits.h>
#include <queue>
#include <set>



std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph, const int &start_vertex) {
  if (start_vertex < 1 || start_vertex > (int)graph.getGraph().size())
    throw std::invalid_argument("start vertex is invalid value");
  std::vector<int> res{start_vertex};
  std::vector<bool> visits(graph.getGraph().size(), 0);
  visits[start_vertex - 1] = true;;
  s21::Stack<int> vertex;
  for (int i = start_vertex - 1; true; ) {
    for (int k = (int)graph.getGraph().size() - 1; k >= 0; --k) {
      if (graph.getGraph().at(i).at(k) > 0 && !visits[k]) {
        vertex.push(k);
        visits[k] = true;;
      }
    }
    if (vertex.empty()) break;
    i = vertex.top();
    res.push_back(vertex.top() + 1);
    vertex.pop();
  }
  return res;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph, const int& start_vertex) {
  if (start_vertex < 1 || start_vertex > (int)graph.getGraph().size())
    throw std::invalid_argument("start vertex is invalid value");
  std::vector<int> res{start_vertex};
  std::vector<bool> visits(graph.getGraph().size(), 0);
  visits[start_vertex - 1] = true;
  s21::queue<int> vertex;
  for (int i = start_vertex - 1; true; ) {
    for (int k = 0; k < (int)graph.getGraph().size(); ++k) {
      if (graph.getGraph()[i][k] > 0 && !visits[k]) {
        vertex.push(k);
        visits[k] = true;
      }
    }
    if (vertex.empty()) break;
    i = vertex.front();
    res.push_back(vertex.front() + 1);
    vertex.pop();
  }
  return res;
}

std::pair<int, std::vector<int>> GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph, const int &vertex1, const int &vertex2) {
  // std::vector<int> preVertex(graph.getGraph().size(), 0);
  std::vector<int> vertexes(graph.getGraph().size(), INT_MAX);
  vertexes[vertex1 - 1] = 0;
  s21::queue<int> visited;
  std::vector<int> path;
  path.push_back(vertex1 - 1);
  auto&& findMin = [](const std::vector<int>& vec)->int {
    int min = INT_MAX;
    int index = 0;
    for (int i = 0; i < (int)vec.size(); ++i) {
      if (vec[i] < min) {
        min = vec[i];
        index = i;
      }
    }
    return index;
  };
  for (int i = vertex1 - 1; i != vertex2 - 1; ) {
    for (int k = 0; k < (int)graph.getGraph().size(); ++k) {
      if (graph.getGraph()[i][k] > 0 && vertexes[i] + graph.getGraph()[i][k] < vertexes[k]) {
        vertexes[k] = vertexes[i] + graph.getGraph()[i][k];
        // preVertex[k] = i;
        // visited.push(k);
      }
    }
    if (visited.empty()) return {0, {}};
    // i = visited.front();
    i = findMin(vertexes);
    // visited.pop();
    path.push_back(i);
  }
  // фильтр лишних посещённых узлов пути
  int pathWeight = 0;
  for (int i = path.size() - 1; i > 0; --i) {printf("%d ", path[i]);} printf("\n");

  for (int i = path.size() - 1; i > 0; --i) {
    if (!graph.getGraph()[path[i - 1]][path[i]]) {
      path.erase(path.begin() + i - 1);
    } 
  }
  for (int i = 0; i < (int)path.size() - 1; ++i) {
    pathWeight += graph.getGraph()[path[i]][path[i + 1]];
    path[i] += 1;
  }
  path[path.size() - 1] += 1;
  return {pathWeight, path};
}







std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(Graph &graph){

  std::vector<std::vector<int>> base_graph = graph.getGraph();
  long unsigned int g_size = base_graph.size();
  std::vector<std::vector<int>> new_graph (g_size, std::vector<int>(g_size,0));
  std::set<int> found_way {0};

  while (found_way.size() != g_size){
    int min = std::numeric_limits<int>::max();
    int row_min = int();
    int col_min = int();
    int flag_found = 0;
    for (auto it=found_way.begin(); it != found_way.end(); it++){
      int row = it.operator*();
      for (long unsigned int col = 0; col < g_size; col++){
        if (found_way.count(col) || base_graph[row][col] == 0){continue;}
        if (base_graph[row][col] < min){
          min = base_graph[row][col];
          row_min = row;
          col_min = col;
          flag_found = 1;
        }
      }
    }

    if (flag_found) {
      new_graph[row_min][col_min] = min;
      new_graph[col_min][row_min] = min;
      found_way.insert(col_min);
      flag_found = 0;
    }
    
  }

  // for (long unsigned int i=0; i < base_graph.size(); i++ ){
  //   for (long unsigned int j=0; j < base_graph[i].size(); j++){
  //     std::cout << base_graph[i][j] << " ";
  //   }
  //     std::cout << "\n";
  // }

return new_graph;

};

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  ACO SolutionMaker(graph);
  return SolutionMaker.tsmSolver();
}
