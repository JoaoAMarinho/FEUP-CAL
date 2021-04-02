/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include <iostream>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<int>> bestPaths;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    // TODO implement this
    for (Vertex<T>* vertex : vertexSet) {
        vertex->dist=-1;
        vertex->path=NULL;
    }
    Vertex<T>* vertex = findVertex(orig);
    vertex->dist=0;
    std::queue<Vertex<T>*> vertexQueue;
    vertexQueue.push(vertex);

    while (!vertexQueue.empty()){
        vertex=vertexQueue.front();
        vertexQueue.pop();
        for (Edge<T> e:vertex->adj) {
            if(e.dest->dist==-1){
                vertexQueue.push(e.dest);
                e.dest->dist=vertex->dist+1;
                e.dest->path=vertex;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    // TODO implement this
    for (Vertex<T>* vertex : vertexSet) {
        vertex->dist=LONG_MAX;
        vertex->path=NULL;
    }
    Vertex<T>* vertex = findVertex(origin);
    vertex->dist=0;

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(vertex);

    while (!q.empty()){
        vertex=q.extractMin();
        for (Edge<T> edge : vertex->adj) {
            if(edge.dest->dist > vertex->dist + edge.weight) {
                double oldDist = edge.dest->dist;
                edge.dest->dist = vertex->dist + edge.weight;
                edge.dest->path = vertex;
                if (oldDist == LONG_MAX) {
                    q.insert(edge.dest);
                } else {
                    q.decreaseKey(edge.dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
    for (Vertex<T>* vertex : vertexSet) {
        vertex->dist=LONG_MAX;
        vertex->path=NULL;
    }
    Vertex<T>* vertex = findVertex(orig);
    vertex->dist=0;

    for (int i = 1; i <= vertexSet.size()-1; ++i) {
        for (Vertex<T>* v : vertexSet) {
            for (Edge<T> edge : v->adj) {
                if (edge.dest->dist > v->dist + edge.weight){
                    edge.dest->dist = v->dist + edge.weight;
                    edge.dest->path = v;
                }
            }
        }
    }
    for (Vertex<T>* v : vertexSet) {
        for (Edge<T> edge : v->adj) {
            if (v->dist + edge.weight < edge.dest->dist)
                std::cout << "There are cycles of negative weight." << std::endl;
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    Vertex<T>* vertex = findVertex(dest);
    std::stack<Vertex<T>*> stack;
    bool reached = false;
    while (vertex->path!=NULL){
        stack.push(vertex);
        vertex=vertex->path;
        if (vertex->info==origin){
            reached=true;
            stack.push(vertex);
            break;
        }
    }

    if(reached){
        while (!stack.empty()){
            res.push_back(stack.top()->info);
            stack.pop();
        }
    }

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this
    std::vector<std::vector<double>> dist(vertexSet.size(),std::vector<double>(vertexSet.size(), INT_MAX));
    std::vector<std::vector<int>> path(vertexSet.size(),std::vector<int>(vertexSet.size(), -1));
    for (int i = 0; i < vertexSet.size(); ++i) {
        for (int j = 0; j < vertexSet.size(); ++j) {
            if(i==j) dist[i][j]=0;
            else{
                for (Edge<T> edge : vertexSet[i]->adj) {
                    if(edge.dest->info==vertexSet[j]->info) {dist[i][j]=edge.weight; break;}
                }
            }
        }
    }

    for (int i = 0; i < vertexSet.size(); ++i) {
        for (int j = 0; j < vertexSet.size(); ++j) {
            if(dist[i][j]!=INT_MAX){
                path[i][j]=i;
            }
        }
    }
    
    for (int k = 0; k < vertexSet.size(); k++)
    {
        // Pick all vertices as source one by one
        for (int i = 0; i < vertexSet.size(); i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (int j = 0; j < vertexSet.size(); j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    bestPaths = path;
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    int origIndex, destIndex;
    for (int i = 0; i < vertexSet.size(); ++i) {
        if(vertexSet[i]->info==orig)  origIndex=i;
        if(vertexSet[i]->info==dest) destIndex=i;
    }

    std::stack<T> stack;
    stack.push(vertexSet[destIndex]->info);

    while (origIndex!=destIndex){
        destIndex=bestPaths[origIndex][destIndex];
        stack.push(vertexSet[destIndex]->info);
    }

    while (!stack.empty()){
        res.push_back(stack.top());
        stack.pop();
    }
    return res;
}


#endif /* GRAPH_H_ */
