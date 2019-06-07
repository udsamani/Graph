//
//  DirecteGraph.hpp
//  Graphs
//
//  Created by Udit Samani on 6/6/19.
//  Copyright © 2019 Udit Samani. All rights reserved.
//

#ifndef DirecteGraph_hpp
#define DirecteGraph_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stack>
#include <deque>

template <class T>
class DirectedGraph;

template <class T>
class Edge;

template <class T>
class Vertex
{
private:
    T element;
    bool visited;
    bool exploring;
    std::vector<Edge<T>> adjList;
    void addEdge(Vertex<T> *dest, double w);
    bool removeEdge(Vertex<T> *dest);
    int pre;
    int post;
public:
    Vertex(T ele): element(ele), visited(false){}
    Vertex(const Vertex<T> &v);
    friend class DirectedGraph<T>;

};


template <class T>
class Edge
{
private:
    Vertex<T> *src;
    Vertex<T> *dest;
    double weight;
public:
    Edge(Vertex<T> *source, Vertex<T> *destination, double w = 0)
    {
        this->src = source;
        this->dest = destination;
        this->weight = w;
    }
    friend class DirectedGraph<T>;
    friend class Vertex<T>;
};

template <class T>
class DirectedGraph
{
private:
    std::vector<Vertex<T> *> vertexList;
    const void dfs(Vertex<T> *u, std::vector<T> &result, int &time);
    const void dfsStack(Vertex<T> *u, std::stack<Vertex<T>*> &stk);
    bool hasCycleUtil(Vertex<T> *u);
    void sortPostOrder();
public:
    bool addVertex(const T &element);
    bool addEdge(const T &source, const T &destination, double w);
    bool removeEdge(const T &source, const T &destination);
    bool removeVertex(const T &vertex);
    std::vector<T> neighbors(const T &vertex);
    void dfs();
    void printPrePost();
    bool hasCycle();
    std::vector<T> topologicalSort();
};

#endif /* DirecteGraph_hpp */
