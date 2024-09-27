/*
 * File: Driver.cpp Author: Nicolas Gioanni Purpose: Entry point/test
 * case for the bipartite matching program.
 *
 * Functionality/Features:
 * - Creates a BipartiteMatcher object.
 * - Reads graph data from a specified file.
 * - Solves the bipartite matching problem.
 *
 * Assumptions:
 * - The file "program3data.txt" exists and contains valid graph data.
 * - The graph data file is formatted correctly.
 */

#include <iostream>
#include "BipartiteMatcher.h"

/**
 * Main function of the program.
 *
 * Method Name: main
 *
 * Purpose: Entry point of the program. It creates a BipartiteMatcher
 *          object, reads the graph data from a file, and solves the
 *          bipartite matching problem.
 *
 * Preconditions:
 * - The program must have access to the "program3data.txt" file.
 *
 * Postconditions:
 * - The bipartite matching problem is solved.
 * - If an error occurs, an error message is printed to the standard
 *   error stream.
 */
int main()
{
    try
    {
        // Create a BipartiteMatcher object
        BipartiteMatcher bipartiteSolver;

        // Read the graph data from the specified file
        bipartiteSolver.fileRead("program3data.txt");

        // Solve the bipartite matching problem
        bipartiteSolver.solve();
    }
    catch (...)
    {
        // Output an error message if the program fails
        std::cerr << "Program 3 Failed" << std::endl;
        return 0;
    }

    return 0;
}
