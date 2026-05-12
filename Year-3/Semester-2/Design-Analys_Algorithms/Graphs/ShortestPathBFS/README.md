# Shortest Path using BFS
## Problem1
Input: An undirected unweighted graph G(V,E), vertex v and vertex u
Output: shortest path from v to u if u is reachable from v, -1 otherwise

## Problem2
Input: An undirected unweighted graph G(V,E), vertex v
Output: shortest paths from v to others if others are reachable from v, -1 otherwise

## Problem3
Input: A matrix A[1..n][1..n], where A[i][j] in {0, 1}. 
Output: shortest path from (1,1) to {n,n} if possible, -1 otherwise

We can move vertical, horizontal, diagonal. 0 is transit, 1 is wall.
If (1,1) is 1, then no path exists.