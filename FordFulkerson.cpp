/*
 * File: FordFulkerson.cpp Author: Nicolas Gioanni Purpose:
 * Implementation of the FordFulkerson class, providing methods for
 * calculating maximum flow using the Ford-Fulkerson algorithm.
 *
 * Functionality/Features:
 * - Calculate the maximum flow in a flow network.
 * - Construct level graphs to facilitate flow calculations.
 * - Find augmenting paths and update the residual graph.
 * - Initialize internal data structures for the algorithm.
 * - Handle exceptions and errors during the calculation process.
 *
 * Assumptions:
 * - The graph is a flow network with defined source and sink nodes.
 * - The graph's adjacency matrix accurately represents the capacities
 *   of the edges.
 */

#include "FordFulkerson.h"
#include <stdexcept>
#include <iostream>
#include <climits>

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
FordFulkerson::FordFulkerson(Graph &graph) : graph(graph)
{
    try
    {
        // Initialize the depth and maxFlow vectors
        initializeMaxFlow();
        initializeDepth();
    }
    catch (const std::exception &e)
    {
        // Output an error message if initialization fails
        std::cerr
            << "ERROR: Error during initialization: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error during initialization: " +
                          std::string(e.what()));
    }
}

/**
 * Calculates the maximum flow in the flow network using the
 * Ford-Fulkerson algorithm.
 *
 * Method Name: calculateMaxFlow
 *
 * Purpose: Calculates the maximum flow in the flow network from the
 * source to the sink node.
 *
 * Parameters:
 * - source: An integer representing the source node in the flow
 *   network.
 * - sink: An integer representing the sink node in the flow network.
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
void FordFulkerson::calculateMaxFlow(int source,
                                     int sink)
{
    try
    {
        // Check if source and sink nodes are within valid range
        if (source < 0 ||
            source >= graph.getNodes() ||
            sink < 0 ||
            sink >= graph.getNodes())
        {
            // Output an error message if source or sink is out of
            // valid range
            std::cerr
                << "ERROR: Source or sink is out of valid range."
                << std::endl;
            throw std::
                invalid_argument("Source or sink is out of valid range.");
        }

        // Continue finding level graphs and augmenting paths
        while (levelGraph(source, sink))
        {
            // Get the adjacency matrix from the graph
            maxFlow = graph.getAdjacencyMatrix();
            std::vector<int> path;

            // Augment flow along the found path
            augmentFlowAlongPath(path, source, sink);
        }
    }
    catch (const std::exception &e)
    {
        // Output an error message if max flow calculation fails
        std::cerr
            << "ERROR: Error in calculateMaxFlow: "
            << e.what()
            << std::endl;
        throw std::runtime_error("Error in calculateMaxFlow: " +
                                 std::string(e.what()));
    }
}

/**
 * Constructs a level graph from the flow network to facilitate flow
 * calculations.
 *
 * Method Name: levelGraph
 *
 * Purpose: Constructs a level graph to determine if the sink node is
 * reachable from the source node.
 *
 * Parameters:
 * - source: An integer representing the source node in the flow
 *   network.
 * - sink: An integer representing the sink node in the flow network.
 *
 * Returns: A boolean value indicating if the sink node is reachable
 * from the source node.
 *
 * Preconditions:
 * - The source and sink nodes are within the valid range of the
 *   graph.
 *
 * Postconditions:
 * - The depth vector is updated with the depth of each node in the
 *   level graph.
 * - The function returns true if the sink node is reachable, false
 *   otherwise.
 * - An exception is thrown if the level graph construction process
 *   fails.
 */
bool FordFulkerson::levelGraph(int source, int sink)
{
    try
    {
        int totalNodes = graph.getNodes();

        // Initialize BFS queue and depth vector
        std::vector<int> bfsQueue(totalNodes);
        int front = 0, back = 0;

        // Set the depth of the source node to 0 and add it to the BFS
        // queue
        depth.assign(totalNodes, -1);
        depth[source] = 0;
        bfsQueue[back++] = source;

        // Continue while there are nodes in the BFS queue
        while (front < back)
        {
            // Get the current node from the front of the queue
            int currentNode = bfsQueue[front++];

            // Iterate over the adjacent nodes of the current node
            for (int adjacent : graph.findAdjacentNodes(currentNode))
            {
                // Check if the adjacent node has not been visited and
                // there is available capacity
                if (depth[adjacent] == -1 &&
                    graph.getAdjacencyMatrix()[currentNode][adjacent] > 0)
                {
                    // Set the depth of the adjacent node and add it
                    // to the BFS queue
                    depth[adjacent] = depth[currentNode] + 1;

                    // Check if the adjacent node is the sink node
                    if (adjacent == sink)
                    {
                        // Sink is reachable
                        return true;
                    }
                    bfsQueue[back++] = adjacent;
                }
            }
        }

        // Sink is not reachable
        return false;
    }
    catch (const std::exception &e)
    {
        // Output an error message if level graph calculation fails
        std::cerr
            << "ERROR: Error in levelGraph: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in levelGraph: " +
                          std::string(e.what()));
    }
}

/**
 * Finds an augmenting path from the source to the sink node in the
 * flow network.
 *
 * Method Name: findAugmentingPath
 *
 * Purpose: Finds an augmenting path from the source to the sink node
 * in the flow network.
 *
 * Parameters:
 * - path: A vector of integers to store the nodes in the augmenting
 *   path.
 * - source: An integer representing the source node in the flow
 *   network.
 * - sink: An integer representing the sink node in the flow network.
 *
 * Returns: A boolean value indicating if an augmenting path is found.
 *
 * Preconditions:
 * - The source and sink nodes are within the valid range of the
 *   graph.
 *
 * Postconditions:
 * - The path vector is updated with the nodes in the augmenting path.
 * - The function returns true if an augmenting path is found, false
 *   otherwise.
 * - An exception is thrown if finding an augmenting path fails.
 */
bool FordFulkerson::findAugmentingPath(std::vector<int> &path,
                                       int source,
                                       int sink)
{
    try
    {
        // Initialize the current node to the source node and
        // backtracking flag to false
        int currentNode = source;
        bool backtracking = false;

        // Continue while the current node is not the sink node
        while (currentNode != sink)
        {
            // Find the next node in the path
            if (!findNextNodeInPath(currentNode,
                                    path,
                                    backtracking,
                                    source))
            {
                return false;
            }

            // Check if the current node is the sink node
            if (currentNode == sink)
            {
                // Add the sink node to the path
                path.push_back(sink);
                return true;
            }
        }

        // Sink node is not reachable
        return false;
    }
    catch (const std::exception &e)
    {
        // Output an error message if finding an augmenting path fails
        std::cerr
            << "ERROR: Error in findAugmentingPath: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in findAugmentingPath: " +
                          std::string(e.what()));
    }
}

/**
 * Updates the residual graph with the flow along the augmenting path.
 *
 * Method Name: updateResidualGraph
 *
 * Purpose: Updates the residual graph with the flow along the
 * augmenting path.
 *
 * Parameters:
 * - src: An integer representing the source node in the flow network.
 * - dst: An integer representing the destination node in the flow
 *   network.
 *
 * Preconditions:
 * - The source and destination nodes are within the valid range of
 *   the graph.
 *
 * Postconditions:
 * - The residual graph is updated with the flow along the augmenting
 *   path.
 * - An exception is thrown if updating the residual graph fails.
 */
void FordFulkerson::updateResidualGraph(int src,
                                        int dst)
{
    try
    {
        // Check if source and destination nodes are within valid
        // range
        if (src < 0 ||
            src >= graph.getNodes() ||
            dst < 0 ||
            dst >= graph.getNodes())
        {
            // Output an error message if source or destination node
            // is out of valid range
            std::cerr
                << "ERROR: Source or destination node is out of valid range."
                << std::endl;
            throw std::
                out_of_range("Source or destination node is out of valid range.");
        }

        // Update the residual graph with the flow along the path
        graph.adjustAdjacencyMatrix()[dst][src] += 1;
        graph.adjustAdjacencyMatrix()[src][dst] -= 1;
    }
    catch (const std::exception &e)
    {
        // Output an error message if updating the residual graph
        // fails
        std::cerr
            << "ERROR: Error in updateResidualGraph: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in updateResidualGraph: " +
                          std::string(e.what()));
    }
}

/**
 * Clears the max flow values at the specified node in the flow
 * network.
 *
 * Method Name: clearMaxFlowAtNode
 *
 * Purpose: Clears the max flow values at the specified node in the
 * flow network.
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
 * - An exception is thrown if clearing the max flow at a node fails.
 */
void FordFulkerson::clearMaxFlowAtNode(int node)
{
    try
    {
        // Clear the max flow values at the specified node
        for (int i = 0; i < graph.getNodes(); ++i)
        {
            maxFlow[i][node] = 0;
        }
    }
    catch (const std::exception &e)
    {
        // Output an error message if clearing max flow at a node
        // fails
        std::cerr
            << "ERROR: Error in clearMaxFlowAtNode: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in clearMaxFlowAtNode: " +
                          std::string(e.what()));
    }
}

/**
 * Initializes the depth vector with the total number of nodes in the
 * flow network.
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
 * - The depth vector is initialized with the total number of nodes.
 * - An exception is thrown if initializing the depth vector fails.
 */
void FordFulkerson::initializeDepth()
{
    try
    {
        // Initialize the depth vector with the total number of nodes
        int totalNodes = graph.getNodes();
        depth.resize(totalNodes);
    }
    catch (const std::exception &e)
    {
        // Output an error message if initializing depth fails
        std::cerr
            << "ERROR: Error in initializeDepth: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in initializeDepth: " +
                          std::string(e.what()));
    }
}

/**
 * Initializes the max flow matrix with the total number of nodes in
 * the flow network.
 *
 * Method Name: initializeMaxFlow
 *
 * Purpose: Initializes the max flow matrix with the total number of
 * nodes in the flow network.
 *
 * Preconditions:
 * - The graph object is initialized with valid data.
 *
 * Postconditions:
 * - The max flow matrix is initialized with the total number of
 *   nodes.
 * - An exception is thrown if initializing the max flow matrix fails.
 */
void FordFulkerson::initializeMaxFlow()
{
    try
    {
        // Initialize the max flow matrix with the total number of
        // nodes
        int totalNodes = graph.getNodes();
        maxFlow.resize(totalNodes, std::vector<int>(totalNodes, 0));
    }
    catch (const std::exception &e)
    {
        // Output an error message if initializing max flow fails
        std::cerr
            << "ERROR: Error in initializeMaxFlow: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in initializeMaxFlow: " +
                          std::string(e.what()));
    }
}

/**
 * Finds the next node in the path for the Ford-Fulkerson algorithm.
 *
 * Method Name: findNextNodeInPath
 *
 * Purpose: Finds the next node in the path for the Ford-Fulkerson
 * algorithm.
 *
 * Parameters:
 * - node: A reference to an integer representing the current node in
 *   the path.
 * - path: A reference to a vector of integers storing the nodes in
 *   the path.
 * - backtracking: A reference to a boolean flag indicating if
 *   backtracking is required.
 * - source: An integer representing the source node in the flow
 *   network.
 *
 * Returns: A boolean value indicating if the next node in the path is
 * found.
 *
 * Preconditions:
 * - The current node is within the valid range of the graph.
 *
 * Postconditions:
 * - The path vector is updated with the nodes in the path.
 * - The backtracking flag is set to true if backtracking is required.
 * - The function returns true if the next node in the path is found,
 *   false otherwise.
 * - An exception is thrown if finding the next node in the path
 *   fails.
 */
bool FordFulkerson::findNextNodeInPath(int &node,
                                       std::vector<int> &path,
                                       bool &backtracking,
                                       int source)
{
    try
    {
        // Check if backtracking is required
        if (backtracking)
        {
            backtracking = false;
        }
        else
        {
            // Add the current node to the path
            path.push_back(node);
        }

        bool advanced = false;

        // Iterate over the adjacent nodes of the current node
        for (int neighbor : graph.findAdjacentNodes(node))
        {
            // Check if the neighbor is the next node in the path
            if (depth[node] + 1 == depth[neighbor] &&
                maxFlow[node][neighbor] > 0)
            {
                // Update the current node and set the advanced flag
                // to true
                node = neighbor;
                advanced = true;
                break;
            }
        }

        // Check if the current node is the source node or no path is
        // found
        if (advanced)
        {
            // Successfully advanced to the next node
            return true;
        }

        // Check if the current node is the source node
        if (node == source)
        {
            // Reached the source, no augmenting path found
            return false;
        }

        // Clear the max flow at the current node and backtrack
        clearMaxFlowAtNode(node);

        // Remove the current node from the path and update the
        // current node
        path.pop_back();

        // Check if the path is empty
        if (!path.empty())
        {
            node = path.back();
        }

        // Backtrack to the previous node
        backtracking = true;
        return true;
    }
    catch (const std::exception &e)
    {
        // Output an error message if finding the next node in the
        // path fails
        std::cerr
            << "ERROR: Error in findNextNodeInPath: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in findNextNodeInPath: " +
                          std::string(e.what()));
    }
}

/**
 * Augments the flow along the found path in the flow network.
 *
 * Method Name: augmentFlowAlongPath
 *
 * Purpose: Augments the flow along the found path in the flow
 * network.
 *
 * Parameters:
 * - path: A reference to a vector of integers storing the nodes in
 *   the augmenting path.
 * - source: An integer representing the source node in the flow
 *   network.
 * - sink: An integer representing the sink node in the flow network.
 *
 * Preconditions:
 * - The path vector contains the nodes in the augmenting path.
 *
 * Postconditions:
 * - The flow along the path is augmented in the flow network.
 * - The residual graph is updated with the flow values.
 * - An exception is thrown if augmenting flow along the path fails.
 */
void FordFulkerson::augmentFlowAlongPath(std::vector<int> &path,
                                         int source,
                                         int sink)
{
    try
    {
        // Continue while there is an augmenting path
        while (findAugmentingPath(path, source, sink))
        {
            // Find the maximum flow along the path
            int pathFlow = INT_MAX;

            // Iterate over the nodes in the path to find the maximum
            // flow
            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                // Get the nodes in the path
                int u = path[i];
                int v = path[i + 1];
                pathFlow = std::min(pathFlow, maxFlow[u][v]);
            }

            // Update the flow along the path
            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                // Get the nodes in the path
                int u = path[i];
                int v = path[i + 1];
                updateResidualGraph(u, v);
            }

            // Clear the path and continue finding augmenting paths
            path.clear();
        }
    }
    catch (const std::exception &e)
    {
        // Output an error message if augmenting flow along the path
        // fails
        std::cerr
            << "ERROR: Error in augmentFlowAlongPath: "
            << e.what()
            << std::endl;
        throw std::
            runtime_error("Error in augmentFlowAlongPath: " +
                          std::string(e.what()));
    }
}
