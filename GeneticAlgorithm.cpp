/**
 * @file    GeneticAlgorithm.cpp
 * @brief   Apply a genetic algorithm on a population of puzzles to evolve a
 *          solution.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#include "GeneticAlgorithm.h"


/** Default constructor.
 */
GeneticAlgorithm::GeneticAlgorithm() : popSize(0), maxGens(0), preGen()
{
} // end default constructor

/** Constructor.
 * @param init  Initial puzzle, the one to be solved.
 * @param pop  Size of the population to have each generation.
 * @param gens  Maximum number of generations before giving up.
 */
GeneticAlgorithm::GeneticAlgorithm(Puzzle init, int pop, int gens) :
                         preGen(init), popSize(pop), maxGens(gens)
{
} // end constructor

/** Copy constructor.
 * @param orig  The population to be copied.
 */
GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& orig) :
    popSize(orig.popSize), maxGens(orig.maxGens), preGen(orig.preGen)
{
} // end copy constructor

/** Destructor.
 */
GeneticAlgorithm::~GeneticAlgorithm()
{
} // end destructor

/** Attempt to evolve a solution to a Sudoku puzzle. Stops if a true solution
 *  is found.
 * @pre None.
 * @post A solution that is close to satisfying the rules of Sudoku is found.
 * @return The most fit solution that evolved.
 */
Puzzle GeneticAlgorithm::evolve(void)
{
    bool success = false;
    Population current;

    current.reserve(popSize);
    populate(current);

    for (int i = 0; i < maxGens && !success; ++i)
    {
        success = current.deleteWorst() == IDEAL;   // perfect fitness found
        breed(current);
    } // end for (int i = 0)

    return current.front();
} // end evolve()

/** Generate the initial, random population of potential solutions.
 * @param pop  The population to fill with potential solutions.
 * @pre None.
 * @post pop contains popSize Puzzles with random attampts at solutions.
 */
void GeneticAlgorithm::populate(Population& pop)
{
    for (int i = 0; i < popSize; ++i)
    {
        pop.push_back(mutate(preGen, 1.0));
    } // end for (int i = 0)
} // end populate()

/** Completely fills a population that is only at 10% of its maximum size. The
 *  new elements are mutated from the original elements.
 * @param pop  The population to refill.
 * @pre pop contains popSize / 10 elements.
 * @post pop contains popSize elements, 90% of which are derived from the
 *       initial 10%.
 */
void GeneticAlgorithm::breed(Population& pop)
{
    Population::iterator parent = pop.begin();

    for (int i = pop.size(); i > 0; --i, ++parent)
    {
        for (int j = 0; j < 9; ++j)
        {
            pop.push_back(mutate(*parent, MUTANTINESS));
        } // end for (int j = 0)
    } // end for (int i = 0)
} // end breed(Population&)

/** Mutate the elements of a single Puzzle. First, likelihood of mutation is
 *  checked. Then, if mutation occurs, a replacement is randomly selected. The
 *  replacement may be the same as the original.
 * @param parent  The Puzzle on which to base the mutation.
 * @param chance  The likelihood of mutation from 0 (why did you call mutate
 *                with no chance of mutation?) and 1 (always mutate). Anything
 *                greater than 1 will be treated as 1.
 * @pre None.
 * @post The parent Puzzle is unchanged.
 * @return A Puzzle based on the input Puzzle, possibly identical.
 */
Puzzle GeneticAlgorithm::mutate(const Puzzle& parent, double chance) const
{
    Puzzle mutant = parent;
    Puzzle::PuzzleIterator parIt = preGen.begin(), mutIt = mutant.begin();

    for (int i = 0; i < ROWS * COLUMNS; ++i, ++parIt, ++mutIt)
    {
        if (*parIt == '0')
        {
            if (chance >= 1.0)
            {
                mutant.setCell(mutIt, randDigit());
            }
            else if (chance > static_cast<double>(rand()) /
                              static_cast<double>(RAND_MAX))
            {
                mutant.setCell(mutIt, randDigit());
            } // end if (chance >= 1.0)
        } // end if (*parIt == '0')
    } // end for (int i = 0)

    return mutant;
} // end mutate(double)

/** Select a digit from 1 to 9 at random.
 * @pre srand() has already been called.
 * @post None.
 * @return The char for an ASCII digit in the range 1-9, inclusive.
 */
char GeneticAlgorithm::randDigit(void) const
{
    double range = (floor((static_cast<double>(rand()) /
                           static_cast<double>(RAND_MAX)) * 9.0));
    if (range < 1.0)
    {
        return '1';
    }
    else if (range < 2.0)
    {
        return '2';
    }
    else if (range < 3.0)
    {
        return '3';
    }
    else if (range < 4.0)
    {
        return '4';
    }
    else if (range < 5.0)
    {
        return '5';
    }
    else if (range < 6.0)
    {
        return '6';
    }
    else if (range < 7.0)
    {
        return '7';
    }
    else if (range < 8.0)
    {
        return '8';
    }

    return '9';
} // end randDigit()
