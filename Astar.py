import math
import numpy as np

gridX = 10
gridY = 10


def distance(x1, y1, x2, y2):
    if x1 == x2 or y1 == y2:
        return 10
    else:
        return 14

class node:
    def __init__(self, a=-1, b=-1):
        self.x = a
        self.y = b
        self.parentx = -1
        self.parenty = -1
        self.Gcost = math.inf
        self.Hcost = math.inf
        self.Fcost = math.inf

    def __gt__(self, n):
        return self.Fcost > n.Fcost

    def __lt__(self, n):
        return self.Fcost < n.Fcost

    def __eq__(self, n):
        return (self.x == n.x) and (self.y == n.y)

    def calHcost(self, dest):
        self.Hcost = math.sqrt((self.x - dest.x) ** 2 + (self.y - dest.y) ** 2)*10

    # return a list of the nodes neighboring this node
    def get_neighbors(self, dest):
        neighbors = []
        for i in range(self.x - 1, self.x + 2):
            for j in range(self.y - 1, self.y + 2):
                if i == self.x and j == self.y:
                    continue
                elif (i < 0 or i >= gridX or j < 0 or j >= gridY):
                    continue
                # if out of bounds skip
                neighbor = node(i, j)
                neighbor.parentx = self.x
                neighbor.parenty = self.y
                neighbor.Gcost = self.Gcost + distance(self.x, self.y, dest.x, dest.y)
                neighbor.calHcost(dest)
                neighbor.Fcost = neighbor.Gcost + neighbor.Hcost
                neighbors.append(neighbor)
        return neighbors

    def print(self):
        print(self.x,self.y)

def trace(list,n,source):
    if n == source:
        n.print()
        return 
    else:
        n.print()
        n = [i for i in list if i == node(n.parentx,n.parenty)].pop()
        trace(list,n,source)

def Asearch(grid, src, dest):
    open = list()
    closed = list()
    open.append(src)
    while len(open) != 0:
        current_node = min(open)
        candidates = current_node.get_neighbors(dest)
        open.remove(current_node)
        for candidate in candidates:
            if not grid[candidate.x][candidate.y]:
                continue

            if candidate == dest:
                print("destination found")
                closed.append(current_node)
                trace(closed,candidate,src)
                return

            if candidate in closed and closed[closed.index(candidate)] < candidate:
                continue

            if candidate in open and open[open.index(candidate)] < candidate:
                continue

            else:
                open.append(candidate)

        closed.append(current_node)

    print("destination not found")

import time
def main():
    grid = np.ones((10, 10), np.int8).tolist()
    print("enter the obstacles on the map or hit q to exit")
    while(1):
        user_input = input("format: x y >> ")
        if user_input == 'q': break
        else:
            i,j = tuple(int(a) for a in user_input.split())
            grid[i][j] = 0
    
    user_input = input("enter source node: x y >> ")
    i,j = tuple(int(a) for a in user_input.split())
    src = node(i, j)
    src.Gcost = 0
    user_input = input("enter destination node: x y >> ")
    i,j = tuple(int(a) for a in user_input.split())
    destination = node(i, j)
    t= time.time()
    Asearch(grid, src, destination)
    print(f"time to search {(time.time()-t)*1000000} microseconds")


main()
