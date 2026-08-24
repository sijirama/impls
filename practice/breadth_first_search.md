# Practice Problem Set: Breadth-First Search on a Graph

## Goal

Implement a directed graph using an adjacency list and use breadth-first search (BFS) to find the shortest connection between two nodes.

Use a queue and a `visited` set. A node must be visited at most once, even when multiple nodes point to it or when the graph contains a cycle.

## Graph

```text
you    -> alice, bob, claire
alice  -> peggy
bob    -> anuj, peggy
claire -> thom, jonny
anuj   ->
peggy  ->
thom   ->
jonny  ->
```

Represent it with an adjacency list, for example:

```text
graph["you"] = ["alice", "bob", "claire"]
```

## Exercises

### 1. Build the graph

Create the graph in code. Make sure nodes with no outgoing edges are still present with an empty neighbor list.

### 2. Find whether a target is reachable

Implement:

```text
bool can_reach(graph, start, target)
```

Return `true` if BFS can reach `target` from `start`; otherwise return `false`.

Expected results:

```text
can_reach(graph, "you", "peggy")  -> true
can_reach(graph, "you", "thom")   -> true
can_reach(graph, "you", "zara")   -> false
```

### 3. Find the shortest path

Implement:

```text
path shortest_path(graph, start, target)
```

Return the nodes in the shortest path, including `start` and `target`. Return an empty path when no path exists.

Expected results:

```text
shortest_path(graph, "you", "peggy")
-> ["you", "alice", "peggy"]

shortest_path(graph, "you", "thom")
-> ["you", "claire", "thom"]

shortest_path(graph, "you", "zara")
-> []
```

If multiple shortest paths exist, returning any one of them is acceptable.

### 4. Mango seller search

Implement:

```text
string find_seller(graph, start)
```

A seller is any node whose name ends in `m`. Return the first seller found by BFS, or an empty string if no seller exists.

For the graph above:

```text
find_seller(graph, "you") -> "thom"
```

### 5. Handle cycles

Add these edges:

```text
peggy -> you
jonny -> peggy
```

Run all relevant tests again. The search must terminate and must not process any node twice.

## Test cases

Test at least the following:

1. The target is the start node.
2. The target is a direct neighbor.
3. The target is several edges away.
4. The target is unreachable.
5. The start node is missing from the graph.
6. The graph contains a cycle.
7. Two different nodes point to the same neighbor.

## Complexity target

Your BFS should run in `O(V + E)` time and use `O(V)` additional space, where `V` is the number of nodes and `E` is the number of edges.

## Optional extensions

- Return the distance instead of the full path.
- Return all shortest paths.
- Build an undirected graph from a list of edges.
- Find the nearest mango seller when seller status is stored separately from the node name.
