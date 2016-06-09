/**
 * @file    sudoku.cpp
 * @brief   This program tests a genetic algorithm as a solution for solving a
 *          Sudoku puzzle. The solution, therefore, is not as important as the
 *          behavior of the algorithm in approaching a solution.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#include "GeneticAlgorithm.h"

using namespace std;

const int POPSIZE = 750, MAXGENS = 30000;


/*
 * 
 */
int main(int argc, char** argv)
{
    Puzzle test;
    Puzzle fit;
    srand(time(NULL));

    cin >> test;
    GeneticAlgorithm tryit(test, atoi(argv[1]), atoi(argv[2]));
    //GeneticAlgorithm tryit(test, POPSIZE, MAXGENS);
    fit = tryit.evolve();
    fit.display();
    cout << "Fitness: " << fit.fitness() << endl;

    return (EXIT_SUCCESS);
}
