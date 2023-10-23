// #include "graph.h"
#include <vector>
#include <string>

class ConsoleInterface {
public:
    void start();

private:
    void menu();
    void action();
    void printVec(const std::vector<int> &vec);
    void printGraph(const std::vector<std::vector<int>> &graph);
    bool checkInt(const std::string &s);
    // Graph graph;
    // void 
    
};