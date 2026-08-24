#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using Graph = std::map<std::string, std::vector<std::string>>;

// A mango seller is any person whose name ends with the letter 'm'.
bool isMangoSeller(const std::string& name) {
    return !name.empty() && name.back() == 'm';
}

// TODO: Implement breadth-first search.
//
// Start at `start` and return the first mango seller you find.
// Return an empty string if no seller is reachable.
//
// Requirements:
// - Use a std::queue for BFS.
// - Use a std::set to avoid searching the same person twice.
// - Do not get stuck if the graph contains a cycle.
// - If multiple sellers are at the same distance, return the one reached first.
std::string findNearestMangoSeller(const Graph& graph, const std::string& start) {
    // Your code goes here.
    return "";
}

int main() {
    Graph graph;

    graph["you"] = {"alice", "bob", "claire"};
    graph["alice"] = {"peggy"};
    graph["bob"] = {"anuj", "peggy"};
    graph["claire"] = {"thom", "jonny"};
    graph["anuj"] = {};
    graph["peggy"] = {"you"};       // Cycle back to you.
    graph["thom"] = {};
    graph["jonny"] = {"peggy"};     // Shared neighbor and another cycle.

    std::cout << findNearestMangoSeller(graph, "you") << '\n';

    // Expected output: thom
    // The function should return "" for an unknown or unreachable start node.
    return 0;
}
