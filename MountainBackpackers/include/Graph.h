#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    int ID;
    std::string name;
    int district;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};

struct queueVertex{
    int distance;
    std::vector<vertex *> path;
    bool operator<(const queueVertex& a) const
    {
        return distance > a.distance;
    }
};

struct Comparator {
public:
    bool operator()(const vertex* a, const vertex* b)
    {
        return (a->distance > b->distance);
    }
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistricts();
        void BFTraversalLabel(std::string startingCity, int distID);
        void shortestPath(std::string startingCity,std::string endingCity);
        void shortestDistance(std::string startingCity,std::string endingCity);
        void shortestDistanceRoundTrip(std::string startingCity);
        void time(int i);
        void backpackingTime(std::string trailhead,std::string trailEnd);
        void water(std::string trailhead, std::string trailEnd);
        vertex * findVertex(std::string name);

    protected:
    private:
        std::vector<vertex> vertices;

};
#endif // PROJECT_H
