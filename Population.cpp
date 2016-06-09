/**
 * @file    Population.cpp
 * @brief   Stores a populations of Puzzles to be tested as solutions.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#include "Population.h"


/** Default constructor.
 */
Population::Population()
{
} // end default constructor

/** Copy constructor.
 * @param orig  The Population to be copied.
 */
Population::Population(const Population& orig)
{
} // end copy constructor

/** Destructor.
 */
Population::~Population()
{
} // end destructor

/** Remove the 90% of the population with the lowest fitness.
 * @pre None.
 * @post None.
 * @return The fitness of the Puzzle at the head of the Population.
 */
int Population::deleteWorst(void)
{
    int limit = size() / 10;

    sort(begin(), begin() + size() - 1);

    for (int i = size(); i > limit; --i)
    {
        pop_back();
    } // end for (int i = size(); i > limit; --i)

    bestFitness = front().fitness();

    return bestFitness;
} // end deleteWorst(void)
