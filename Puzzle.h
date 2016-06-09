/**
 * @file    Puzzle.h
 * @brief   This class holds a representation of a Sudoku puzzle, which
 *          consists of a 9x9 grid of cells. Each cell may contain a digit from
 *          1 to 9. The goal of the puzzle is to fill in the empty cells with
 *          digits from 1 to 9 so that every cell is full without a digit being
 *          repeated across any row or down any column, or repeated within a
 *          nonet (a 3x3 block that is unique and does not overlap another 3x3
 *          block, so there are nine in the puzzle). This class does not solve
 *          a given puzzle, but it does have methods to determine the fitness
 *          of a given solution. This class also cannot validate a puzzle, so
 *          it is up to the user to input a solvable puzzle with only one
 *          solution. The expected initialization puzzle will be unsolved, but
 *          a puzzle with a tentative solution may also be provided. The cells
 *          that are part of the initial puzzle are marked as such to keep them
 *          separete from cells that are part of a solution. Values of char '0'
 *          represent an empty cell.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 22, 2011
 */

#ifndef _PUZZLE_H
#define	_PUZZLE_H

#include <iostream>

using namespace std;

const int ROWS = 9;
const int COLUMNS = 9;


class Puzzle
{
public:

    //friend class GeneticAlgorithm;
    friend class PuzzleIterator;

    class PuzzleIterator
    {
    public:

        friend class Puzzle;

        /** Default constructor.
         */
        PuzzleIterator();

        /** Constructor.
         * @param aPuzzle  The containing puzzle.
         * @param index  The value of the index to hold.
         */
        PuzzleIterator(const Puzzle *aPuzzle, int index);

        /** Copy constructor.
         * @param orig  The PuzzleIterator to copy.
         */
        PuzzleIterator(const PuzzleIterator& orig);

        /** Destructor.
         */
        virtual ~PuzzleIterator();

        /** Assign an existing PuzzleIterator's values to this object.
         * @param rhs  The PuzzleIterator with the values to be assigned.
         * @pre None
         * @post This object is a duplicate of rhs. rhs is unchanged
         */
        void operator=(const PuzzleIterator& rhs);

        /** Obtain a reference to the item at which this iterator points to.
         * @pre The index of this iterator is within the range of the
         *      containing item. The item at the specified index has been set
         *      to a proper value.
         * @post None
         */
        const char& operator*(void);

        /** Move this iterator to the next index in its container.
         * @pre This iterator is not already beyond the range of the container.
         * @post This iterator points to the item immediately following the
         *       item it originally pointed to.
         * @return Itself.
         */
        PuzzleIterator operator++(void);

        /** Move this iterator a specified number of indexes forward in its
         *  container.
         * @param inc  The amount by which to increase the index.
         * @pre This iterator is not already beyond the range of the container.
         * @post This iterator points to the item inc indexes following the
         *       item it originally pointed to, or it points to the last index.
         * @return Itself.
         */
        PuzzleIterator operator++(int inc);

        /** Move this iterator to the previous index in its container.
         * @pre This iterator is not already at the beginning of the container.
         * @post This iterator points to the item immediately following the
         *       item it originally pointed to.
         * @return Itself.
         */
        PuzzleIterator operator--(void);

        /** Move this iterator a specified number of indexes back in its
         *  container.
         * @param dec  The amount by which to decrease the index.
         * @pre This iterator is not already at the beginning of the container.
         * @post This iterator points to the item dec indexes preceding the
         *       item it originally pointed to, or it points to the first
         *       index.
         * @return Itself.
         */
        PuzzleIterator operator--(int dec);

        /** Compare the position of this iterator with another.
         * @param rhs  The iterator with which to compare.
         * @pre Both iterators reference the same container instance.
         * @post None.
         * @return true if this iterator lies before the input iterator, false
         *         otherwise.
         */
        bool operator<(const PuzzleIterator& rhs) const;

        /** Compare the position of this iterator with another.
         * @param rhs  The iterator with which to compare.
         * @pre Both iterators reference the same container instance.
         * @post None.
         * @return true if this iterator lies after the input iterator, false
         *         otherwise.
         */
        bool operator>(const PuzzleIterator& rhs) const;

        /** Compares this iterator with another for equality.
         * @param rhs  The iterator with which to compare.
         * @pre None.
         * @post None.
         * @return true if this iterator and the input iterator reference the
         *         same container and point to the same index, false otherwise.
         */
        bool operator==(const PuzzleIterator& rhs) const;

        /** Compares this iterator with another for inequality.
         * @param rhs  The iterator with which to compare.
         * @pre None.
         * @post None.
         * @return false if this iterator and the input iterator reference the
         *         same container and point to the same index, true otherwise.
         */
        bool operator!=(const PuzzleIterator& rhs) const;

    private:

        const Puzzle *container;
        int cur;

    };
    
    Puzzle();
    
    /** Copy constructor.
     * @param orig  The Puzzle to copy.
     */
    Puzzle(const Puzzle& orig);
    
    /** Destructor.
     */
    virtual ~Puzzle();

    /** Assign an existing Puzzle's values to this object.
     * @param rhs  The Puzzle with the values to be assigned.
     * @pre None
     * @post This object is a duplicate of rhs. rhs is unchanged
     */
    void operator=(const Puzzle& rhs);
    
    /** Pull a string representing a Puzzle from an input stream.
     * @param input  The stream containing the new puzzle string.
     * @param dest  The Puzzle to be set from the input string (this one).
     * @pre The input stream contains at least 81 ASCII digits, 0-9.
     * @post This Puzzle has been set with the input values. The input stream
     *       has every character up to and including the 81st ASCII digit
     *       removed.
     * @return The istream that was passed in, changed.
     */
    friend istream& operator>>(istream& input, Puzzle& dest);
    
    /** Push a string representing a Puzzle onto an output stream.
     * @param output  The stream to contain the puzzle string.
     * @param source  The Puzzle containing the string to output string (this
     *        one).
     * @pre None.
     * @post The ouput stream contains a string representing a puzzle. Ths
     *       soucre puzzle (this one) remains unchanged.
     * @return The ostream that was passed in, changed.
     */
    friend ostream& operator<<(ostream& output, const Puzzle& source);

    /** Compare the fitness of this Puzzle with the fitness of another.
     * @param rhs  The Puzzle with which to compare fitness.
     * @pre None.
     * @post None.
     * @return true if this Puzzle has higher fitness than the input puzzle,
     *         false otherwise. This is done for purposes of sorting, as
     *         returning the logical result caused sorting to work
     *         unexpectedly.
     */
    bool operator<(const Puzzle& rhs) const;

    /** Compare the fitness of this Puzzle with the fitness of another.
     * @param rhs  The Puzzle with which to compare fitness.
     * @pre None.
     * @post None.
     * @return true if this Puzzle has higher fitness than the input puzzle,
     *         false otherwise. This is done to complement operator<(), which
     *         had to be altered to make sorting work as expected.
     */
    bool operator>(const Puzzle& rhs) const;

    /** Compares this Puzzle with another for equality.
     * @param rhs  The Puzzle with which to compare.
     * @pre None.
     * @post None.
     * @return true if this Puzzle and the input Puzzle contain identical
     *         puzzle strings, false otherwise.
     */
    bool operator==(const Puzzle& rhs) const;

    /** Compares this Puzzle with another for inequality.
     * @param rhs  The Puzzle with which to compare.
     * @pre None.
     * @post None.
     * @return false if this Puzzle and the input Puzzle contain identical
     *         puzzle strings, true otherwise.
     */
    bool operator!=(const Puzzle& rhs) const;
    
    /** Display a puzzle in human-readable format.
     * @pre None.
     * @post None.
     */
    void display(void) const;
    
    /** Returns the fitness of this Puzzle. Fitness is calculated by starting
     *  with 81 (a perfectly solved puzzle) and subtracting 1 for every rule of
     *  Sudoku the puzzle breaks. 1 is subtracted for empty cells, but one
     *  filled cell can multiple rules.
     * @pre None.
     * @post If fitLevel was not previously calculated, it is set.
     * @retunr The fitness of this Puzzle as a solution, from -135 to 81.
     */
    int fitness(void) const;

    /** Provide the size of this Puzzle, indicating the number of empty spaces.
     * @pre None.
     * @post None.
     * @return The number of cells in this Puzzle that are not variable.
     */
    int size(void) const;

    /** Provide an iterator to the first item in this Puzzle.
     * @pre None.
     * @post The returned iterator references the first item in this Puzzle.
     * @return An iterator to the first item in this Puzzle.
     */
    void setCell(const PuzzleIterator& loc, const char& item);

    /** Provide an iterator to the first item in this Puzzle.
     * @pre None.
     * @post The returned iterator references the first item in this Puzzle.
     * @return An iterator to the first item in this Puzzle.
     */
    PuzzleIterator begin(void) const;

    /** Provide an iterator to the last item in this Puzzle.
     * @pre None.
     * @post The returned iterator references the last item in this Puzzle.
     * @return An iterator to the last item in this Puzzle.
     */
    PuzzleIterator end(void) const;
    
private:

    int fitLevel;
    int notSet;
    char content[ROWS * COLUMNS];

    /** Determine the number of times rules are broken by row.
     * @param quality  The initial quality to work back from.
     * @pre None.
     * @post None.
     * @return The input quality minus the number of broken rules by row.
     */
    int fitRow(int quality) const;

    /** Determine the number of times rules are broken by column.
     * @param quality  The initial quality to work back from.
     * @pre None.
     * @post None.
     * @return The input quality minus the number of broken rules by column.
     */
    int fitColumn(int quality) const;

    /** Determine the number of times rules are broken by nonet.
     * @param quality  The initial quality to work back from.
     * @pre None.
     * @post None.
     * @return The input quality minus the number of broken rules by nonet.
     */
    int fitNonet(int quality) const;

};

#endif	/* _PUZZLE_H */
