#ifndef CAL_PROJ_DATALOADER_H
#define CAL_PROJ_DATALOADER_H


#include "../graph/Graph.h"
#include "../Application.h"
#include "../utils/utils.h"
#include <string>

class DataLoader {

public:
    /**
     * Input for the single delivery problem
     * @return application created
     */
    Application oneDeliveryInput();
    /**
     * Input for the multiple delivery problem
     * @return application created
     */
    Application multipleDeliveryInput();
    /**
     * Input for the multiple delivery and multiple bakers problem
     * @return application created
     */
    Application multipleBakersDeliveryInput();
    /**
     * Input for the multiple delivery and multiple bakers with limited quantity problem
     * @return application created
     */
    Application multipleBakersLimitedDeliveryInput();
    /**
     * Inputs the nodes and edges to a grapth saved in the param application
     * @param application - application to save the input graph
     */
    void InputGraph(Application * application);
    /**
     * @param graph - graph to be verified if has the inputted bakery
     * @return pair with the vertex of the bakery and its index from the graph
     */
    pair<Vertex<int>*, int> InputBakery(const Graph<int> &graph);
    /**
     * @param graph - grapth with vertex locations
     * @param n - number of clients to be inputted
     * @param application - application with tolerances
     * @return vector with clients to deliver
     */
    vector<Client *> InputClients(const Graph<int> &graph, int n,const Application &application);
    /**
     * @param application - to set the inputted tolerances
     */
    void InputTolerances(Application &application);
    /**
     * @param n - number of bakers to be inputted
     * @return vector with inputted bakers
     */
    vector<Baker *> InputBaker( int n);
    /**
     * @param n - number of bakers to be inputted
     * @return vector with inputted bakers which have a limited amount of breads to deliver
     */
    vector<Baker *> InputBakerWithQuantity(const int n);
    /**
     * @param graph - graph to be validated
     * @return true if the graph is valid and can deliver to at least one client
     */
    bool validGraph(Graph<int> &graph);
};

#endif //CAL_PROJ_DATALOADER_H
