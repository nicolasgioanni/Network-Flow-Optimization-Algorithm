/*
 * File: Graph.cpp Author: Nicolas Gioanni Purpose: Implementation of
 * the Graph class, providing methods for graph construction and
 * manipulation.
 *
 * Functionality/Features:
 * - Initialize the graph with a specified number of nodes.
 * - Create edges between nodes with specified capacities.
 * - Connect source and sink nodes to the graph.
 * - Adjust and access the adjacency matrix.
 * - Find adjacent nodes for a given node.
 * - Print the matching results of the bipartite graph.
 *
 * Assumptions:
 * - The graph is bipartite and used for flow network algorithms.
 * - The adjacency matrix accurately represents edges and capacities.
 * - Node indices and capacities are valid and within expected ranges.
 */

#include "Graph.h"
#include <iostream>

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
 * - nodes: An integer representing the number of nodes in the graph.
 */
Graph::Graph(int nodes) : nodes(nodes), totalNodes(nodes + 2)
{
    // Initialize adjacency matrix
    initializeAdjacencyMatrix(totalNodes);
}

/**
 * Create an edge between two nodes with a specified maximum flow.
 *
 * Method Name: createEdge
 *
 * Purpose: Creates an edge between node1 and node2 with the specified
 * maximum flow.
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
void Graph::createEdge(int node1, int node2, int maxFlow)
{
    // Create edge between node1 and node2 with maxFlow
    adjacencyMatrix[node1][node2] = maxFlow;
}

/**
 * Connect the source and sink nodes to the graph.
 *
 * Method Name: connectSourceAndSinkNodes
 *
 * Purpose: Connects the source and sink nodes to the graph.
 *
 * Preconditions:
 * - The source and sink nodes are valid and within the range of the
 *   graph's node count.
 *
 * Postconditions:
 * - The source and sink nodes are connected to the graph.
 *
 * Parameters:
 * - source: An integer representing the source node.
 * - sink: An integer representing the sink node.
 */
void Graph::connectSourceAndSinkNodes(int source, int sink)
{
    // Connect source and sink nodes to the graph
    createSourceNode(source);
    createSinkNode(sink);
}

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
std::vector<std::vector<int>> &Graph::adjustAdjacencyMatrix()
{
    return adjacencyMatrix;
}

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
 * Returns: An integer representing the number of nodes in the graph.
 */
int Graph::getNodes() const
{
    return totalNodes;
}

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
const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix()
    const
{
    return adjacencyMatrix;
}

/**
 * Find the adjacent nodes for a given node.
 *
 * Method Name: findAdjacentNodes
 *
 * Purpose: Finds the adjacent nodes for the given node.
 *
 * Preconditions:
 * - The node is valid and within the range of the graph's node count.
 *
 * Postconditions:
 * - The adjacent nodes for the given node are returned.
 *
 * Parameters:
 * - node: An integer representing the node to find adjacent nodes
 *   for.
 *
 * Returns: A vector of integers representing the adjacent nodes for
 * the given node.
 */
std::vector<int> Graph::findAdjacentNodes(int node) const
{
    // Create a vector to store adjacent nodes
    std::vector<int> adjacent;

    // Iterate through the adjacency matrix to find adjacent nodes
    for (int i = 0; i < totalNodes; ++i)
    {
        // Check if there is an edge between the nodes
        if (adjacencyMatrix[node][i] > 0)
        {
            // Add the adjacent node to the vector
            adjacent.push_back(i);
        }
    }

    // Return the set of adjacent nodes
    return adjacent;
}

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
 * - inputAdjacencyMatrix: A constant reference to a vector of strings
 *   representing the input adjacency matrix.
 */
void Graph::printResults(const std::vector<std::string>
                             &inputAdjacencyMatrix) const
{
    int matches = 0;

    // Iterate through the adjacency matrix to find the matching pairs
    for (int i = 1; i <= nodes / 2; ++i)
    {
        // Iterate through the second half of the nodes
        for (int n = nodes / 2 + 1; n <= nodes; ++n)
        {
            // Check if there is an edge between the nodes
            if (adjacencyMatrix[n][i] == 1)
            {
                // Output the matching pair
                std::cout
                    << inputAdjacencyMatrix[i]
                    << " / "
                    << inputAdjacencyMatrix[n]
                    << std::endl;
                matches++;
            }
        }
    }

    // Output the total number of matches
    std::cout << matches << " total matches" << std::endl;
}

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
 * - nodes: An integer representing the number of nodes in the graph.
 */
void Graph::initializeAdjacencyMatrix(int nodes)
{
    // Initialize the adjacency matrix with 0 values
    adjacencyMatrix.assign(nodes, std::vector<int>(nodes, 0));
}

/**
 * Create the source node and connect it to the first half of the
 * nodes.
 *
 * Method Name: createSourceNode
 *
 * Purpose: Creates the source node and connects it to the first half
 * of the nodes.
 *
 * Preconditions:
 * - The source node is valid and within the range of the graph's node
 *   count.
 *
 * Postconditions:
 * - The source node is connected to the first half of the nodes.
 *
 * Parameters:
 * - source: An integer representing the source node.
 */
void Graph::createSourceNode(int source)
{
    // Connect the source node to the first half of the nodes
    for (int i = 1; i <= nodes / 2; ++i)
    {
        // Create an edge from the source to the node
        createEdge(source, i, 1);
    }
}

/**
 * Create the sink node and connect the second half of the nodes to
 * it.
 *
 * Method Name: createSinkNode
 *
 * Purpose: Creates the sink node and connects the second half of the
 * nodes to it.
 *
 * Preconditions:
 * - The sink node is valid and within the range of the graph's node
 *   count.
 *
 * Postconditions:
 * - The second half of the nodes is connected to the sink node.
 *
 * Parameters:
 * - sink: An integer representing the sink node.
 */
void Graph::createSinkNode(int sink)
{
    // Connect the second half of the nodes to the sink node
    for (int i = nodes / 2 + 1; i <= nodes; ++i)
    {
        // Create an edge from the node to the sink
        createEdge(i, sink, 1);
    }
}
