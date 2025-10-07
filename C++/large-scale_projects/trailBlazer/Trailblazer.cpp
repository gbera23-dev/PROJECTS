/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "map.h"
#include "random.h"
#include "UnionFind.h"
using namespace std;
/*CONSTANT ARRAYS USED FOR TRAVERSAL PURPOSES*/
const int dx[8] = {1, -1, 1, -1, 1, -1, 0, 0};
const int dy[8] = { 1, -1, -1, 1, 0, 0, 1, -1 };

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world), 
    double heuristic(Loc start, Loc end, Grid<double>& world)) {
    //My implementation uses two maps: One for maintaining current path costs and second for 
    //maintaining parents of the children. map is the good structure to use, because we can access 
    //and check elements efficiently
    TrailblazerPQueue<Loc> queue;  
    Map<Loc, double> pathCost; 
    Set<Loc> used;  
    Map<Loc, Loc> childParent;
    pathCost[start] = 0.0; 
    colorCell(world, start, YELLOW);
    queue.enqueue(start, heuristic(start, end, world));
    while (!queue.isEmpty()) {
        Loc current = queue.dequeueMin();
        used.add(current); 
        colorCell(world, current, GREEN);
        if (current == end) break; 
        for (int i = 0; i < 8; i++) {
            Loc candidate = makeLoc(current.row + dx[i], current.col + dy[i]);
            if (!world.inBounds(candidate.row, candidate.col)) continue; 
                double edgeCost = costFn(current, candidate, world);
                if (used.contains(candidate) || edgeCost == INFINITY)continue;
                double newCost = pathCost[current] + edgeCost;
                if (!pathCost.containsKey(candidate)) {
                    pathCost[candidate] = newCost;
                    childParent[candidate] = current;
                    colorCell(world, candidate, YELLOW);
                    queue.enqueue(candidate, pathCost[candidate] + heuristic(candidate, end, world));
                }
                else if(newCost < pathCost[candidate]) {
                    pathCost[candidate] = newCost;
                    queue.decreaseKey(candidate, newCost + heuristic(candidate, end, world));
                    childParent[candidate] = current;
                }
            }
    }
    return generatePath(childParent, start, end); 
}

Vector<Loc> generatePath(Map<Loc, Loc>& childParent, Loc start, Loc end) {
    Stack<Loc> path; 
    Vector<Loc> sol; 
    path.push(end); 
    Loc parent = end; 
    while (parent != start) {
        parent = childParent[parent];
        path.push(parent);
    }
    while (!path.isEmpty()) {
        sol.add(path.pop()); 
    }
    return sol; 
}

Set<Edge> createMaze(int numRows, int numCols) {
    Set<Edge> mazeTree; 
    TrailblazerPQueue<Edge> queue; 
    UnionFind uf(numRows * numCols); 
    Map<Loc, int> intIdentifier; 
    generateGrid(numRows, numCols, queue, intIdentifier);
    while (mazeTree.size() < numRows*numCols - 1) {
        Edge e = queue.dequeueMin();
        int first = intIdentifier[e.start]; 
        int second = intIdentifier[e.end];
        if (uf.find(first) != uf.find(second)) {
            uf.merge(first, second);
            mazeTree.add(e); 
        }
    }
    return mazeTree;
}

void generateGrid(int numRows, int numCols, TrailblazerPQueue<Edge>& queue, Map<Loc, int>& intIdentifier) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Loc current = makeLoc(i, j);
            generateEdge(current, makeLoc(i + 1, j), numRows, numCols, queue);
            generateEdge(current, makeLoc(i, j + 1), numRows, numCols, queue);
            intIdentifier[current] = numRows * i + j; 
        }
    }
}

void generateEdge(Loc first, Loc second, int maxi, int maxj,
    TrailblazerPQueue<Edge>& queue) {
    if (second.row == maxi || second.col == maxj)return;  
    Edge edge = makeEdge(first, second);
    queue.enqueue(edge, randomReal(0, 1));
}
