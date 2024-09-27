/*
 * File: Graph.h Author: Nicolas Gioanni Purpose: Declaration of the
 * Graph class for representing and managing graph structures and
 * operations.
 *
 * Functionality/Features:
 * - Declare methods for constructing a graph with a specified number
 *   of nodes.
 * - Declare methods for creating edges between nodes with specified
 *   capacities.
 * - Declare methods for connecting source and sink nodes for flow
 *   network algorithms.
 * - Declare methods for accessing and modifying the adjacency matrix.
 * - Declare methods for retrieving adjacent nodes for a given node.
 * - Declare methods for printing matching results for the bipartite
 *   graph.
 *
 * Assumptions:
 * - The graph is used for bipartite matching and flow network
 *   algorithms.
 * - The adjacency matrix accurately represents the graph's structure
 *   and capacities.
 * - Node indices are valid and within the range of the graph's node
 *   count.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Graph
{
public:
    /**
     * Constructor for the Graph class.
     *
     * Method Name: Graph
     *
     * Purpose: Initializes a new instance of the Graph class with the
     * specified number of nodes.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - A new instance of the Graph class is created.
     * - The nodes and totalNodes variables are initialized with the
     *   specified value.
     * - The adjacency matrix is initialized.
     *
     * Parameters:
     * - nodes: An integer representing the number of nodes in the
     *   graph.
     */
    Graph(int nodes);

    /**
     * Create an edge between two nodes with a specified maximum flow.
     *
     * Method Name: createEdge
     *
     * Purpose: Creates an edge between node1 and node2 with the
     * specified maximum flow.
     *
     * Preconditions:
     * - The nodes are valid and within the range of the graph's node
     *   count.
     *
     * Postconditions:
     * - An edge is created between node1 and node2 with the specified
     *   maximum flow.
     *
     * Parameters:
     * - node1: An integer representing the first node.
     * - node2: An integer representing the second node.
     * - maxFlow: An integer representing the maximum flow between the
     *   nodes.
     */
    void createEdge(int node1, int node2, int maxFlow);

    /**
     * Connect the source and sink nodes to the graph.
     *
     * Method Name: connectSourceAndSinkNodes
     *
     * Purpose: Connects the source and sink nodes to the graph.
     *
     * Preconditions:
     * - The source and sink nodes are valid and within the range of
     *   the graph's node count.
     *
     * Postconditions:
     * - The source and sink nodes are connected to the graph.
     *
     * Parameters:
     * - source: An integer representing the source node.
     * - sink: An integer representing the sink node.
     */
    void connectSourceAndSinkNodes(int source, int sink);

    /**
     * Adjust the adjacency matrix to allow external access.
     *
     * Method Name: adjustAdjacencyMatrix
     *
     * Purpose: Adjusts the adjacency matrix to allow external access.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - The adjacency matrix is returned for external access.
     *
     * Returns: A reference to the adjacency matrix.
     */
    std::vector<std::vector<int>> &adjustAdjacencyMatrix();

    /**
     * Get the number of nodes in the graph.
     *
     * Method Name: getNodes
     *
     * Purpose: Returns the number of nodes in the graph.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - The number of nodes in the graph is returned.
     *
     * Returns: An integer representing the number of nodes in the
     * graph.
     */
    int getNodes() const;

    /**
     * Get the adjacency matrix of the graph.
     *
     * Method Name: getAdjacencyMatrix
     *
     * Purpose: Returns the adjacency matrix of the graph.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - The adjacency matrix of the graph is returned.
     *
     * Returns: A constant reference to the adjacency matrix.
     */
    const std::vector<std::vector<int>> &getAdjacencyMatrix() const;

    /**
     * Find the adjacent nodes for a given node.
     *
     * Method Name: findAdjacentNodes
     *
     * Purpose: Finds the adjacent nodes for the given node.
     *
     * Preconditions:
     * - The node is valid and within the range of the graph's node
     *   count.
     *
     * Postconditions:
     * - The adjacent nodes for the given node are returned.
     *
     * Parameters:
     * - node: An integer representing the node to find adjacent nodes
     *   for.
     *
     * Returns: A vector of integers representing the adjacent nodes
     * for the given node.
     */
    std::vector<int> findAdjacentNodes(int node) const;

    /**
     * Print the matching results for the bipartite graph.
     *
     * Method Name: printResults
     *
     * Purpose: Prints the matching results for the bipartite graph.
     *
     * Preconditions:
     * - The input adjacency matrix contains valid node names.
     *
     * Postconditions:
     * - The matching pairs are printed to the console.
     *
     * Parameters:
     * - inputAdjacencyMatrix: A constant reference to a vector of
     *   strings representing the input adjacency matrix.
     */
    void printResults(const std::vector<std::string>
                          &inputAdjacencyMatrix) const;

private:
    // The number of nodes in the graph
    int nodes;

    // The total number of nodes in the graph
    int totalNodes;

    // The adjacency matrix representing the graph structure
    std::vector<std::vector<int>> adjacencyMatrix;

    /**
     * Initialize the adjacency matrix with 0 values.
     *
     * Method Name: initializeAdjacencyMatrix
     *
     * Purpose: Initializes the adjacency matrix with 0 values.
     *
     * Preconditions:
     * - The number of nodes is valid and greater than 0.
     *
     * Postconditions:
     * - The adjacency matrix is initialized with 0 values.
     *
     * Parameters:
     * - nodes: An integer representing the number of nodes in the
     *   graph.
     */
    void initializeAdjacencyMatrix(int nodes);

    /**
     * Create the source node and connect it to the first half of the
     * nodes.
     *
     * Method Name: createSourceNode
     *
     * Purpose: Creates the source node and connects it to the first
     * half of the nodes.
     *
     * Preconditions:
     * - The source node is valid and within the range of the graph's
     *   node count.
     *
     * Postconditions:
     * - The source node is connected to the first half of the nodes.
     *
     * Parameters:
     * - source: An integer representing the source node.
     */
    void createSourceNode(int source);

    /**
     * Create the sink node and connect the second half of the nodes
     * to it.
     *
     * Method Name: createSinkNode
     *
     * Purpose: Creates the sink node and connects the second half of
     * the nodes to it.
     *
     * Preconditions:
     * - The sink node is valid and within the range of the graph's
     *   node count.
     *
     * Postconditions:
     * - The second half of the nodes is connected to the sink node.
     *
     * Parameters:
     * - sink: An integer representing the sink node.
     */
    void createSinkNode(int sink);
};

#endif
