/**
 * @file    GeneticAlgorithm.cpp
 * @brief   Apply a genetic algorithm on a population of puzzles to evolve a
 *          solution.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#ifndef _GENETICALGORITHM_H
#define	_GENETICALGORITHM_H

#include <cmath>
#include <cstdlib>

#include "Population.h"

const int IDEAL = ROWS * COLUMNS;
const double MUTANTINESS = 0.05;


class GeneticAlgorithm
{
public:

    /** Default constructor.
     */
    GeneticAlgorithm();

    /** Constructor.
     * @param init  Initial puzzle, the one to be solved.
     * @param pop  Size of the population to have each generation.
     * @param gens  Maximum number of generations before giving up.
     */
    GeneticAlgorithm(Puzzle init, int pop, int gens);

    /** Copy constructor.
     * @param orig  The population to be copied.
     */
    GeneticAlgorithm(const GeneticAlgorithm& orig);

    /** Destructor.
     */
    virtual ~GeneticAlgorithm();
    
    /** Attempt to evolve a solution to a Sudoku puzzle. Stops if a true
     *  solution is found.
     * @pre None.
     * @post A solution that is close to satisfying the rules of Sudoku is
     *       found.
     * @return The most fit solution that evolved.
     */
    Puzzle evolve(void);

private:

    int popSize;
    int maxGens;
    Puzzle preGen;

    /** Generate the initial, random population of potential solutions.
     * @param pop  The population to fill with potential solutions.
     * @pre None.
     * @post pop contains popSize Puzzles with random attampts at solutions.
     */
    void populate(Population& pop);

    /** Completely fills a population that is only at 10% of its maximum size.
     *  The new elements are mutated from the original elements.
     * @param pop  The population to refill.
     * @pre pop contains popSize / 10 elements.
     * @post pop contains popSize elements, 90% of which are derived from the
     *       initial 10%.
     */
    void breed(Population& pop);

    /** Mutate the elements of a single Puzzle. First, likelihood of mutation
     *  is checked. Then, if mutation occurs, a replacement is randomly
     *  selected. The replacement may be the same as the original.
     * @param parent  The Puzzle on which to base the mutation.
     * @param chance  The likelihood of mutation from 0 (why did you call
     *                mutate with no chance of mutation?) and 1 (always
     *                mutate). Anything greater than 1 will be treated as 1.
     * @pre None.
     * @post The parent Puzzle is unchanged.
     * @return A Puzzle based on the input Puzzle, possibly identical.
     */
    Puzzle mutate(const Puzzle& parent, double chance) const;

    /** Select a digit from 1 to 9 at random.
     * @pre srand() has already been called.
     * @post None.
     * @return The char for an ASCII digit in the range 1-9, inclusive.
     */
    char randDigit(void) const;

};

#endif	/* _GENETICALGORITHM_H */
