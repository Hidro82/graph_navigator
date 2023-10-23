#include <vector>
#include <string>

enum class GraphType {
  UnweightedUndirected,
  WeightedUndirected,
  UnweightedDirected,
  WeightedDirected
};

class Graph {
public:
  Graph();
  Graph(const std::string &filename);
  ~Graph();

  void LoadGraphFromFile(const std::string &filename);
  void ExportGraphToDot(const std::string &filename);

  const std::vector<std::vector<int>>& getGraph() const noexcept;
  const GraphType& getType() const noexcept;

private:
  std::vector<std::string> readFile(const std::string &filePath) const;
  void parseFile(const std::vector<std::string> &fileData);
  void checkGraphType();

  std::vector<std::vector<int>> graph;
  GraphType type;
};
