//
//  Graph.hpp
//  Graphs
//
//  Created by Udit Samani on 6/4/19.
//  Copyright © 2019 Udit Samani. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>


template <class T>
class Edge;


template <class T>
class Vertex
{
private:
    T element;
    bool visited;
public:
    Vertex(T &ele, bool visit = false): element(ele), visited(visit){}
    friend class Edge<T>;
};


template <class T>
class Edge
{
private:
    Vertex<T> *src;
    Vertex<T> *dest;
    int weight;
public:
    Edge();
    
};
#endif /* Graph_hpp */
