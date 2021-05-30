#ifndef CAL_PROJ_GRAPHLOADER_H
#define CAL_PROJ_GRAPHLOADER_H

#include <fstream>
#include "graphviewer.h"
#include "../graph/Graph.h"
#include <string>
#include <unistd.h>

class GraphLoader{
private:
    GraphViewer* gv;
    vector<sf::Color> colors{GraphViewer::MAGENTA,GraphViewer::YELLOW,GraphViewer::CYAN,GraphViewer::GREEN,GraphViewer::PINK,GraphViewer::BLUE,GraphViewer::ORANGE};
    int currColor = 0;
public:
    /**
     * @param graph - graph to be loaded to the graph viewer
     * @method Constructor
     */
    GraphLoader(Graph<int> &graph);
    /**
     * @method Getter
     * @return current Edges color
     */
    sf::Color getCurrColor();
    /**
     * @method Setter
     * @param idBakery - new bakery vertex
     */
    void setBakery(int idBakery);
    /**
     * @method Setter
     * @param path - new path to be drawn in the graph viewer
     */
    void setPath(vector<Edge<int> *> &path);
    /**
     * @method Setter
     * @param clientsID - new vector with the id's of the client vertexes
     */
    void setClients(const vector<int> &clientsID);
    /**
     * Join the window main thread.
     */
    void join();
    /**
     * Changes the currColor attribute to the next color in the colors vector
     */
    void nextColor();
};


#endif //CAL_PROJ_GRAPHLOADER_H
