#include "ConsoleInterface.h"
#include "../libs/containers/s21_containers.hpp"
#include <limits.h>
#include <queue>
#include <set>

#include <string>
#include "graphAlgorithms.h"

// #include "graph.h"
// void printGraph(const std::vector<std::vector<int>> &graph) {
//   for (auto &vec : graph) {
//     for (const int &i : vec) {
//       std::cout << i << ' ';
//     }
//     std::cout << '\n';
//   }
// }

bool ConsoleInterface::checkInt(const std::string &s) {
    int return_flag = 0;
    for (long unsigned int i=0; i < s.length(); i++){
      if (isdigit(s[i]) == false){
        return_flag = 1;
        break;
      }
    }
    return return_flag;
}

void ConsoleInterface::printVec(const std::vector<int> &vec) {
    std::cout << "\n----DONE----" << endl;
    for (const int &i : vec) std::cout << i << ' ';
    std::cout << '\n';
    action();

}

void ConsoleInterface::printGraph(const std::vector<std::vector<int>> &graph) {
  std::cout << "\n----DONE----" << endl;
  for (auto &vec : graph) {
    for (const int &i : vec) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
  action();
}

void ConsoleInterface::start() {
  // std::cout << "Hi! Do't waste my time! Load your graph!" << endl;  
    menu();
  // }
}

void ConsoleInterface::action() {
  int choice = int();
  while (true){
    std::cout << "\nExit or Continue?" << endl;
    std::cout << "1. Continue" << endl;
    std::cout << "Print something else for Exit" << endl;
    std::cin >> choice;




    if (choice == 1){
      break;
    }
    else {
      exit(0);
    }
    
  }


}


void ConsoleInterface::menu(){
  
  std::string temp_cin = std::string();
  int choice = int();
  Graph graph;
  std::string line = std::string();

  // std::cout << "\nChoose option" << endl;  
  
  
  
  std::cout << "Hi! Let's do't waste time! Load your graph!" << endl;  
  
  while (true){
    std::cin >> line;
    try {
      graph.LoadGraphFromFile(line);
      std::cout << "Loaded Success!" << endl;  
  
      break;
    } catch (std::exception &e) {
      std::cout << "Error: " << e.what() << endl;
      std::cout << "\nTry Another File:" << endl;  
    }
  }  

  


  while (true) {

    std::cout << "\nChoose option" << endl;  
    std::cout << "*********" << endl;
    std::cout << "1. Load new graph from file" << endl;  
    std::cout << "2. Breadth First Search" << endl;  
    std::cout << "3. Depth First Search" << endl;  
    std::cout << "4. Shortest path between any two vertices" << endl;  
    std::cout << "5. Shortest path between all pair of vertices" << endl;  
    std::cout << "6. Prim's Algorithm" << endl;  
    std::cout << "7. Solving salesman problem" << endl;  
    std::cout << "*********" << endl;
    std::cout << "0. EXIT\n" << endl;  
    
    
    std::cout << "Enter your number:" << endl; 
    // try { 
    std:: cin >> temp_cin;
    if (checkInt(temp_cin)){
      std::cout << "\n---Answer---\nWrong arg!" << endl;
      action();
      continue;
    }
    else {choice = std::stoi(temp_cin);}


    // // continue;
    // } catch (std::exception &e) {
    //   std::cout << "Error: " << e.what() << endl;
    //   // std::cout << "\nTry Another File:" << endl;  
    // }

    GraphAlgorithms algos;

    if (choice == 1){
      continue;
    }
    else if (choice ==2){
      // GraphAlgorithms algos;
      std::vector<int> v = algos.BreadthFirstSearch(graph, 1);
      printVec(v);
    }
    else if (choice ==3){
      std::vector<int> v = algos.DepthFirstSearch(graph, 1);
      // std::cout << "\n----DONE----" << endl;
      printVec(v);
      // action();
    }
    else if (choice ==4){
      continue;
    }
    else if (choice ==5){
      continue;
    }
    else if (choice ==6){
      // continue;
      std::vector<std::vector<int>> v = algos.GetLeastSpanningTree(graph);
      printGraph(v);
      // action();
    }
    else if (choice ==7){
      continue;      
    }
    else if (choice ==0){
      exit(0);      
    }
    else {
      std::cout << "\n---Answer---\nWrong arg!" << endl;
      // std::cout << "Wrong arg! Try again?" << endl;
      action();
      continue;
    }

  }
  


}