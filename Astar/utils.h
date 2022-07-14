#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define gridX 11
#define gridY 6
int euclidean_distance(int x1, int y1, int x2, int y2);


class node
{
public:
	//x,y is the location of the node and parents denotes how to reach this node
	int x;
	int y;
	int parentX;
	int parentY;

	//could be integers with the current implementation but left floats for generalizing cost convention
	float Gcost; //distance from source
	float Hcost; //distance from destination
	float Fcost; //g+h

	node(int a = NULL, int b = NULL)
	{
		x = a;
		y = b;
		parentX = NULL;
		parentY = NULL;
		Gcost = FLT_MAX;
		Hcost = FLT_MAX;
		Fcost = FLT_MAX;
	}

	//operator overlaoding
	bool operator < (node n) const
	{
		return (this->Fcost < n.Fcost);
	}
	bool operator > (node n) const
	{
		return (this->Fcost > n.Fcost);
	}
	bool operator == (node n) const
	{
		return ((this->x == n.x) && (this->y == n.y));
	}

	// calculation of euclidean distance from a node to the destination
	void calHCost(node dest)
	{
		Hcost = (float)sqrt(pow((this->x - dest.x), 2) + pow((this->y - dest.y), 2)) * 10;
	}
	void calFcost()
	{
		Fcost = Gcost + Hcost;
	}

	//get the 8 nearest neighbors to the current node
	//initialize their parents to the current node
	//calculate costs accordingly and return the neighbors in a vector
	vector<node> getNeighbors(node goal)
	{
		vector <node> nodes;
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (i == this->x && j == this->y) continue; //skip the current node from the loop
				else if (i<0 || i>=gridX || j<0 || j>=gridY) continue; //get the neighbors if they are not out of bounds
				node n(i, j);
				n.parentX = this->x;
				n.parentY = this->y;
				n.Gcost = (this->Gcost + euclidean_distance(this->x, this->y, i, j)); //accumulate Gcost as we explore nodes
				n.calHCost(goal);
				n.calFcost();
				nodes.push_back(n);
			}
		}
		return nodes;
	}
	void print() const
	{
		cout << "(" << this->x << ", " << this->y << ")" << endl;
	}
};

//calculate the euclidean distance between two neighbors in the grid
//orthogonal neighbors have a cost of 10 and diagonal neighbors have a cost of 14
int euclidean_distance(int x1, int y1, int x2, int y2)
{
	if ((x1 == x2) || (y1 == y2))
		return 10;
	else
		return 14;
}

//see if a node is already in the list with a lower cost
bool match(vector<node> list, node n)
{
	for (auto itr : list)
	{
		if (itr == n && itr < n)
		{
			return true;
		}
	}
	return false;
}

//iteratively traverse from the node n to the source node and display each node along the route
//list -> the list of closed nodes from the search algorithm
//n -> a copy of the destination node once it is reached by the search algorithm
//source -> the source node of the search
void trace(vector<node> list, node n, node source)
{
	if (n == source) //trace complete
		return;
	else
	{
		//display the node n, set n to its parent, and trace from new n
		n.print();
		n = *find(list.begin(), list.end(), node(n.parentX, n.parentY));
		trace(list, n, source);
	}
}
