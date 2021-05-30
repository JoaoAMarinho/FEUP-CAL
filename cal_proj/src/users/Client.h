/*
 * Client.h
 */
#ifndef CLIENT_H_
#define CLIENT_H_

#include "../graph/Vertex.h"

template<class T> class Vertex;

class Client {
    static int idTracker;
private:
    const int id;
    Vertex<int> * vertex;   // destination vertex
    int index;
    long int scheduledTime;   // time of delivery in seconds
    int breadsQuantity;
    long int actualDeliveryTime; //seconds of when the delivery happened
    bool delivered;
public:
    /**
     * @method Constructor
     */
    Client();
    /**
     * @param vertex - client vertex
     * @param scheduledTime - expected time to deliver
     * @method Constructor
     */
    Client(Vertex<int> *vertex, double scheduledTime);
    /**
     * @param vertex - client vertex
     * @param scheduledTime - expected time to deliver
     * @param breadsQuantity - desired quantity of breads
     * @method Constructor
     */
    Client(Vertex<int> *vertex, double scheduledTime, int breadsQuantity);
    /**
     * @method Getter
     * @return client vertex
     */
    Vertex<int> *getVertex() const;
    /**
     * @method Getter
     * @return index of the client vertex
     */
    int getIndex() const;
    /**
     * @method Getter
     * @return scheduled time to deliver
     */
    long getScheduledTime() const;
    /**
     * @method Getter
     * @return desired quantity of breads
     */
    int getBreadsQuantity() const;
    /**
     * @method Getter
     * @return id of the client
     */
    const int getId() const;
    /**
     * @method Getter
     * @return actualDeliveryTime attribute
     */
    bool isDelivered() const;

    /**
     * @method Getter
     * @return
     */
    long getActualDeliveryTime() const;
    /**
     * @param breadsQuantity - new desired quantity of breads
     * @method Setter
     */
    void setBreadsQuantity(int breadsQuantity);
    /**
     * @param vertex - new client vertex
     * @method Setter
     */
    void setVertex(Vertex<int> *vertex);
    /**
     * @param index - new index in the vector of vertex
     * @method Setter
     */
    void setIndex(int index);
    /**
     *
     * @param scheduledTime - new schedule time to deliver
     * @method Setter
     */
    void setScheduledTime(long int scheduledTime);
    /**
     *
     * @param delivered - change the delivered flag
     * @method Setter
     */
    void setDelivered(bool delivered);
    /**
     *
     * @param actualDeliveryTime - time the delivery really happened
     * @method Setter
     */
    void setActualDeliveryTime(long actualDeliveryTime);
};


#endif /* Client_ */
