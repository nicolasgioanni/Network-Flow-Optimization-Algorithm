/*
 * File: FordFulkerson.h Author: Nicolas Gioanni Purpose: Declaration
 * of the FordFulkerson class for implementing the Ford-Fulkerson
 * algorithm for maximum flow in a flow network.
 *
 * Functionality/Features:
 * - Declare methods for calculating the maximum flow.
 * - Declare methods for constructing level graphs.
 * - Declare methods for finding augmenting paths.
 * - Declare methods for updating the residual graph.
 * - Declare methods for initializing internal data structures.
 *
 * Assumptions:
 * - The graph is a flow network with defined source and sink nodes.
 * - The graph's adjacency matrix accurately represents the capacities
 *   of the edges.
 */

#ifndef FORDFULKERSON_H
#define FORDFULKERSON_Hs

#include "Graph.h"
#include <queue>

class FordFulkerson
{
public:
    /**
     * Constructor for the FordFulkerson class.
     *
     * Method Name: FordFulkerson
     *
     * Purpose: Initializes a new instance of the FordFulkerson class.
     *
     * Preconditions:
     * - A valid Graph object is provided as input.
     *
     * Postconditions:
     * - A new instance of the FordFulkerson class is created.
     * - The depth and maxFlow vectors are initialized.
     */
    FordFulkerson(Graph &graph);

    /**
     * Calculates the maximum flow in the flow network using the
     * Ford-Fulkerson algorithm.
     *
     * Method Name: calculateMaxFlow
     *
     * Purpose: Calculates the maximum flow in the flow network from
     * the source to the sink node.
     *
     * Parameters:
     * - source: An integer representing the source node in the flow
     *   network.
     * - sink: An integer representing the sink node in the flow
     *   network.
     *
     * Preconditions:
     * - The source and sink nodes are within the valid range of the
     *   graph.
     *
     * Postconditions:
     * - The maximum flow in the flow network is calculated.
     * - The maxFlow matrix is updated with the flow values.
     * - An exception is thrown if the calculation process fails.
     */
    void calculateMaxFlow(int source, int sink);

private:
    // The depth of each node in the graph
    std::vector<int> depth;

    // The maximum flow matrix
    std::vector<std::vector<int>> maxFlow;

    // The residual graph
    Graph &graph;

    /**
     * Constructs a level graph from the flow network to facilitate
     * flow calculations.
     *
     * Method Name: levelGraph
     *
     * Purpose: Constructs a level graph to determine if the sink node
     * is reachable from the source node.
     *
     * Parameters:
     * - source: An integer representing the source node in the flow
     *   network.
     * - sink: An integer representing the sink node in the flow
     *   network.
     *
     * Returns: A boolean value indicating if the sink node is
     * reachable from the source node.
     *
     * Preconditions:
     * - The source and sink nodes are within the valid range of the
     *   graph.
     *
     * Postconditions:
     * - The depth vector is updated with the depth of each node in
     *   the level graph.
     * - The function returns true if the sink node is reachable,
     *   false otherwise.
     * - An exception is thrown if the level graph construction
     *   process fails.
     */
    bool levelGraph(int source, int sink);

    /**
     * Finds an augmenting path from the source to the sink node in
     * the flow network.
     *
     * Method Name: findAugmentingPath
     *
     * Purpose: Finds an augmenting path from the source to the sink
     * node in the flow network.
     *
     * Parameters:
     * - path: A vector of integers to store the nodes in the
     *   augmenting path.
     * - source: An integer representing the source node in the flow
     *   network.
     * - sink: An integer representing the sink node in the flow
     *   network.
     *
     * Returns: A boolean value indicating if an augmenting path is
     * found.
     *
     * Preconditions:
     * - The source and sink nodes are within the valid range of the
     *   graph.
     *
     * Postconditions:
     * - The path vector is updated with the nodes in the augmenting
     *   path.
     * - The function returns true if an augmenting path is found,
     *   false otherwise.
     * - An exception is thrown if finding an augmenting path fails.
     */
    bool findAugmentingPath(std::vector<int> &path,
                            int source,
                            int sink);

    /**
     * Updates the residual graph with the flow along the augmenting
     * path.
     *
     * Method Name: updateResidualGraph
     *
     * Purpose: Updates the residual graph with the flow along the
     * augmenting path.
     *
     * Parameters:
     * - src: An integer representing the source node in the flow
     *   network.
     * - dst: An integer representing the destination node in the flow
     *   network.
     *
     * Preconditions:
     * - The source and destination nodes are within the valid range
     *   of the graph.
     *
     * Postconditions:
     * - The residual graph is updated with the flow along the
     *   augmenting path.
     * - An exception is thrown if updating the residual graph fails.
     */
    void updateResidualGraph(int src, int dst);

    /**
     * Clears the max flow values at the specified node in the flow
     * network.
     *
     * Method Name: clearMaxFlowAtNode
     *
     * Purpose: Clears the max flow values at the specified node in
     * the flow network.
     *
     * Parameters:
     * - node: An integer representing the node in the flow network to
     *   clear the max flow values.
     *
     * Preconditions:
     * - The node is within the valid range of the graph.
     *
     * Postconditions:
     * - The max flow values at the specified node are cleared.
     * - An exception is thrown if clearing the max flow at a node
     *   fails.
     */
    void clearMaxFlowAtNode(int node);

    /**
     * Initializes the depth vector with the total number of nodes in
     * the flow network.
     *
     * Method Name: initializeDepth
     *
     * Purpose: Initializes the depth vector with the total number of
     * nodes in the flow network.
     *
     * Preconditions:
     * - The graph object is initialized with valid data.
     *
     * Postconditions:
     * - The depth vector is initialized with the total number of
     *   nodes.
     * - An exception is thrown if initializing the depth vector
     *   fails.
     */
    void initializeDepth();

    /**
     * Initializes the max flow matrix with the total number of nodes
     * in the flow network.
     *
     * Method Name: initializeMaxFlow
     *
     * Purpose: Initializes the max flow matrix with the total number
     * of nodes in the flow network.
     *
     * Preconditions:
     * - The graph object is initialized with valid data.
     *
     * Postconditions:
     * - The max flow matrix is initialized with the total number of
     *   nodes.
     * - An exception is thrown if initializing the max flow matrix
     *   fails.
     */
    void initializeMaxFlow();

    /**
     * Finds the next node in the path for the Ford-Fulkerson
     * algorithm.
     *
     * Method Name: findNextNodeInPath
     *
     * Purpose: Finds the next node in the path for the Ford-Fulkerson
     * algorithm.
     *
     * Parameters:
     * - node: A reference to an integer representing the current node
     *   in the path.
     * - path: A reference to a vector of integers storing the nodes
     *   in the path.
     * - backtracking: A reference to a boolean flag indicating if
     *   backtracking is required.
     * - source: An integer representing the source node in the flow
     *   network.
     *
     * Returns: A boolean value indicating if the next node in the
     * path is found.
     *
     * Preconditions:
     * - The current node is within the valid range of the graph.
     *
     * Postconditions:
     * - The path vector is updated with the nodes in the path.
     * - The backtracking flag is set to true if backtracking is
     *   required.
     * - The function returns true if the next node in the path is
     *   found, false otherwise.
     * - An exception is thrown if finding the next node in the path
     *   fails.
     */
    bool findNextNodeInPath(int &node,
                            std::vector<int> &path,
                            bool &backtrack,
                            int source);

    /**
     * Augments the flow along the found path in the flow network.
     *
     * Method Name: augmentFlowAlongPath
     *
     * Purpose: Augments the flow along the found path in the flow
     * network.
     *
     * Parameters:
     * - path: A reference to a vector of integers storing the nodes
     *   in the augmenting path.
     * - source: An integer representing the source node in the flow
     *   network.
     * - sink: An integer representing the sink node in the flow
     *   network.
     *
     * Preconditions:
     * - The path vector contains the nodes in the augmenting path.
     *
     * Postconditions:
     * - The flow along the path is augmented in the flow network.
     * - The residual graph is updated with the flow values.
     * - An exception is thrown if augmenting flow along the path
     *   fails.
     */
    void augmentFlowAlongPath(std::vector<int> &path,
                              int source,
                              int sink);
};

#endif
