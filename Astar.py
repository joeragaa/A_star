import math
import numpy as np
import time
import matplotlib.pyplot as plt

# default map values
gridX = 10
gridY = 10

# dictionary used for visulization
# the obstalce and open spaces must be at positions 0 and 1 
# respectively as they are used for boolean operations
vis_labels = ['obstacle', 'open', 'source', 'destination', 'path']
vis_dict = {k:v for v,k in enumerate(vis_labels)}
vis_list = [] #list of nodes on the generated path

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
        self.Hcost = math.sqrt((self.x - dest.x) ** 2 +
                               (self.y - dest.y) ** 2)*10

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
                neighbor.Gcost = self.Gcost + \
                    distance(self.x, self.y, dest.x, dest.y)
                neighbor.calHcost(dest)
                neighbor.Fcost = neighbor.Gcost + neighbor.Hcost
                neighbors.append(neighbor)
        return neighbors

    def print(self):
        print(self.x, self.y)

def trace(list, n, source):
    if n == source:
        n.print()
        vis_list.append(n)
        return
    else:
        n.print()
        vis_list.append(n)
        n = [i for i in list if i == node(n.parentx, n.parenty)].pop()
        trace(list, n, source)


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
                trace(closed, candidate, src)
                return

            if candidate in closed and closed[closed.index(candidate)] < candidate:
                continue

            if candidate in open and open[open.index(candidate)] < candidate:
                continue

            else:
                open.append(candidate)

        closed.append(current_node)

    print("destination not found")


def display(arr):
    figure = plt.figure()
    axes = figure.add_subplot()
    axes = axes.matshow(np.transpose(arr))
    cb_labels = vis_labels
    cb = figure.colorbar(axes)
    cb.ax.get_yaxis().set_ticks(list(range(len(cb_labels))))
    cb.ax.set_yticklabels(cb_labels)
    plt.show()

# get a valid input point from the user
def get_input(isPoint=False):
    user_input = input("format: x y >> ")
    if user_input is None:
        raise ValueError("invalid input")

    if user_input == 'q':
        raise Exception

    x, y = tuple(int(a) for a in user_input.split())
    if x is None or y is None:
        raise ValueError("invalid input")

    if (isPoint == True) and (x < 0 or y < 0 or x > gridX or y > gridY):
        raise ValueError("invalid input")

    else:
        return x, y


def main():
    print("enter map dimensions")
    try:
        global gridX, gridY
        gridX, gridY = get_input()
    except:
        print("map dimensions must be positive integers")
        return
    grid = np.ones((gridX, gridY), np.int8).tolist()

    print("enter the obstacles on the map or hit q to exit")
    try:
        while(1):
            i, j = get_input(isPoint=True)
            grid[i][j] = 0
    except ValueError:
        print("obstacles must be within 0 and specified map dimension")
        return
    except:
        pass

    print("enter source node")
    try:
        i, j = get_input(isPoint=True)
        src = node(i, j)
        src.Gcost = 0
    except:
        return

    print("enter destination node")
    try:
        i, j = get_input(isPoint=True)
        destination = node(i, j)
    except:
        return

    # search
    t = time.time()
    Asearch(grid, src, destination)
    print(f"time to search {int((time.time()-t)*1000)} milliseconds")

    # visulization steps
    for t in vis_list:
        grid[t.x][t.y] = vis_dict["path"]
    grid[src.x][src.y] = vis_dict["source"]
    grid[destination.x][destination.y] = vis_dict["destination"]
    display(grid)


main()
