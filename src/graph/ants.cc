#include "ants.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

/* Ant movement methods */

Ant::Ant(int birth) {
    start = birth;
    current = birth;
    visited.push_back(current);
    path.vertices.push_back(current);
}

std::vector<int> Ant::getNeighbors(const Graph &graph) {
    std::vector<int> neighbors;
    std::vector<std::vector<int>> graphMat = graph.getGraph();

    for (int destination = 0; destination < static_cast<double>(graph.getGraph().size()); destination++) {
        if ((graphMat[current][destination] != 0) && (current != destination)) {
            neighbors.push_back(destination);
        }
    }

    return neighbors;
}

double Ant::randomizer() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    return dist(re);
}

void Ant::decision(const Mafs &kField) {
    std::vector<int> pathes = getNeighbors(kField.graph);
    std::vector<std::vector<int>> graphMat = kField.graph.getGraph();
    std::vector<double> probabilities;
    double choice = randomizer();
    double localTotal = 0.0;

    if (pathes.empty()) {
        movable = false;
        return;
    }
    for (int i = 0; i < static_cast<int>(pathes.size()); i++) {
        localTotal += kField.probability[pathes[i]][current];
    }
    for (int i = 0; i < static_cast<int>(pathes.size()); i++) {
        if (i == 0) {
            probabilities.push_back(kField.probability[current][pathes[i]] / localTotal);
        } else {
            probabilities.push_back(probabilities[i - 1] + kField.probability[current][pathes[i]] / localTotal);
        }
        if (choice <= probabilities[i]) {
            path.distance += graphMat[current][pathes[i]];
            path.vertices.push_back(pathes[i]);
            current = pathes[i];
            break;
        }
    }
    visitDiary();
    if (current == start && visited.size() == graphMat.size()) {
        success = true;
    }
}

void Ant::visitDiary() {
    bool hasVisited = false;

    for (int i = 0; i < static_cast<int>(visited.size()); i++) {
        if (current == visited[i]) {
            hasVisited = true;
        }
    }

    if (!hasVisited) {
        visited.push_back(current);
    }
}

/* Math solving methods */

Mafs::Mafs() {}

void Mafs::updateBasicPheromone() {
    std::vector<std::vector<int>> graphMat = graph.getGraph();

    for (int i = 0; i < static_cast<int>(pheromones.size()); i++) {
        for (int j = 0; j < static_cast<int>(pheromones.size()); j++) {
            switch (graphMat[i][j]) {
                case 0:
                    pheromones[i][j] = 0.0;
                    break;
                default:
                    pheromones[i][j] = basicPheromone;
                    break;
            }
        }
    }
}

void Mafs::updatePheromoneMatrix(std::vector<std::vector<double>> pheromones_update) {
    for (int i = 0; i < static_cast<int>(graph.getGraph().size()) - 1; i++) {
        for (int j = 0; j < static_cast<int>(graph.getGraph().size()) - 1; j++) {
            pheromones[i][j] = (remain * pheromones[i][j]) + pheromones_update[i][j];
        }
    }
}

void Mafs::updateProbabilityMatrix() {
    std::vector<std::vector<int>> graphMat = graph.getGraph();
    total = 0.0;

    for (int i = 0; i < static_cast<int>(probability.size()); i++) {
        for (int j = 0; j < static_cast<int>(probability.size()); j++) {
            switch (graphMat[i][j]) {
                case 0:
                    probability[i][j] = 0.0;
                    break;
                default:
                    double t = pheromones[i][j];
                    double n = 1.0 / graphMat[i][j];
                    double wish = std::pow(t, alpha) * std::pow(n, beta);
                    total += wish;
                    probability[i][j] = wish;
                    break;
            }
        }
    }
}

/* Setters, getters and solution maker */

ACO::ACO(const Graph &graph) {
    kField_.graph = graph;
    for (int i = 0; i < static_cast<int>(graph.getGraph().size()); i++) {
        std::vector<double> buffer;
        for (int j = 0; j < static_cast<int>(graph.getGraph().size()); j++) {
            buffer.push_back(0.0);
        }
        kField_.pheromones.push_back(buffer);
        kField_.probability.push_back(buffer);
    }
    kField_.updateBasicPheromone();
    kField_.updateProbabilityMatrix();
    result_.distance = std::numeric_limits<double>::max();
}

void ACO::setAlpha(double alpha) {
    kField_.alpha = alpha;
    kField_.updateProbabilityMatrix();
}

void ACO::setBeta(double beta) {
    kField_.beta = beta;
    kField_.updateProbabilityMatrix();
}

void ACO::setDeposition(double q) {
    kField_.q = q;
}

void ACO::setRemaining(double remain) {
    kField_.remain = remain;
}

void ACO::setBasic(double basicPheromone) {
    kField_.basicPheromone = basicPheromone;
    kField_.updateBasicPheromone();
    kField_.updateProbabilityMatrix();
}


double ACO::getAlpha() {
    return kField_.alpha;
}

double ACO::getBeta() {
    return kField_.beta;
}

double ACO::getDeposition() {
    return kField_.q;
}

double ACO::getRemaining() {
    return kField_.remain;
}

double ACO::getBasic() {
    return kField_.basicPheromone;
}

std::vector<std::vector<double>> ACO::pheromoneUpdater() {
    std::vector<std::vector<double>> pheromones_update;

    for (int i = 0; i < static_cast<int>(kField_.graph.getGraph().size()); i++) {
        std::vector<double> buffer;
        for (int j = 0; j < static_cast<int>(kField_.graph.getGraph().size()); j++) {
            buffer.push_back(0.0);
        }
        pheromones_update.push_back(buffer);
    }

    for (int i = 0; i < static_cast<int>(ants_.size()); i++) {
        if (ants_[i].visited.size() == kField_.graph.getGraph().size()) {
            for (int j = 0; j < static_cast<int>(ants_[i].path.vertices.size()) - 1; j++) {
                pheromones_update[ants_[i].path.vertices[j]][ants_[i].path.vertices[j + 1]]
                    += kField_.q / ants_[i].path.distance;
            }
        }
    }

    return pheromones_update;
}

void ACO::ColonyBirth() {
    ants_.clear();
    ants_.resize(kField_.graph.getGraph().size());

    for (int i = 0; i < static_cast<int>(kField_.graph.getGraph().size()); i++) {
        ants_[i] = Ant(i);
    }
}

void ACO::shortestPath() {
    for (int i = 0; i < static_cast<int>(ants_.size()); i++) {
        if ((ants_[i].success) && (result_.distance > ants_[i].path.distance)) {
            result_ = ants_[i].path;
        }
    }
}

TsmResult ACO::tsmSolver() {
    for (int i = 0; i < iterations; i++) {
        ColonyBirth();

        for (int j = 0; j < static_cast<int>(ants_.size()); j++) {
            while (ants_[j].movable && !(ants_[j].success)) {
                ants_[j].decision(kField_);
            }
        }
        kField_.updatePheromoneMatrix(pheromoneUpdater());
        shortestPath();
    }

    return result_;
}