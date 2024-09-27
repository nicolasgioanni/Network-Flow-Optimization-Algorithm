/*
 * File: BipartiteMatcher.cpp Author: Nicolas Gioanni Purpose:
 * Implementation of the BipartiteMatcher class, providing methods for
 * reading graph data and solving the bipartite matching problem.
 *
 * Functionality/Features:
 * - Read graph data from a specified file.
 * - Solve the bipartite matching problem using the Ford-Fulkerson
 *   algorithm.
 * - Print the results of the matching process.
 *
 * Assumptions:
 * - The input file is correctly formatted and exists.
 * - The graph data represents a bipartite graph.
 * - Node indices and capacities are valid and within expected ranges.
 */

#include "BipartiteMatcher.h"
#include <iostream>
#include <stdexcept>

/**
 * Constructor for the BipartiteMatcher class.
 *
 * Method Name: BipartiteMatcher
 *
 * Purpose: Initializes a new instance of the BipartiteMatcher class.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - A new instance of the BipartiteMatcher class is created.
 * - The graph and algorithm pointers are set to nullptr.
 */
BipartiteMatcher::BipartiteMatcher() : graph(nullptr),
                                       algorithm(nullptr) {}

/**
 * Reads the graph data from a specified file.
 *
 * Method Name: fileRead
 *
 * Purpose: Reads the graph data from the specified file using the
 * GraphPrepare object.
 *
 * Parameters:
 * - filename: A constant reference to a string representing the name
 *   of the file to read.
 *
 * Preconditions:
 * - The input file is correctly formatted and exists.
 *
 * Postconditions:
 * - The graph data is read from the file and stored in the graph
 *   object.
 * - An exception is thrown if the file reading process fails.
 */
void BipartiteMatcher::fileRead(const std::string &filename)
{
    try
    {
        // Create a unique pointer to a Graph object with 0 nodes
        // initially
        graph = std::make_unique<Graph>(0);

        // Read the graph data from the specified file into the graph
        // object
        readGraph.fileRead(filename, *graph);
    }
    catch (const std::exception &e)
    {
        // Output an error message if reading the graph file fails
        std::cerr
            << "ERROR: Failed to read the graph from file: "
            << e.what()
            << std::endl;
        throw;
    }
}

/**
 * Solves the bipartite matching problem using the Ford-Fulkerson
 * algorithm.
 *
 * Method Name: solve
 *
 * Purpose: Solves the bipartite matching problem by finding the
 * maximum flow in the bipartite graph.
 *
 * Preconditions:
 * - The graph data is read and stored in the graph object.
 *
 * Postconditions:
 * - The maximum matching in the bipartite graph is calculated and
 *   printed.
 * - An exception is thrown if the solving process fails.
 */
void BipartiteMatcher::solve()
{
    // Check if the graph is initialized and has nodes
    if (!graph || graph->getNodes() == 0)
    {
        // Output an error message if the graph is not properly
        // initialized
        std::cerr
            << "ERROR: Graph is not initialized properly."
            << std::endl;
        throw;
        return;
    }

    try
    {
        // Get the number of nodes from the readGraph object
        int nodes = readGraph.getNodes();

        // Get the names associated with the nodes
        std::vector<std::string> names = readGraph.getNames();

        // Connect the source and sink nodes in the graph
        graph->connectSourceAndSinkNodes(0, nodes + 1);

        // Create a unique pointer to a FordFulkerson algorithm object
        // using the graph
        algorithm = std::make_unique<FordFulkerson>(*graph);

        // Calculate the maximum flow from the source to the sink node
        algorithm->calculateMaxFlow(0, nodes + 1);

        // Print the results of the matching process
        graph->printResults(names);
    }
    catch (const std::exception &e)
    {
        // Output an error message if the solving process fails
        std::cerr
            << "ERROR: Failed during solving process: "
            << e.what()
            << std::endl;
        throw;
    }
}
