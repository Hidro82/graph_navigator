#ifndef S21_ANTS_H
#define S21_ANTS_H

#include "graph.h"

struct TsmResult {
    std::vector<int> vertices;
    double distance = 0.0;
};

struct Mafs {
    explicit Mafs();

    Graph graph;
    double alpha = 1.0;
    double beta = 1.0;
    double q = 2.0;
    double basicPheromone = 0.5;
    double remain = 0.95;
    double total = 0.0;
    std::vector<std::vector<double>> pheromones;
    std::vector<std::vector<double>> probability;

    void updateBasicPheromone();
    void updatePheromoneMatrix(std::vector<std::vector<double>> pheromones_update);
    void updateProbabilityMatrix();
};

struct Ant {
    explicit Ant(int birth = 0);

    TsmResult path;

    std::vector<int> visited;
    int start = 0;
    int current = 0;
    bool movable = true;
    bool success = false;

    void decision(const Mafs &kField);
    std::vector<int> getNeighbors(const Graph &graph);
    double randomizer();
    void visitDiary();
};

class ACO {
    public:
        explicit ACO(const Graph &graph);
        TsmResult tsmSolver();

        void setAlpha(double alpha);
        void setBeta(double beta);
        void setDeposition(double q);
        void setRemaining(double remain);
        void setBasic(double basicPheromone);

        double getAlpha();
        double getBeta();
        double getDeposition();
        double getRemaining();
        double getBasic();

    private:
        std::vector<std::vector<double>> pheromoneUpdater();
        void shortestPath();
        void ColonyBirth();
        int iterations = 100;
        std::vector<Ant> ants_;
        Mafs kField_;
        TsmResult result_;
};

#endif // S21_ANTS_H