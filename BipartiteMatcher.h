/*
 * File: BipartiteMatcher.h Author: Nicolas Gioanni Purpose:
 * Declaration of the BipartiteMatcher class for solving the bipartite
 * matching problem using Ford-Fulkerson algorithm.
 *
 * Functionality/Features:
 * - Declare methods for reading graph data from a file.
 * - Declare methods for solving the bipartite matching problem.
 * - Utilize Ford-Fulkerson algorithm to find the maximum matching in
 *   the bipartite graph.
 *
 * Assumptions:
 * - The input file format is correct and contains valid graph data.
 * - The graph data represents a bipartite graph.
 */

#ifndef BIPARTITEMATCHER_H
#define BIPARTITEMATCHER_H

#include "Graph.h"
#include "FordFulkerson.h"
#include "GraphPrepare.h"
#include <memory>

class BipartiteMatcher
{
public:
    /**
     * Constructor for the BipartiteMatcher class.
     *
     * Method Name: BipartiteMatcher
     *
     * Purpose: Initializes a new instance of the BipartiteMatcher
     * class.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - A new instance of the BipartiteMatcher class is created.
     * - The graph and algorithm pointers are set to nullptr.
     */
    BipartiteMatcher();

    /**
     * Reads the graph data from a specified file.
     *
     * Method Name: fileRead
     *
     * Purpose: Reads the graph data from the specified file using the
     * GraphPrepare object.
     *
     * Parameters:
     * - filename: A constant reference to a string representing the
     *   name of the file to read.
     *
     * Preconditions:
     * - The input file is correctly formatted and exists.
     *
     * Postconditions:
     * - The graph data is read from the file and stored in the graph
     *   object.
     * - An exception is thrown if the file reading process fails.
     */
    void fileRead(const std::string &filename);

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
    void solve();

private:
    // Unique pointers to Graph and FordFulkerson objects
    std::unique_ptr<Graph> graph;
    std::unique_ptr<FordFulkerson> algorithm;

    // GraphPrepare object for reading graph data
    GraphPrepare readGraph;
};

#endif