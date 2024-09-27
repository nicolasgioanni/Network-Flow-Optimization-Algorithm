/*
 * File: GraphPrepare.h 
 * Author: Nicolas Gioanni 
 * Purpose: Declaration
 * of the GraphPrepare class for reading and preparing graph 
 * data from a file.
 * 
 * Functionality/Features:
 * - Declare methods for reading graph data from a file.
 * - Declare methods for validating nodes and edges.
 * - Declare methods for reading node names and edges.
 * - Provide access to the number of nodes and node names.
 *
 * Assumptions:
 * - The input file format is correct and contains valid data.
 * - Node names are alphanumeric or spaces and are valid for graph
 *   representation.
 */

#ifndef GRAPHPREPARE_H
#define GRAPHPREPARE_H

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <utility>

class GraphPrepare
{
public:
    /**
     * Constructor for the GraphPrepare class.
     *
     * Method Name: GraphPrepare
     *
     * Purpose: Initializes a new instance of the GraphPrepare class.
     *
     * Preconditions:
     * - None.
     *
     * Postconditions:
     * - A new instance of the GraphPrepare class is created.
     * - The nodes and edges variables are initialized to 0.
     */
    GraphPrepare();

    /**
     * Reads the graph data from a specified file.
     *
     * Method Name: fileRead
     *
     * Purpose: Reads the graph data from the specified file and
     * stores it in the graph object.
     *
     * Parameters:
     * - filename: A constant reference to a string representing the
     *   name of the file to read.
     * - graph: A reference to a Graph object where the graph data
     *   will be stored.
     *
     * Preconditions:
     * - The input file is correctly formatted and exists.
     *
     * Postconditions:
     * - The graph data is read from the file and stored in the graph
     *   object.
     * - An exception is thrown if the file reading process fails.
     */
    void fileRead(const std::string &filename, Graph &graph);

    /**
     * Gets the number of nodes in the graph.
     *
     * Method Name: getNodes
     *
     * Purpose: Gets the number of nodes in the graph.
     *
     * Preconditions:
     * - The graph data is read from the input file.
     *
     * Postconditions:
     * - The number of nodes in the graph is returned.
     */
    int getNodes() const;

    /**
     * Gets the names of the nodes in the graph.
     *
     * Method Name: getNames
     *
     * Purpose: Gets the names of the nodes in the graph.
     *
     * Preconditions:
     * - The graph data is read from the input file.
     *
     * Postconditions:
     * - The names of the nodes in the graph are returned.
     */
    const std::vector<std::string> &getNames() const;

private:
    // The number of nodes in the graph
    int nodes;

    // The number of edges in the graph
    int edges;

    // The names of the nodes in the graph
    std::vector<std::string> names;

    /**
     * Opens a file for reading.
     *
     * Method Name: openFile
     *
     * Purpose: Opens a file with the given filename for reading.
     *
     * Parameters:
     * - filename: A constant reference to a string representing the
     *   name of the file to open.
     * - inputFile: A reference to an input file stream object.
     *
     * Preconditions:
     * - The filename is a valid path to a readable file.
     *
     * Postconditions:
     * - The file is opened successfully for reading.
     * - An exception is thrown if the file cannot be opened.
     */
    void openFile(const std::string &filename,
                  std::ifstream &inputFile);

    /**
     * Reads the number of nodes from the input file.
     *
     * Method Name: readNumberOfNodes
     *
     * Purpose: Reads the number of nodes from the input file.
     *
     * Parameters:
     * - inputFile: A reference to an input file stream object.
     *
     * Preconditions:
     * - The input file is correctly formatted and open.
     *
     * Postconditions:
     * - The number of nodes is read from the file and returned.
     * - An exception is thrown if reading the number of nodes fails.
     */
    int readNumberOfNodes(std::ifstream &inputFile);

    /**
     * Validates the number of nodes.
     *
     * Method Name: validateNodes
     *
     * Purpose: Validates the number of nodes to ensure it is a
     * positive even number.
     *
     * Parameters:
     * - nodes: An integer representing the number of nodes.
     *
     * Preconditions:
     * - The number of nodes is read from the input file.
     *
     * Postconditions:
     * - An exception is thrown if the number of nodes is invalid.
     */
    void validateNodes(int nodes);

    /**
     * Reads the number of edges from the input file.
     *
     * Method Name: readNumberOfEdges
     *
     * Purpose: Reads the number of edges from the input file.
     *
     * Parameters:
     * - inputFile: A reference to an input file stream object.
     *
     * Preconditions:
     * - The input file is correctly formatted and open.
     *
     * Postconditions:
     * - The number of edges is read from the file and returned.
     * - An exception is thrown if reading the number of edges fails.
     */
    int readNumberOfEdges(std::ifstream &inputFile);

    /**
     * Validates the number of edges.
     *
     * Method Name: validateEdges
     *
     * Purpose: Validates the number of edges to ensure it is a
     * positive number.
     *
     * Parameters:
     * - edges: An integer representing the number of edges.
     *
     * Preconditions:
     * - The number of edges is read from the input file.
     *
     * Postconditions:
     * - An exception is thrown if the number of edges is invalid.
     */
    void validateEdges(int edges);

    /**
     * Reads the names of the nodes from the input file.
     *
     * Method Name: readNodeNames
     *
     * Purpose: Reads the names of the nodes from the input file and
     * stores them in the names vector.
     *
     * Parameters:
     * - inputFile: A reference to an input file stream object.
     * - nodes: An integer representing the number of nodes.
     *
     * Preconditions:
     * - The number of nodes is read from the input file.
     *
     * Postconditions:
     * - The names of the nodes are read from the file and stored in
     *   the names vector.
     * - An exception is thrown if reading the node names fails.
     */
    void readNodeNames(std::ifstream &inputFile, int nodes);

    /**
     * Validates a node name by removing non-alphanumeric characters.
     *
     * Method Name: validateName
     *
     * Purpose: Validates a node name by removing non-alphanumeric
     * characters.
     *
     * Parameters:
     * - name: A constant reference to a string representing the name
     *   of the node.
     *
     * Preconditions:
     * - The name of the node is read from the input file.
     *
     * Postconditions:
     * - The name is cleansed by removing non-alphanumeric characters
     *   and returned.
     */
    std::string validateName(const std::string &name);

    /**
     * Reads the edges from the input file and creates them in the
     * graph.
     *
     * Method Name: readEdges
     *
     * Purpose: Reads the edges from the input file and creates them
     * in the graph.
     *
     * Parameters:
     * - inputFile: A reference to an input file stream object.
     * - edges: An integer representing the number of edges.
     * - graph: A reference to a Graph object where the edges will be
     *   created.
     *
     * Preconditions:
     * - The number of edges is read from the input file.
     *
     * Postconditions:
     * - The edges are read from the file and created in the graph.
     * - An exception is thrown if reading the edges fails.
     */
    void readEdges(std::ifstream &inputFile,
                   int edges,
                   Graph &graph);

    /**
     * Parses an edge string to extract the edge nodes.
     *
     * Method Name: parseEdge
     *
     * Purpose: Parses an edge string to extract the edge nodes.
     *
     * Parameters:
     * - edge: A constant reference to a string representing the edge.
     *
     * Preconditions:
     * - The edge string is read from the input file.
     *
     * Postconditions:
     * - The edge nodes are extracted from the edge string and
     *   returned as a pair.
     * - An exception is thrown if the edge is invalid.
     */
    std::pair<int, int> parseEdge(const std::string &edge);
};

#endif