#include "utils.h"
#include <chrono>
using namespace std::chrono;
void Asearch(bool grid[gridX][gridY], node src, node dest)
{
	vector<node> openList; // a list for the nodes of interest to be chosen from
	vector<node> closedList; //a list of the nodes that have been explored already
	openList.push_back(src);
	while (!openList.empty())
	{
		//seelct the node with the least cost from the open list and explore its neighbors
		auto current_node_itr = min_element(openList.begin(), openList.end());
		node current_node = *current_node_itr;
		vector<node> current_candidates = current_node.getNeighbors(dest);
		openList.erase(current_node_itr);
		for (auto it = current_candidates.begin(); it != current_candidates.end(); it++)
		{
			//for each neighbor, check if it's the destination
			//check if the cell has already been explored or
			//if it's reachable by another node with a lower cost path if so ignore it
			//otherwise add it to the openlist
			node candidate = *it;
			//check if destination
			if (candidate == dest)
			{
				cout << "found destiantion" << endl;
				closedList.push_back(current_node);
				trace(closedList,candidate,src); //display the selected path
				return;
			}
			//check if the cell is not blocked
			else if (!grid[candidate.x][candidate.y])
			{
				continue;
			}
			//check if the cell is already closed
			else if (match(closedList, candidate))
			{
				continue;
			}
			//check if the cell is in the open list (reachable from another node)
			//this will add the node with the new route but does not remove the old one from the list
			//remember to remove 
			else if (match(openList, candidate))
			{
				continue;
			}
			else
				openList.push_back(candidate);
		}
		closedList.push_back(current_node);
	}
	cout << "destination not found"; //algorithm has finished and goal was not found
}


int main(void)
{
	//get binary occupancy grid 
	//get source and destination
	//set source cost
	//check inputs for errors out of bounds, or blocked source or destination
	//start search
	bool grid[gridX][gridY];
	memset(grid, true, sizeof(grid));
	cout << "input the obstacles of the map" << endl;
	cout << "hit q to exit" << endl;
	int x=0,y=0;
	string input;
	while (1)
	{
		cout << "format: x y >>  ";
		getline(cin, input);
		if (input == "q") break;
		tokenize(&x, &y, input);
		grid[x][y] = false;
	}
	cout << "input the source node >> ";
	getline(cin, input);
	tokenize(&x, &y, input);
	node source(x, y);
	source.Gcost = 0;
	cout << "input the destination node >> ";
	getline(cin, input);
	tokenize(&x, &y, input);
	cout << endl;
	node destination(x, y);
	if (!grid[source.x][source.y] || !grid[destination.x][destination.y])
	{
		cout << "source or destination input blocked" << endl;
		return -1;
	}
	else
	{
		auto start = high_resolution_clock::now();
		Asearch(grid, source, destination);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout<<"time to search: "<<duration.count()<<endl;
	}
	return 0;
}
