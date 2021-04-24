#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
    // TODO

    // Instantiate GraphViewer
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    //i.
    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300)); // Create node
    node0.setColor(GraphViewer::BLUE);

    //ii.
    Node &node1 = gv.addNode(1, sf::Vector2f(400, 300));
    node1.setColor(GraphViewer::RED);

    //iii.
    // for bidirectional edges
    Edge &edge1 = gv.addEdge(0,node0,node1,Edge::EdgeType::UNDIRECTED);
    // for directed edges
    //Edge &edge1 = gv.addEdge(idEdge,idSource,idDestination,Edge::EdgeType::DIRECTED);

    //iv.
    //gv.removeNode(0);

    //v.
    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));

    //vi.
    //Edge &edge2 = gv.addEdge(1,node2,node0,Edge::EdgeType::DIRECTED);

    //vii.
    //node2.setLabel("This is a vertex");

    //viii.
    //edge2.setLabel("This is an edge");

    //ix.
    node2.setColor(GraphViewer::GREEN);

    //x.
    for(Edge *edge: gv.getEdges())
        edge->setColor(GraphViewer::YELLOW);

    //xi.
    //gv.setBackground("../TP7_graphviewer/resources/background.png");

    // Create window
    gv.createWindow(600, 600);
    // Join viewer thread (blocks till window closed)
    gv.join();
}
