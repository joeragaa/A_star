#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
#define gridX 10
#define gridY 10
class node
{	
	public:
		//x,y is the location of the node and parents denotes how to reach this node
		int x;
		int y;
		int parentX;
		int parentY;
		
		//might need to change these to doubles
		float Gcost; //distance from source
		float Hcost; //distance from destination
		float Fcost; //g+h
		
		node(int a= NULL, int b=NULL)
		{
			x=a;
			y=b;
			parentX = NULL;
			parentY= NULL;
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
			if(this->x==n.x && this->y==n.y)
				return true;
			else
				return false;
		}
		
		// calculation of euclidean distance from a node to the destination
		void calHCost(node dest)
		{
			Hcost = (float)sqrt(pow((this->x-dest.x),2) + pow((this->y-dest.y),2) );
		}
		float getFcost()
		{
			return Gcost + Hcost;
		}
		void print() const
		{
			cout << "(" << this->x << ", " << this->y << ")" << endl;
		}
		//get the 8 nearest neighbors to the current node
		vector<node> getNeighbors()
		{
			vector <node> nodes;
			for (int i=x-1;i<=x+1;i++)
			{
				for (int j=y-1;j<=y+1;j++)
				{
					if(i==this->x && j==this->y) continue; //skip the current node from the loop
					else if (i<0 || i>gridX || j<0 || j>gridY) continue; //get the neighbors if they are not out of bounds
					node n(i,j);
					n.parentX=this->x;
					n.parentY=this->y;
					n.Gcost = ( this->Gcost + (int)(sqrt(pow(i,2)+pow(j,2))*10) ); //accumulate Gcost as we explore nodes
					nodes.push_back(n);
				}
			}
			return nodes;
		}
};

void Asearch(bool grid[gridX][gridY], node src, node dest)
{
	//start with source node
	//get neighbors and add to openlist
	//pop neighbor with least f cost
	//explore neighbors and add to openlist
	//etc
	set<node> openList;
	set<node> closedlist;
	openList.insert(src);
	while (!openList.empty())
	{
		node current_node = *openList.begin();
		//check if destination
		if (current_node == dest)
		{
			//declare bankruptcy
		}

		//if(current_node in closedlist)
		//{
		//	check if better path
		//}
		openList.erase(current_node);
		closedlist.insert(current_node);

		vector<node> current_candidates = current_node.getNeighbors();
		openList.insert(current_candidates.begin(), current_candidates.end());

	}
}

int main(void)
{
	//get binary occupancy grid
	//get source and destination
	//set their node values f g h
	//check inputs for errors out of bounds, or blocked source or destination
	node source(3,3);
	source.Gcost = 0;
	node destination(2, 6);
	bool grid[gridX][gridY] = { 1 };
	//Asearch(grid, source, destination);
	return 0;
}
