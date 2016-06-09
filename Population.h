/**
 * @file    Population.h
 * @brief   Stores a populations of Puzzles to be tested as solutions.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#ifndef _POPULATION_H
#define	_POPULATION_H

#include <algorithm>
#include <vector>

#include "Puzzle.h"

using namespace std;


class Population : public vector<Puzzle>
{
public:

    /** Default constructor.
     */
    Population();

    /** Copy constructor.
     * @param orig  The Population to be copied.
     */
    Population(const Population& orig);

    /** Destructor.
     */
    virtual ~Population();

    /** Remove the 90% of the population with the lowest fitness.
     * @pre None.
     * @post None.
     * @return The fitness of the Puzzle at the head of the Population.
     */
    int deleteWorst(void);

private:

    int bestFitness;

};

#endif	/* _POPULATION_H */
