#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <cstring>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input;
    ifstream inFile;
    int i = 0;
    Graph g;

    inFile.open("bestHike.txt");
    vector<string> citiesPath;
    //if(inFile.good([i][j]))
    if(inFile.good())
    {
        if (inFile.is_open())
        {
            string line;
            string city;
            int linecounter = 0;

            while (getline (inFile,line))
            {
                stringstream POIstream(line);

                if (linecounter == 0)
                {
                    getline(POIstream, city, ',');
                    while(getline(POIstream, city, ','))
                    {
                        citiesPath.push_back(city);
                        g.addVertex(city);
                    }
                }
                else
                {
                    string temp;
                    int distValue;
                    int numCounter = 0;
                    getline(POIstream, temp, ',');
                    while(getline(POIstream, temp, ','))
                    {
                        distValue = stoi(temp);
                        if (distValue != 0 && distValue != -1)
                        {
                            g.addEdge(citiesPath[linecounter-1], citiesPath[numCounter], distValue);
                        }
                        numCounter++;
                    }
                }
                linecounter++;
                }

            //g.assignDistricts();

            while(input != "6")
            {
            cout<<"======Main Menu======"<<endl;
            cout<<"1. Print points of interest"<<endl;
            cout<<"2. Find districts"<<endl;
            cout<<"3. Find shortest path"<<endl;
            cout<<"4. Find shortest distance"<<endl;
            cout<<"5. Backpacking"<<endl;
            cout<<"6. Continental divide trail"<<endl;
            cout<<"7. Quit"<<endl;
            cin>>input;

            if(input == "1")
            {
                //g.assignDistricts();  should print -1
                int g;
                for (int i=0; i<citiesPath.size()-1;i++)
                {
                    cout<<citiesPath[i]<<", ";
                    g=i;
                }
                cout<<citiesPath[g+1]<<endl;
            }

            if(input == "2")
            {
                //g.assignDistricts();      should update to district numbers
                g.displayEdges();
            }

            if(input == "3")
            {
                string startingCity;
                string endingCity;
                cout<<"Enter a starting point of interest:"<<endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                cout<<"Enter an ending point of interest:"<<endl;
                getline(cin, endingCity);
                bool bothfound = false;
                for(int i =0; i < citiesPath.size();i++)
                {
                    if (citiesPath[i] ==startingCity)
                    {
                        for(int i = 0; i < citiesPath.size();i++)
                        {
                            if (citiesPath[i] == endingCity)
                            {
                                bothfound = true;
                                g.shortestPath(startingCity, endingCity);
                            }
                        }
                    }
                }
                if (bothfound == false)
                {

                }

            }

            if(input == "4")
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                string endingCity;
                cout << "Enter the destination:" << endl;
                getline(cin, endingCity);
                bool bothfound = false;
                for (int i=0; i < citiesPath.size(); i++){
                    if (citiesPath[i] == startingCity){
                        for (int i=0; i < citiesPath.size(); i++){
                            if (citiesPath[i] == endingCity){
                                bothfound = true;
                                g.shortestDistance(startingCity, endingCity);
                            }
                        }
                    }
                }
                if (bothfound == false){
                    cout << "One or more points of interest doesn't exist, or it is not in our database." << endl;
                }
            }

            if (input == "5")
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < citiesPath.size(); i++)
                {
                    if (citiesPath[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The point of interest you entered is not in our database." << endl;
                }
                else{
//                l.Dish(startingCity);
                }
            }

            if (input=="6")
            {
                cout<<"Enter a starting point of interest:"<<endl;
                //cout<<distance;
            }

        }

        inFile.close();
        cout<<"Goodbye!"<<endl;
        return 0;
        }
    }
}
