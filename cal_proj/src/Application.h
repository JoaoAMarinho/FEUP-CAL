#ifndef CAL_PROJ_APPLICATION_H
#define CAL_PROJ_APPLICATION_H


#include "graph/Graph.h"
#include "users/Baker.h"
#include <string>
#include <ostream>

class Application {

private:
    Graph<int> graph;
    Graph<int> invertedGraph;
    vector<Baker *> bakerSet;            // baker set
    Vertex<int>* bakery;                  // bakery vertex, origin
    int bakeryIndex;
    vector<Client *> clientSet;          // client set
    int previousTolerance;
    int afterTolerance;
    bool algorithm;                        //True if Floyd, false if Dijkstra
    bool capacityRestriction = false;

    /**
     * Removes the vertexes which the bakery can not reach using the visited attribute of each one
     */
    void removeNotVisitedVertex();
    /**
     * Removes the vertexes which can not reach the bakery using the visited attribute of each one
     */
    void removeInvertedNotVisitedVertex();
    /**
     * Removes the vertexes which the bakery can not reach using the floyd's results
     * @param bestPaths - 2D vector which contains the previous vertex info for a certain path
     * @param distances - 2D vector which contains the distance/weight for a certain path
     * @param vec - distances from each vertex to the bakery
     */
    void removeNotReachedFromBakeryFloyd(vector<vector<int>> &bestPaths, vector <vector<double>> &distances,
                                         vector<double> &vec);
    /**
     * Removes the vertexes which can not reach the bakery using the floyd's results
     * @param bestPaths - 2D vector which contains the previous vertex info for a certain path
     * @param distances - 2D vector which contains the distance/weight for a certain path
     * @param vec - distances from each vertex to the bakery
     */
    void removeNotReachedToBakeryFloyd(vector<vector<int>> &bestPaths, vector <vector<double>> &distances,
                                       vector<double> &vec);
    /**
     * Converts a vector of vertex infos to the path of edges traversed
     * @param path - vector with vertex infos
     * @return vector with edges traversed
     */
    vector<Edge<int> *> & convertNodeToEdges(vector<int> path);
    /**
     * TODO
     */
    void setDeliveryPathHours();
    /**
     * Function that solves the multiple delivery problem using Dijkstra with 2 approaches
     */
    void multipleDeliveryDijkstra();
    /**
     * Finds the baker path for multiple deliveries using a greedy approach
     */
    void multipleDeliveryDijkstraGreedy();
    /**
     * Finds the baker path for multiple deliveries using a backtracking approach
     */
    void multipleDeliveryDijkstraBacktracking();
    /**
     * Recursive function that assist the multipleDeliveryDijkstraBacktracking function
     * @param sortedClients - vector with available clients
     * @param currClients - vector with current attended clients
     * @param currPathTime - current time it takes to traverse the full path
     * @param currTime - current time of delivery
     * @param bestClients - vector with best order of clients to deliver
     * @param bestPathTime - best time to traverse the bestClients vector
     */
    void dijkstraBacktracking(vector<Client * > sortedClients ,vector<Client * > currClients, long int currPathTime,
                              long int currTime ,vector<Client * > &bestClients, long int &bestPathTime);
    /**
     * Sets the paths times for the current baker with the client vector passed as parameter
     * @param baker - current baker
     * @param clients - vector with clients that the baker attends
     */
    void setDeliveryPathHoursWithDijkstra(Baker *baker, vector<Client * > &clients);
    /**
     * Finds the bakers path for multiple deliveries using a backtracking approach
     */
    void multipleBakersDeliveryDijkstraBacktracking();
    /**
     * Recursive function that assist the multipleBakersDeliveryDijkstraBacktracking function
     * @param sortedClients - vector with available clients
     * @param currBakers - vector with current available bakers
     * @param bestBakers - vector with the best available bakers
     */
    void solveDijkstraBacktrackingMultipleBakers(vector<Client * > sortedClients ,
                                                 vector<Baker> currBakers, vector<Baker> &bestBakers);
    /**
     * Function that solves the multiple delivery problem using Floyd with 2 approaches
     */
    void multipleDeliveryFloyd();
    /**
     * Finds the baker path for multiple deliveries using a greedy approach
     */
    void multipleDeliveryFloydGreedy();
    /**
     * Finds the bakers path for multiple deliveries using a backtracking approach
     * @param bakerIndex - index of baker in the bakerSet
     * @param clientVec - clients available to be attended
     */
    void multipleDeliveryFloydBacktracking(int bakerIndex, vector<Client*> clientVec);
    /**
     * Recursive function that assist the multipleDeliveryFloydBacktracking function
     * @param test - current attended client infos in the recursive call
     * @param currClient - current client index
     * @param res - result of backtracking algorithm with client infos in order of attendance
     * @param canUse - vector with boolean values to whether the client can or not be attended
     * @param currTime - current time of delivery
     * @param clientVec - vector with all clients
     * @param timeToDeliver - time it takes a certain baker to process a delivery
     * @return true if solution found
     */
    bool solveFloydBacktracking(vector<int> &test, int currClient, vector<int> &res,
                                vector<bool> canUse, long int currTime,
                                const vector<Client *>& clientVec,const int timeToDeliver);
    /**
     * Finds the bakers path for multiple deliveries using a backtracking approach
     */
    void multipleBakersDeliveryFloydBacktracking();
    /**
     * Recursive function that assist the multipleDeliveryFloydBacktracking function having in consideration the
     * capacity of each baker
     * @param test - current attended client infos in the recursive call
     * @param currClient - current client index
     * @param res - result of backtracking algorithm with client infos in order of attendance
     * @param canUse - vector with boolean values to whether the client can or not be attended
     * @param currTime - current time of delivery
     * @param currQuantity - current capacity of the baker being tested
     * @param clientVec - vector with all clients
     * @param timeToDeliver - time it takes a certain baker to process a delivery
     * @return true if solution found
     */
    bool solveLimitedFloydBacktracking(vector<int> &test, int currClient, vector<int> &res,
                                       vector<bool> canUse, long int currTime, int currQuantity,
                                       const vector<Client *> &clientVec,const int timeToDeliver);
    /**
     * Adds a path from a source to a destination vertex of a baker
     * @param source - index of source vertex
     * @param dest - index of destination vertex
     * @param baker - baker to be added the new path
     * @return time it took to traverse the new path
     */
    long int addFloydPathToBaker( int source, int dest, Baker* baker);
    /**
     * Adds a path from a source to a client vertex of a baker and sets that client time attributes
     * @param source - index of source vertex
     * @param baker - baker to be added the new path
     * @param currTime - current time of delivery
     * @param client - pointer to client which the baker will deliver to
     */
    void addClientPathToBaker(int source, Baker* baker, long int &currTime, Client* client);
    /**
     * @param baker - baker which is being tested
     * @return vertex in which the baker is currently at
     */
    Vertex<int> * getCurrBakerVertex(Baker * baker);
    /**
     * Sorts the clientSet vector in order of time
     * @return new sorted clients vector
     */
    vector<Client *> & sortedClients();
    /**
     * Sorts the bakerSet vector in order of start time
     * @return new sorted bakers vector
     */
    vector<Baker>& sortedBakers();
    /**
     * Removes from clientVec all the occurrences from clients
     * @param clients - clients to be removed from the clientVec
     * @param clientVec - vector which will be removed the clients in clients
     */
    static void removeFromClientSet(vector<Client *> &clients, vector<Client *> &clientVec);
    /**
     * Verifies if the vec1 has a bigger quantity of breads than the vec2, having into account the clients vector
     * @param vec1 - infos of clients
     * @param vec2 - infos of clients
     * @param clients - clients vector
     * @return true if the clients in vec1 have a bigger quantity of bread than vec2, false otherwise
     */
    static bool biggerQuantity(const vector<int> &vec1, const vector<int> &vec2, const vector<Client *> &clients);


public:
    /**
     * @method Constructor
     */
    Application();

    //Getters
    /**
     * @method Getter
     * @return graph
     */
    Graph<int> &getGraph();
    /**
     * @method Getter
     * @return bakery vertex
     */
    Vertex<int> *getBakery() const;
    /**
     * @method Getter
     * @return vector with available bakers
     */
    vector<Baker *> &getBakerSet();
    /**
     * @method Getter
     * @return time of after tolerance for each delivery
     */
    int getAfterTolerance() const;
    /**
     * @method Getter
     * @param vertexID - info of the vertex to be found
     * @return pointer to client with the param info
     */
    Client * getClientInVertex(int vertexID);
    /**
     * @method Getter
     * @return vector with client id's
     */
    vector<int> getClientsID() const;
    /**
     * @method Getter
     * @return first start time of all bakers
     */
    long int getFirstBakerStart() const;
    /**
     * @method Getter
     * @param path - vector with edges to calculate the time
     * @return time it takes to traverse all the edges
     */
    long int getPathTime(vector<Edge<int> *> & path);

    //Setters
    /**
     * @method Setter
     * @param previousTolerance - new previous tolerance
     */
    void setPreviousTolerance(int previousTolerance);
    /**
     * @method Setter
     * @param afterTolerance - new after tolerance
     */
    void setAfterTolerance(int afterTolerance);
    /**
     * @method Setter
     * @param bakery - new bakery vertex
     */
    void setBakery(Vertex<int> *bakery);
    /**
     * @method Setter
     * @param bakeryIndex - bakery index in the vertexSet
     */
    void setBakeryIndex(int bakeryIndex);
    /**
     * @method Setter
     * @param bakerSet - new bakers vector
     */
    void setBakerSet(vector<Baker *> bakerSet);
    /**
     * @method Setter
     * @param clientSet - new clients vector
     */
    void setClientSet(vector<Client *> clientSet);
    /**
     * @method Setter
     * @param algorithm - new algorithm flag value
     */
    void setAlgorithm(bool algorithm);
    /**
     * @method Setter
     * @param capacityRestriction - new capacityRestriction flag value
     */
    void setCapacityRestriction(bool capacityRestriction);
    /**
     * @method Setter
     * @param graph - new graph
     */
    void setGraph(const Graph<int> &graph);
    /**
     * @method Setter
     * @param invertedGraph - new inverted graph
     */
    void setInvertedGraph(const Graph<int> &invertedGraph);

    //Problems
    /**
     * Run one delivery problem
     */
    void oneDeliveryRun();
    /**
     * Run multiple delivery problem
     */
    void multipleDeliveryRun();
    /**
     * Run multiple delivery with multiple bakers problem
     */
    void multipleBakersDeliveryRun();
    /**
     * Run multiple delivery with limited bakers problem
     */
    void multipleBakersLimitedDeliveryRun();

    //Pre process
    /**
     * Pre processes the graph, making it strongly connected,  using a BFS algorithm
     */
    void preProcessGraphBFS();
    /**
     * Pre processes the graph, making it strongly connected, using the Floyd Warshall algorithm
     */
    void preProcessGraphFloyd();

    //Final print function
    /**
     * @return string with all the info about the bakers paths
     */
    std::string printPath();

};

#endif //CAL_PROJ_APPLICATION_H
