Glacier National Park Hikes
Project Summary
      Our final project creates a means to find the shortest distances and paths to hiking locations in Montana’s Glacier National Park. The code’s menu offers multiple options which print out the points of interest, find the shortest path and shortest distance, and offers the shortest path round trip from any destination.  A large portion of our project was created using Graphs. We started by building functions that found the needed vertices and created the edges. We also have functions that insert vertices, print the connections between cities, and create districts. To find the shortest distance, we incorporated Dijkstra’s algorithm. There is a function in our code that calculates the time it would take for a hiker to traverse a mountain, using km as a parameter and converting it to time. Our last function calculates the shortest distance it would take to make a round trip from any destination by implementing the Traveling Salesman algorithm.

How to Run
      When our code is first run, a menu screen is presented to the user. The user then has 6 options depending on their preference. “1” displays all the available points of interest. “2” will display the districts on the menu. “3” takes two inputs, the starting point and the ending point, and prints the shortest path available. These inputs need to be within the text file displayed or the user will receive a message asking to follow the parameters of the program. “4” is similar to “3”, however it prints the path in a numerical distance. “5” asks for a single input from the user, the preferred starting city, the program will then calculate the shortest path for a round trip. “6” will calculate the amount of water needed to traverse from origin to destination. 

Dependencies
      Attached to the file is a text file with all the destinations and is needed to run the program. There are no specific system requirements for our program and it can run on any operating system. All that is needed is a code running program to run the code. 

Group Members
      This project was made by Carly Romig and Daniel Zhou from Upendra Sabnis’ 8am Recitation.

Open Issues/Bugs
	We still need to figure out how to implement the time function in the Graph class into the menu. We would also like to implement a simple water function that calculates how much water they would like to bring with them.
