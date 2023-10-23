#include "ants.h"

class GraphAlgorithms {
public:
    std::vector<int> DepthFirstSearch(const Graph &graph, const int &start_vertex);
    std::vector<int> BreadthFirstSearch(const Graph &graph, const int &start_vertex);
    std::pair<int, std::vector<int>> GetShortestPathBetweenVertices(const Graph &graph, const int &vertex1, const int &vertex2);
    std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(const Graph &graph);
    std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
    TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};