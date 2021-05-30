#include "GraphLoader.h"

using namespace std;
using Node = GraphViewer::Node;
using EdgeGV = GraphViewer::Edge;

GraphLoader::GraphLoader(Graph<int> &graph) {
    gv = new GraphViewer;
    int graphSize = graph.getVertexSet().size();

    gv->setCenter(sf::Vector2f(graph.getVertexSet().at(graphSize/2)->getX(), graph.getVertexSet().at(graphSize/2)->getY()));

    for(Vertex<int>* vertex: graph.getVertexSet()){
        gv->addNode(vertex->getInfo(), sf::Vector2f(vertex->getX(), vertex->getY())).setLabel(to_string(vertex->getInfo()));
    }

    for(Vertex<int>* vertex: graph.getVertexSet()){
        for(Edge<int> edge: vertex->getAdj()){
            gv->addEdge(edge.getId(),gv->getNode(vertex->getInfo()),gv->getNode(edge.getDest()->getInfo()), EdgeGV::EdgeType::DIRECTED);
        }
    }

    gv->createWindow(1600, 900);
}

void GraphLoader::setBakery(int idBakery) {
    gv->getNode(idBakery).setColor(GraphViewer::LIGHT_GRAY);
}


void GraphLoader::join() {
    gv->join();
}

void GraphLoader::setPath(vector<Edge<int>*> &path) {
    for(int i=0; i<path.size(); i++){
        gv->getEdge(path.at(i)->getId()).setColor(getCurrColor());
        usleep(path.at(i)->getWeight() * 100000);
    }
}

void GraphLoader::setClients(const vector<int> &clientsID) {
    for(int id: clientsID){
        gv->getNode(id).setColor(GraphViewer::GREEN);
    }
}

sf::Color GraphLoader::getCurrColor() {
    return colors.at(currColor);
}

void GraphLoader::nextColor() {
    currColor = (currColor+1) % colors.size();
}
