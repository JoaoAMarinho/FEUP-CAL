#include "graphviewer.h"
#include <fstream>
#include <sstream>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex3() {
    // TODO

    //a.
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(300, 300));

    //Read nodes
    ifstream nodeFile("../TP7_graphviewer/resources/map1/nodes.txt");
    string str;
    getline(nodeFile, str);
    stringstream ss(str);
    int i;
    ss >> i;

    for (;i>0; --i) {
        getline(nodeFile, str);
        stringstream sstream(str);
        int id, x, y;
        sstream >> id >> x >> y;
        gv.addNode(id,sf::Vector2f(x, y));
    }
    nodeFile.close();

    //Read edges
    ifstream edgeFile("../TP7_graphviewer/resources/map1/edges.txt");
    getline(edgeFile, str);
    ss = stringstream (str);
    ss >> i;

    for (;i>0; --i) {
        getline(edgeFile, str);
        stringstream sstream(str);
        int id, source, dest;
        sstream >> id >> source >> dest;
        gv.addEdge(id,gv.getNode(source),gv.getNode(dest),GraphViewer::Edge::DIRECTED);
    }
    edgeFile.close();

    gv.createWindow(600, 600);
    gv.join();

}

