#include "Graph.h"
#include <vector>
#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

Graph::Graph()
{
//constractor
}

Graph::~Graph()
{
    //dtor
}

vertex * Graph::findVertex(std::string name) //find verticies
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}

void Graph::addEdge(string v1, string v2, int weight)//creates edges
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n)//insert vertices
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == n)
        {
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        v.ID = vertices.size();
        vertices.push_back(v);
    }
}

void Graph::displayEdges()//print connection between cities
{
    for(int i = 0; i < vertices.size(); i++)
    {
        cout<< vertices[i].district <<":" <<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}

void Graph::assignDistricts()// create district
{
    int distID = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].district == -1)
        {
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
    }
}

void Graph::BFTraversalLabel(std::string trailhead, int distID)//function to travers between the verticies
{
    queue<vertex*> q;
    // Label all as unvisited.
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
    // Find the starting node and enqueue it.
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == trailhead)
        {
            vertices[i].visited = true;
            q.push(&vertices[i]);
            vertices[i].district = distID;
            break;
        }
    }
    while (q.empty() != true)
    {
        vertex *u = q.front();
        q.pop();
        for(int i = 0; i < u->adj.size(); i++)
        {
            if (u->adj[i].v->visited == false)
            {
                u->adj[i].v->visited = true;
                u->adj[i].v->district = distID;
                q.push(u->adj[i].v);
            }
        }
    }
}

void Graph::shortestPath(std::string trailhead,std::string trailEnd)//find shortest path
{

    vertex *start = findVertex(trailhead);
    vertex *end = findVertex(trailEnd);

    if (start == NULL || end == NULL)
    {
        cout << "One or more trails doesn't exist,or it is not in our Database"<< endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "No safe trails between points of interest" << endl;
        return;
    }
    ///*
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }
    //*/

    // Initialization
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
    start->visited = true;
    queueVertex qv;
    qv.distance = 0;
    qv.path.push_back(start);
    queue<queueVertex> q;
    q.push(qv);

    while (q.empty() != true)
    {
        qv = q.front();
        q.pop();

        for(int i = 0; i < qv.path.back()->adj.size(); i++)
        {
            if (qv.path.back()->adj[i].v->visited == false)
            {
                // Create a new queueVertex with updated path and distance.
                vector<vertex *> path = qv.path;
                qv.path.back()->adj[i].v->visited = true;
                int distance = qv.distance + 1;

                path.push_back(qv.path.back()->adj[i].v);
                queueVertex temp;
                temp.path = path;
                temp.distance = distance;

                // If we have found the correct path
                if (qv.path.back()->adj[i].v == end)
                {
                    cout<<"===PATH==="<<endl;
                    cout<<"district: " << temp.distance;
                    for (int j = 0; j < temp.path.size(); j++)
                        cout <<", "<< temp.path[j]->name;
                    cout << endl;
                    return;
                }
                else
                    q.push(temp);
            }
        }
    }
    return;
}

// Dijkstra
void Graph::shortestDistance(std::string trailhead,std::string trailEnd)//find shortest distance
{
    // Search from "end" city to "start" city so that the path prints path in correct order.
    vertex * start = findVertex(trailEnd);
    vertex * end = findVertex(trailhead);

    if (start == NULL || end == NULL)
    {
        cout << "One or more trails doesn't exist,or it is not in our Database" << endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "No safe hiking trail" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    // Initialization
    int previous[vertices.size()];
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        previous[vertices[i].ID] = -1;
        vertices[i].distance = INT_MAX;
    }
    priority_queue<vertex * ,vector<vertex *>, Comparator> q;
    start->distance = 0;
    q.push(start);
    vertex * cur;

    while (q.empty() != true)
    {
        cur = q.top();
        q.pop();
        for(int i = 0; i < cur->adj.size(); i++)
        {
            if (cur->adj[i].v->visited == false)
            {
                int distance = cur->distance + cur->adj[i].weight;
                if (distance < cur->adj[i].v->distance)
                {
                   cur->adj[i].v->distance = distance;
                   previous[cur->adj[i].v->ID] = cur->ID;
                }
                q.push(cur->adj[i].v);
            }
        }
        cur->visited = true;
        if (cur == end)
        {
            int i = cur->ID;
            int c=cur->distance;
            cout<<"===PATH==="<<endl;
            cout<<"Distance: "<< cur->distance;
            cout << "," << cur->name;
            while (previous[i] != -1)
            {
                cout << "," << vertices[previous[i]].name;
                i = vertices[previous[i]].ID;
            }
            cout << endl;
            break;
        }
    }
    return;
}

void Graph::backpackingTime(std::string trailhead,std::string trailEnd)
{
    vertex * start = findVertex(trailEnd);
    vertex * end = findVertex(trailhead);

    if (start == NULL || end == NULL)
    {
        cout << "One or more trails doesn't exist,or it is not in our Database" << endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "No safe hiking trail" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    // Initialization
    int previous[vertices.size()];
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        previous[vertices[i].ID] = -1;
        vertices[i].distance = INT_MAX;
    }
    priority_queue<vertex * ,vector<vertex *>, Comparator> q;
    start->distance = 0;
    q.push(start);
    vertex * cur;

    while (q.empty() != true)
    {
        cur = q.top();
        q.pop();
        for(int i = 0; i < cur->adj.size(); i++)
        {
            if (cur->adj[i].v->visited == false)
            {
                int distance = cur->distance + cur->adj[i].weight;
                if (distance < cur->adj[i].v->distance)
                {
                   cur->adj[i].v->distance = distance;
                   previous[cur->adj[i].v->ID] = cur->ID;
                }
                q.push(cur->adj[i].v);
            }
        }
        cur->visited = true;
        if (cur == end)
        {
            int i = cur->ID;
            int c=cur->distance;
            cout << cur->distance;
            cout << "," << cur->name;
            while (previous[i] != -1)
            {
                //cout << "," << vertices[previous[i]].name;
                i = vertices[previous[i]].ID;
            }
            cout << endl;
            time(c);
            break;
    }
}
}

void Graph::time(int i)//Using as a parameter the km from the above function convert it in time of traveling
{
    int minutes2 = i/100;
    int minutes = minutes2*60;
    int convert_to_hours;
    convert_to_hours = minutes / 60;
    int remainder2;
    remainder2 = minutes % 60;
    cout<<endl;
    cout<<"Time of Hike"<<endl;
    cout<<"=================="<<endl;
    cout<<"The time to get to your destination by foot is ";
    if (convert_to_hours < 1)
    {
        cout << "less than an hour." << endl;
    }
    else
    {
        if (convert_to_hours > 1)
            cout << "approximately " << convert_to_hours << " hours ";
        else
            cout << "approximately " << convert_to_hours << " hour ";
        if (remainder2 != 0)
        {
            if (remainder2 > 1)
                cout << "and " << remainder2 << "minutes." << endl;
            else
                cout << "and " << remainder2 << "minute." << endl;
        }
    }

    cout<<endl;
}

// Traveling Salesman
void Graph::shortestDistanceRoundTrip(std::string trailhead)
{
    vertex * start = findVertex(trailhead);
    if (start == NULL)
    {
        cout << "One or more trails doesn't exist,or it is not in our database." << endl;
        return;
    }

    if (start->district == -1)
    {
        cout << "Please identify the trails before checking distances." << endl;
        return;
    }
    // Initialization
    queueVertex qv;
    qv.distance = 0;
    qv.path.push_back(start);
    queue<queueVertex> q;
    q.push(qv);
    std::priority_queue<queueVertex> possibleSolutions;

    while (q.empty() != true)
    {
        qv = q.front();
        q.pop();
        if (qv.path.size() == vertices.size())
        {
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {
                if (qv.path.back()->adj[i].v == start)
                {
                    qv.distance += qv.path.back()->adj[i].weight;
                    qv.path.push_back(qv.path.back()->adj[i].v);
                    possibleSolutions.push(qv);
                }
            }
        }

        else
        {
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {
                if (std::find(qv.path.begin(), qv.path.end(),qv.path.back()->adj[i].v) == qv.path.end())
                {
                    vector<vertex *> path = qv.path;
                    int distance = qv.distance + qv.path.back()->adj[i].weight;
                    path.push_back(qv.path.back()->adj[i].v);
                    queueVertex temp;
                    temp.path = path;
                    temp.distance = distance;
                    q.push(temp);
                }
            }
        }
    }
    if (!possibleSolutions.empty())
    {
        queueVertex solution = possibleSolutions.top();
        cout << solution.distance << endl;
        cout << solution.distance;
        for (int j = 0; j < solution.path.size(); j++)
            cout << "," << solution.path[j]->name;
        cout << endl;
    }
    else
        cout << "No possible path." << endl;
    return;
};
/*
void Graph::water(string trailhead, string trailEnd)
{

    if(distance<="10")
    {
        cout<<"All you need to bring a nalgene bottle!"<<endl;
    }
    else if (distance>"10" && distance<"50")
    {
        cout<<"Make sure to bring at least 4 liters of water. Bringing a water filter is recommended."<<endl;
    }
    else
    {
        cout<<"Make sure to bring at least 4 liters of water. You should make sure to bring a water filter, and always have at least two nalgenes filled."<<endl;
    }

};
*/
