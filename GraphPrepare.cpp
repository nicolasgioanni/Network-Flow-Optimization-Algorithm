/*
 * File: GraphPrepare.cpp Author: Nicolas Gioanni Purpose:
 * Implementation of the GraphPrepare class, providing methods for
 * reading and preparing graph data from a file.
 *
 * Functionality/Features:
 * - Read graph data from a specified file.
 * - Validate the number of nodes and edges.
 * - Read and cleanse node names.
 * - Read edges and create them in the graph.
 * - Provide access to the number of nodes and node names.
 *
 * Assumptions:
 * - The input file is correctly formatted and exists.
 * - Node names are alphanumeric or spaces, and are valid for graph
 *   representation.
 */

#include "GraphPrepare.h"
#include <iostream>
#include <stdexcept>

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
GraphPrepare::GraphPrepare() : nodes(0), edges(0) {}

/**
 * Reads the graph data from a specified file.
 *
 * Method Name: fileRead
 *
 * Purpose: Reads the graph data from the specified file and stores it
 * in the graph object.
 *
 * Parameters:
 * - filename: A constant reference to a string representing the name
 *   of the file to read.
 * - graph: A reference to a Graph object where the graph data will be
 *   stored.
 *
 * Preconditions:
 * - The input file is correctly formatted and exists.
 *
 * Postconditions:
 * - The graph data is read from the file and stored in the graph
 *   object.
 * - An exception is thrown if the file reading process fails.
 */
void GraphPrepare::fileRead(const std::string &filename,
                            Graph &graph)
{
    std::ifstream inputFile;
    try
    {
        // Open the file and read the graph data
        openFile(filename, inputFile);

        // Read the number of nodes from the file
        nodes = readNumberOfNodes(inputFile);
        validateNodes(nodes);
        graph = Graph(nodes);
        names.resize(nodes + 1);

        // Read the names of the nodes from the file
        readNodeNames(inputFile, nodes);

        // Read the number of edges from the file
        edges = readNumberOfEdges(inputFile);
        validateEdges(edges);
        readEdges(inputFile, edges, graph);
    }
    catch (...)
    {
        // Close the file and rethrow the exception
        if (inputFile.is_open())
        {
            inputFile.close();
        }
        std::cerr
            << "ERROR: Function fileRead failed."
            << std::endl;
        throw std::runtime_error("Function fileRead failed.");
    }

    // Close the file after reading
    inputFile.close();
    return;
}

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
int GraphPrepare::getNodes() const
{
    return nodes;
}

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
const std::vector<std::string> &GraphPrepare::getNames()
    const
{
    return names;
}

/**
 * Opens a file for reading.
 *
 * Method Name: openFile
 *
 * Purpose: Opens a file with the given filename for reading.
 *
 * Parameters:
 * - filename: A constant reference to a string representing the name
 *   of the file to open.
 * - inputFile: A reference to an input file stream object.
 *
 * Preconditions:
 * - The filename is a valid path to a readable file.
 *
 * Postconditions:
 * - The file is opened successfully for reading.
 * - An exception is thrown if the file cannot be opened.
 */
void GraphPrepare::openFile(const std::string &filename,
                            std::ifstream &inputFile)
{
    // Open the file with the given filename
    inputFile.open(filename);

    // Check if the file was opened successfully
    if (!inputFile.is_open())
    {
        // Output an error message if the file could not be opened
        std::cerr << "ERROR: Error opening the file." << std::endl;
        throw std::runtime_error("Error opening the file.");
    }

    // Check if the file is empty
    if (inputFile.peek() == std::ifstream::traits_type::eof())
    {
        inputFile.close();

        // Output an error message if the file is empty
        std::cerr << "ERROR: Empty File." << std::endl;
        throw std::runtime_error("Empty File.");
    }
}

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
int GraphPrepare::readNumberOfNodes(std::ifstream &inputFile)
{
    std::string line;

    // Read the number of nodes from the file
    if (std::getline(inputFile, line))
    {
        return std::stoi(line);
    }

    // Output an error message if reading the number of nodes failed
    std::cerr
        << "ERROR: Reading number of nodes failed."
        << std::endl;
    throw std::runtime_error("Reading number of nodes failed.");
}

/**
 * Validates the number of nodes.
 *
 * Method Name: validateNodes
 *
 * Purpose: Validates the number of nodes to ensure it is a positive
 * even number.
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
void GraphPrepare::validateNodes(int nodes)
{
    // Check if the number of nodes is valid
    if (nodes < 2 || nodes % 2 != 0)
    {
        // Output an error message if the number of nodes is invalid
        std::cerr
            << "ERROR: There should be a positive even number of nodes."
            << std::endl;
        throw std::
            invalid_argument("There should be a positive even number of nodes.");
    }
}

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
int GraphPrepare::readNumberOfEdges(std::ifstream &inputFile)
{
    std::string line;

    // Read the number of edges from the file
    if (std::getline(inputFile, line))
    {
        return std::stoi(line);
    }

    // Output an error message if reading the number of edges failed
    std::cerr
        << "ERROR: Reading number of edges failed."
        << std::endl;
    throw std::runtime_error("Reading number of edges failed.");
}

/**
 * Validates the number of edges.
 *
 * Method Name: validateEdges
 *
 * Purpose: Validates the number of edges to ensure it is a positive
 * number.
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
void GraphPrepare::validateEdges(int edges)
{
    // Check if the number of edges is valid
    if (edges < 1)
    {
        // Output an error message if the number of edges is invalid
        std::cerr
            << "ERROR: Edges must be greater than 0."
            << std::endl;
        throw std::
            invalid_argument("Edges must be greater than 0.");
    }
}

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
 * - The names of the nodes are read from the file and stored in the
 *   names vector.
 * - An exception is thrown if reading the node names fails.
 */
void GraphPrepare::readNodeNames(std::ifstream &inputFile,
                                 int nodes)
{
    std::string line;

    // Read the names of the nodes from the file
    for (int i = 1; i <= nodes; ++i)
    {
        // Check if the line is valid
        if (std::getline(inputFile, line))
        {
            // Validate the name and store it in the names vector
            std::string cleanName = validateName(line);

            // Check if the name is valid
            if (cleanName.empty())
            {
                // Output an error message if the name is invalid
                std::cerr
                    << "ERROR: Name is invalid."
                    << std::endl;
                throw std::
                    invalid_argument("Name is invalid.");
            }

            // Store the name in the names vector
            names[i] = cleanName;
        }
        else
        {
            // Output an error message if reading the node name failed
            std::cerr
                << "ERROR: Reading node name failed."
                << std::endl;
            throw std::
                runtime_error("Reading node name failed.");
        }
    }
}

/**
 * Validates a node name by removing non-alphanumeric characters.
 *
 * Method Name: validateName
 *
 * Purpose: Validates a node name by removing non-alphanumeric
 * characters.
 *
 * Parameters:
 * - name: A constant reference to a string representing the name of
 *   the node.
 *
 * Preconditions:
 * - The name of the node is read from the input file.
 *
 * Postconditions:
 * - The name is cleansed by removing non-alphanumeric characters and
 *   returned.
 */
std::string GraphPrepare::validateName(const std::string &name)
{
    std::string cleanName;

    // Cleanse the name by removing non-alphanumeric characters
    for (char ch : name)
    {
        // Check if the character is alphanumeric or a space
        if (std::isalnum(ch) ||
            (!cleanName.empty() &&
             ch == ' ' &&
             cleanName.back() != ' '))
        {
            // Append the character to the clean name
            cleanName += ch;
        }
    }

    // Return the validated name
    return cleanName;
}

/**
 * Reads the edges from the input file and creates them in the graph.
 *
 * Method Name: readEdges
 *
 * Purpose: Reads the edges from the input file and creates them in
 * the graph.
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
void GraphPrepare::readEdges(std::ifstream &inputFile,
                             int edges,
                             Graph &graph)
{
    std::string line;

    // Read the edges from the file
    for (int i = 0; i < edges; ++i)
    {
        // Check if the line is validq
        if (std::getline(inputFile, line))
        {
            // Parse the edge nodes and create an edge in the graph
            auto edgeNodes = parseEdge(line);
            graph.createEdge(edgeNodes.first,
                             edgeNodes.second, 1);
        }
        else
        {
            // Output an error message if reading the edge failed
            std::cerr
                << "ERROR: Reading edge Failed."
                << std::endl;
            throw std::
                runtime_error("Reading edge Failed.");
        }
    }
}

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
 * - The edge nodes are extracted from the edge string and returned as
 *   a pair.
 * - An exception is thrown if the edge is invalid.
 */
std::pair<int, int> GraphPrepare::parseEdge(
    const std::string &edge)
{
    // Create a string stream from the edge string
    std::istringstream ss(edge);
    int node1, node2;

    // Parse the edge nodes
    if (!(ss >> node1 >> node2))
    {
        // Output an error message if the edge is invalid
        std::cerr << "ERROR: Edge is Invalid." << std::endl;
        throw std::invalid_argument("Edge is Invalid.");
    }

    // Return the edge nodes
    return {node1, node2};
}
