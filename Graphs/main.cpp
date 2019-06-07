//
//  main.cpp
//  Graphs
//
//  Created by Udit Samani on 6/4/19.
//  Copyright © 2019 Udit Samani. All rights reserved.
//

#include <iostream>
#include "DirecteGraph.cpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    DirectedGraph<char> graph;
    graph.addVertex('a');
    graph.addVertex('b');
    graph.addVertex('c');
    graph.addVertex('d');
    graph.addVertex('e');
    graph.addVertex('f');
    graph.addVertex('g');
    graph.addVertex('h');
    graph.addEdge('a','f', 0);
    graph.addEdge('a', 'b', 0);
    graph.addEdge('a', 'c', 0);
    graph.addEdge('f', 'b', 0);
    graph.addEdge('f', 'g', 0);
    graph.addEdge('e', 'f', 0);
    graph.addEdge('e', 'h', 0);
    graph.addEdge('e', 'g', 0);
    graph.addEdge('b', 'e', 0);
    graph.addEdge('c', 'd', 0);
    graph.addEdge('d', 'a', 0);
    graph.addEdge('d', 'h', 0);
    graph.addEdge('h', 'g', 0);
    std::vector<char> result = graph.topologicalSort();
    typename std::vector<char>::iterator it = result.begin();
    typename std::vector<char>::iterator ite = result.end();
    
    while(it!=ite)
    {
        std::cout << (*it) << std::endl;
        ++it;
    }
    graph.printPrePost();
    
}
