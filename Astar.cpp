#include "Astar/utils.h"

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
				//node tmp = candidate;
				//while (!(tmp == src))
				//{
				//	tmp.print();
				//	tmp = *find(closedList.begin(), closedList.end(), node(tmp.parentX, tmp.parentY));
				//}
				//src.print();

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
	//set their node values f g h
	//check inputs for errors out of bounds, or blocked source or destination
	node source(0,0);
	source.Gcost = 0;
	node destination(10, 5);
	bool grid[gridX][gridY];
	memset(grid, true, sizeof(grid));
	grid[3][0] = false;
	grid[3][1] = false;
	grid[3][2] = false;
	grid[3][3] = false;
	grid[3][4] = false;
	Asearch(grid, source, destination);
	return 0;
}
