//
//  DirecteGraph.cpp
//  Graphs
//
//  Created by Udit Samani on 6/6/19.
//  Copyright © 2019 Udit Samani. All rights reserved.
//

#include "DirecteGraph.hpp"


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w)
{
    Edge<T> newEdge(this, dest, w);
    this->adjList.push_back(newEdge);
}

template <class T>
bool Vertex<T>::removeEdge(Vertex<T> *dest)
{
    typename std::vector<Edge<T>>::iterator it;
    for(it = adjList.begin(); it!=adjList.end(); ++it)
    {
        if(it->dest == dest)
        {
            adjList.erase(it);
            return true;
        }
    }
    std::cout << "No edge found to be deleted." << std::endl;
    return false;
}


template <class T>
bool DirectedGraph<T>::addVertex(const T &element)
{
    typename std::vector<Vertex<T> *>::iterator it;
    for(it = this->vertexList.begin(); it!= this->vertexList.end(); ++it)
    {
        if ((*it)->element == element)
        {
            return false;
        }
    }
    Vertex<T> *vertex = new Vertex<T>(element);
    this->vertexList.push_back(vertex);
    return true;
}


template <class T>
bool DirectedGraph<T>::addEdge(const T &source, const T &destination, double w)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexList.end();
    int found = 0;
    Vertex<T> *src;
    Vertex<T> *dst;
    
    while(found!=2 && it!=ite)
    {
        if((*it)->element==source)
        {
            src = (*it);
            found++;
        }
        if ((*it)->element==destination)
        {
            dst = (*it);
            found++;
        }
        it++;
    }
    
    if(found!=2)
    {
        return false;
    }
    
    src->addEdge(dst, w);
    return true;
}

template <class T>
bool DirectedGraph<T>::removeEdge(const T &source, const T &destination)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexList.end();
    int found = 0;
    Vertex<T> *src;
    Vertex<T> *dst;
    
    while(found!=2 && it!=ite)
    {
        if((*it)->element==source)
        {
            src = (*it);
            found++;
        }
        if ((*it)->element==destination)
        {
            dst = (*it);
            found++;
        }
        it++;
    }
    
    if(found!=2)
    {
        return false;
    }
    
    src->removeEdge(dst);
    return true;
}


template <class T>
const void DirectedGraph<T>::dfs(Vertex<T> *u, std::vector<T> &result, int &time)
{
    u->pre = time++;
    u->visited = true;
    result.push_back(u->element);
    typename std::vector<Edge<T>>::iterator it = u->adjList.begin();
    typename std::vector<Edge<T>>::iterator ite = u->adjList.end();
    while(it!=ite)
    {
        if(it->dest->visited==false)
        {
            dfs(it->dest, result, time);
        }
        it++;
    }
    u->post = time++;
}


template <class T>
std::vector<T> DirectedGraph<T>::neighbors(const T &vertex)
{
    int time = 0;
    typename std::vector<Vertex<T>*>::iterator it = this->vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = this->vertexList.end();
    std::vector<T> result;
    
    while(it!=ite)
    {
        if((*it)->element == vertex)
        {
            dfs((*it),result, time);
            return result;
        }
        it++;
    }
    std::cout << "No such vertex in the graph" << std::endl;
    return result;
}


template <class T>
void DirectedGraph<T>::dfs()
{
    int time = 0;
    typename std::vector<Vertex<T>*>::iterator it = this->vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = this->vertexList.end();
    std::vector<T> result;
    
    while(it!=ite)
    {
        (*it)->visited = false;
        ++it;
    }
    
    it = this->vertexList.begin();
    
    while(it!=ite)
    {
        if((*it)->visited == false)
        {
            dfs((*it), result, time);
        }
        it++;
    }
}


template <class T>
void DirectedGraph<T>::printPrePost()
{
    typename std::vector<Vertex<T>*>::iterator it = this->vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = this->vertexList.end();
    
    while(it!=ite)
    {
        std::cout << (*it)->element << " : " << "[" << (*it)->pre <<", " << (*it)->post << "]" << std::endl;
        it++;
    }
}


template <class T>
bool DirectedGraph<T>::hasCycleUtil(Vertex<T> *u)
{
    if(u->visited == false)
    {
        u->visited = true;
        u->exploring = true;
        
        typename std::vector<Edge<T>>::iterator it = u->adjList.begin();
        typename std::vector<Edge<T>>::iterator ite = u->adjList.end();
        
        while(it!=ite)
        {
            if (!it->dest->visited && hasCycleUtil(it->dest))
            {
                return true;
            }
            else if (it->dest->exploring)
            {
                return true;
            }
            it++;
        }
        
    }
    u->exploring = false;
    return false;
}

template <class T>
bool DirectedGraph<T>::hasCycle()
{
    typename std::vector<Vertex<T>*>::iterator it = this->vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = this->vertexList.end();
    
    while(it!=ite)
    {
        (*it)->visited = false;
        (*it)->exploring = false;
        ++it;
    }
    
    it = this->vertexList.begin();
    
    while(it!=ite)
    {
        if(hasCycleUtil((*it)))
        {
            return true;
        }
        it++;
    }
    
    return false;
}

template <class T>
void DirectedGraph<T>::sortPostOrder()
{
    std::vector<T> result;
    this->dfs();
    
    std::sort(this->vertexList.begin(), this->vertexList.end(), [](const Vertex<T> *a, const Vertex<T> *b){return a->post < b->post;});
}

template <class T>
std::vector<T> DirectedGraph<T>::topologicalSort()
{
    this->sortPostOrder();
    typename std::vector<Vertex<T>*>::iterator it = this->vertexList.begin();
    typename std::vector<Vertex<T>*>::iterator ite = this->vertexList.end();
    std::vector<T> result;
    
    while(it!=ite)
    {
        result.push_back((*it)->element);
        it++;
    }
    return result;
}

