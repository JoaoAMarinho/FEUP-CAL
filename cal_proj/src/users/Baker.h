/*
 * Baker.h
 */
#ifndef BAKER_H_
#define BAKER_H_

#include "../graph/Edge.h"
#include <string>
#include "./Client.h"

template<class T> class Edge;
class Client;

class Baker {
    static int idTracker;
    const int id;           // id
    long int startTime;       // bakery departure utils
    long int actualStartTime;
    int capacity;           // amount of bread he can deliver
    long int deliveryTime;    // seconds spent in the processing of a delivery
    vector<Edge<int>*> path; // contains edges of the bakers path
    vector<Client *> clientsAttended; // contains the clients attended by the baker in order
    long int pathDuration = 0;
    int breadsDelivered = 0;

public:
    long int currTime = -1;

    /**
     * @method Constructor
     */
    Baker();
    /**
     * @param startTime - the time the baker starts working
     * @param deliveryTime - time spent in a delivery
     * @method Constructor
     */
    Baker(long int startTime, long int  deliveryTime);
    /**
     * @param startTime - the time the baker starts working
     * @param capacity - the amount of breads which he can deliver
     * @param deliveryTime - time spent in a delivery
     * @method Constructor
     */
    Baker(long int startTime, int capacity, long int  deliveryTime);
    /**
     * @method Getter
     * @return the time the baker starts working
     */
    long int getStartTime() const;
    /**
     * @method Getter
     * @return the amount of breads which the baker can deliver
     */
    int getCapacity() const;
    /**
     * @method Getter
     * @return time spent to process a delivery
     */
    long int getDeliveryTime() const;
    /**
     * @method Getter
     * @return vector with the Edges of the full path the baker does
     */
    vector<Edge<int> *> &getPath();
    /**
     * @method Getter
     * @return the real time the baker leaves the bakery
     */
    long getActualStartTime() const;
    /**
     * @method Getter
     * @return the time spent in the full path
     */
    long getPathDuration() const;
    /**
     * @method Getter
     * @return the baker id
     */
    const int getId() const;
    /**
     * @method Getter
     * @return vector with the clients attended by the baker
     */
    vector<Client *> &getClientsAttended();
    /**
     * @method Getter
     * @return amount of breads delivered
     */
    int getBreadsDelivered() const;
    /**
     * @method Setter
     * @param clientsAttended - new vector of clients attended
     */
    void setClientsAttended(const vector<Client *> &clientsAttended);
    /**
     * @method Setter
     * @param startTime - new time the baker starts working
     */
    void setStartTime(long int startTime);
    /**
     * @method Setter
     * @param capacity - new capacity of breads which can be delivered
     */
    void setCapacity(int capacity);
    /**
     * @method Setter
     * @param deliveryTime - new time it takes the baker to process a delivery
     */
    void setDeliveryTime(long int deliveryTime);
    /**
     * @method Setter
     * @param path - new vector with the Edges of the full path the baker does
     */
    void setPath(const vector<Edge<int> *> &path);
    /**
     * @method Setter
     * @param actualStartTime - new time which the baker leaves the bakery
     */
    void setActualStartTime(long actualStartTime);
    /**
     * @method Setter
     * @param pathDuration - new time it takes the baker to deliver to all clients attended
     */
    void setPathDuration(long pathDuration);
    /**
     * @param client - client to be added to the attended client vector
     */
    void addAttendedClient(Client * client);
    /**
     * Removes the last client in the attended client vector
     */
    void removeLastAttendedClient();
    /**
     *
     * @param breads - amount of breads to be added to the breadsDelivered attribute
     */
    void addBreadsDelivered(int breads);
};


#endif /* Baker_ */
