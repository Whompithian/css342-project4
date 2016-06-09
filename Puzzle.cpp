/**
 * @file    Puzzle.cpp
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

#include "Puzzle.h"


/** Default constructor.
 */
Puzzle::PuzzleIterator::PuzzleIterator() : container(NULL), cur(0)
                                           
{
} // end default constructor

/** Constructor.
 * @param aPuzzle  The containing puzzle.
 * @param index  The value of the index to hold.
 */
Puzzle::PuzzleIterator::PuzzleIterator(const Puzzle *aPuzzle, int index) :
                                          container(aPuzzle), cur(index)
{
} // end constructor

/** Copy constructor.
 * @param orig  The PuzzleIterator to copy.
 */
Puzzle::PuzzleIterator::PuzzleIterator(const PuzzleIterator& orig) :
                          container(orig.container), cur(orig.cur)
{
} // end copy constructor

/** Destructor.
 */
Puzzle::PuzzleIterator::~PuzzleIterator()
{
    container = NULL;
} // end destructor

/** Assign an existing PuzzleIterator's values to this object.
 * @param rhs  The PuzzleIterator with the values to be assigned.
 * @pre None
 * @post This object is a duplicate of rhs. rhs is unchanged
 */
void Puzzle::PuzzleIterator::operator=(const PuzzleIterator& rhs)
{
    container = rhs.container;
    cur = rhs.cur;
} // end operator=(PuzzleIterator& orig)

/** Obtain a reference to the item at which this iterator points to.
 * @pre The index of this iterator is within the range of the containing item.
 *      The item at the specified index has been set to a proper value.
 * @post None
 */
const char& Puzzle::PuzzleIterator::operator*(void)
{
    return container->content[cur];
} // end operator*(void)

/** Move this iterator to the next index in its container.
 * @pre This iterator is not already beyond the range of the container.
 * @post This iterator points to the item immediately following the item it
 *       originally pointed to.
 * @return Itself.
 */
Puzzle::PuzzleIterator Puzzle::PuzzleIterator::operator++(void)
{
    if (cur < ROWS * COLUMNS)
    {
        ++cur;
    } // end if (cur < ROWS * COLUMNS)

    return *this;
} // end operator++(void)

/** Move this iterator a specified number of indexes forward in its container.
 * @param inc  The amount by which to increase the index.
 * @pre This iterator is not already beyond the range of the container.
 * @post This iterator points to the item inc indexes following the item it
 *       originally pointed to, or it points to the last index.
 * @return Itself.
 */
Puzzle::PuzzleIterator Puzzle::PuzzleIterator::operator++(int inc)
{
    if (cur + inc < ROWS * COLUMNS)
    {
        cur += inc;
    }
    else
    {
        cur = ROWS * COLUMNS - 1;
    } // end if (cur + inc < ROWS * COLUMNS)

    return *this;
} // end operator++(int)

/** Move this iterator to the previous index in its container.
 * @pre This iterator is not already at the beginning of the container.
 * @post This iterator points to the item immediately following the item it
 *       originally pointed to.
 * @return Itself.
 */
Puzzle::PuzzleIterator Puzzle::PuzzleIterator::operator--(void)
{
    if (cur > 0)
    {
        --cur;
    } // end if (cur > 0)

    return *this;
} // end operator--(void)

/** Move this iterator a specified number of indexes back in its container.
 * @param dec  The amount by which to decrease the index.
 * @pre This iterator is not already at the beginning of the container.
 * @post This iterator points to the item dec indexes preceding the item it
 *       originally pointed to, or it points to the first index.
 * @return Itself.
 */
Puzzle::PuzzleIterator Puzzle::PuzzleIterator::operator--(int dec)
{
    if (cur - dec > 0)
    {
        cur -= dec;
    } // end if (cur > 0)
    else
    {
        cur = 0;
    }

    return *this;
} // end operator--(int)

/** Compare the position of this iterator with another.
 * @param rhs  The iterator with which to compare.
 * @pre Both iterators reference the same container instance.
 * @post None.
 * @return true if this iterator lies before the input iterator, false
 *         otherwise.
 */
bool Puzzle::PuzzleIterator::operator<(const PuzzleIterator& rhs) const
{
    return cur < rhs.cur;
} // end operator<(PuzzleIterator&)

/** Compare the position of this iterator with another.
 * @param rhs  The iterator with which to compare.
 * @pre Both iterators reference the same container instance.
 * @post None.
 * @return true if this iterator lies after the input iterator, false
 *         otherwise.
 */
bool Puzzle::PuzzleIterator::operator>(const PuzzleIterator& rhs) const
{
    return cur > rhs.cur;
} // end operator>(PuzzleIterator&)

/** Compares this iterator with another for equality.
 * @param rhs  The iterator with which to compare.
 * @pre None.
 * @post None.
 * @return true if this iterator and the input iterator reference the same
 *         container and point to the same index, false otherwise.
 */
bool Puzzle::PuzzleIterator::operator==(const PuzzleIterator& rhs) const
{
    return ((container == rhs.container) && (cur == rhs.cur));
} // end operator==(PuzzleIterator&)

/** Compares this iterator with another for inequality.
 * @param rhs  The iterator with which to compare.
 * @pre None.
 * @post None.
 * @return false if this iterator and the input iterator reference the same
 *         container and point to the same index, true otherwise.
 */
bool Puzzle::PuzzleIterator::operator!=(const PuzzleIterator& rhs) const
{
    return !(*this == rhs);
} // end operator!=(PuzzleIterator&)

/** Default constructor. fitLevel set to 1 beyond max value to indicate it has
 *  not been calculated. Actual fitness is 0.
 */
Puzzle::Puzzle() : fitLevel(ROWS * COLUMNS + 1), notSet(ROWS * COLUMNS)
{
    for (int i = 0; i < ROWS * COLUMNS; ++i)
    {
        content[i] = '0';
    } // end for (int i = 0; i < ROWS * COLUMNS; ++i)
} // end default constructor

/** Copy constructor.
 * @param orig  The Puzzle to copy.
 */
Puzzle::Puzzle(const Puzzle& orig) : fitLevel(orig.fitLevel),
                                         notSet(orig.notSet)
{
    for (int i = 0; i < ROWS * COLUMNS; ++i)
    {
        content[i] = orig.content[i];
    } // end for (int i = 0; i < ROWS * COLUMNS; ++i)
} // end copy constructor

/** Destructor.
 */
Puzzle::~Puzzle()
{
} // end destructor

/** Assign an existing Puzzle's values to this object.
 * @param rhs  The Puzzle with the values to be assigned.
 * @pre None
 * @post This object is a duplicate of rhs. rhs is unchanged
 */
void Puzzle::operator=(const Puzzle& rhs)
{
    for (int i = 0; i < ROWS * COLUMNS; ++i)
    {
        content[i] = rhs.content[i];
    } // end for (int i = 0; i < ROWS * COLUMNS; ++i)

    fitLevel = rhs.fitLevel;
    notSet = rhs.notSet;
} // end operator=(Puzzle&)

/** Pull a string representing a Puzzle from an input stream.
 * @param input  The stream containing the new puzzle string.
 * @param dest  The Puzzle to be set from the input string (this one).
 * @pre The input stream contains at least 81 ASCII digits, 0-9.
 * @post This Puzzle has been set with the input values. The input stream has
 *       every character up to and including the 81st ASCII digit removed.
 * @return The istream that was passed in, changed.
 */
istream& operator>>(istream& input, Puzzle& dest)
{
    int index = 0;
    char temp;

    dest.notSet = ROWS * COLUMNS;   // all cells initially empty

    // Pull characters from the stream one-at-a-time until 81 digits have been
    // found. All non-digit characters are discarded.
    while(index < ROWS * COLUMNS)
    {
        cin >> temp;

        if (temp == '0')            // empty cell
        {
            dest.content[index++] = temp;
        }
        else if (isdigit(temp))     // fixed value cell
        {
            dest.content[index++] = temp;
            dest.notSet--;
        } // end if (temp == '0')
    } // end while(index < ROWS * COLUMNS)

    return input;
} // end operator>>(istream&, Puzzle&)

/** Push a string representing a Puzzle onto an output stream.
 * @param output  The stream to contain the puzzle string.
 * @param source  The Puzzle containing the string to output string (this one).
 * @pre None.
 * @post The ouput stream contains a string representing a puzzle. Ths soucre
 *       puzzle (this one) remains unchanged.
 * @return The ostream that was passed in, changed.
 */
ostream& operator<<(ostream& output, const Puzzle& source)
{
    for (int i = 0; i < ROWS * COLUMNS; ++i)
    {
        output << source.content[i];
    } // end for (int i = 0; i < ROWS * COLUMNS; ++i)

    return output;
} // end Puzzle::operator<<(ostream&, Puzzle&)

/** Compare the fitness of this Puzzle with the fitness of another.
 * @param rhs  The Puzzle with which to compare fitness.
 * @pre None.
 * @post None.
 * @return true if this Puzzle has higher fitness than the input puzzle, false
 *         otherwise. This is done for purposes of sorting, as returning the
 *         logical result caused sorting to work unexpectedly.
 */
bool Puzzle::operator<(const Puzzle& rhs) const
{
    return fitness() > rhs.fitness();
} // end operator<(Puzzle&)

/** Compare the fitness of this Puzzle with the fitness of another.
 * @param rhs  The Puzzle with which to compare fitness.
 * @pre None.
 * @post None.
 * @return true if this Puzzle has higher fitness than the input puzzle, false
 *         otherwise. This is done to complement operator<(), which had to be
 *         altered to make sorting work as expected.
 */
bool Puzzle::operator>(const Puzzle& rhs) const
{
    return fitness() < rhs.fitness();
} // end operator>(Puzzle&)

/** Compares this Puzzle with another for equality.
 * @param rhs  The Puzzle with which to compare.
 * @pre None.
 * @post None.
 * @return true if this Puzzle and the input Puzzle contain identical puzzle
 *         strings, false otherwise.
 */
bool Puzzle::operator==(const Puzzle& rhs) const
{
    int i = 0;

    while((i < ROWS * COLUMNS) && (rhs.content[i] == content[i]))
    {
        ++i;
    } // end while((i < ROWS * COLUMNS) && (rhs.content[i] == content[i]))

    return i == ROWS * COLUMNS;
} // end operator==(const Puzzle& rhs)

/** Compares this Puzzle with another for inequality.
 * @param rhs  The Puzzle with which to compare.
 * @pre None.
 * @post None.
 * @return false if this Puzzle and the input Puzzle contain identical puzzle
 *         strings, true otherwise.
 */
bool Puzzle::operator!=(const Puzzle& rhs) const
{
    return !(*this == rhs);
} // end operator!=(Puzzle&)

/** Display a puzzle in human-readable format.
 * @pre None.
 * @post None.
 */
void Puzzle::display(void) const
{
    // Construct one row at a time.
    for (int i = 0; i < ROWS * COLUMNS; i += COLUMNS)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            cout << ' ' << content[i + j];
        } // end for (int j = 0; j < COLUMNS; ++j)

        cout << endl;
    } // end for (int i = 0; i < ROWS * COLUMNS; i += COLUMNS)
} // end display()

/** Returns the fitness of this Puzzle. Fitness is calculated by starting with
 *  81 (a perfectly solved puzzle) and subtracting 1 for every rule of Sudoku
 *  the puzzle breaks. 1 is subtracted for empty cells, but one filled cell can
 *  multiple rules.
 * @pre None.
 * @post If fitLevel was not previously calculated, it is set.
 * @retunr The fitness of this Puzzle as a solution, from -135 to 81.
 */
int Puzzle::fitness(void) const
{
    if (fitLevel <= ROWS * COLUMNS)     // fitLevel already calculated
    {
        return fitLevel;
    }
    
    int quality = ROWS * COLUMNS;       // assume perfect fitness

    quality = fitRow(quality);          // check for repeats in rows
    quality = fitColumn(quality);       // check for repeats in columns
    quality = fitNonet(quality);        // check for repeats in nonets

    return quality;
} // end fitness()

/** Provide the size of this Puzzle, indicating the number of empty spaces.
 * @pre None.
 * @post None.
 * @return The number of cells in this Puzzle that are not variable.
 */
int Puzzle::size(void) const
{
    return notSet;
} // end size()

/** Set a specified cell to a given value.
 * @param loc  An iterator at the cell to be set.
 * @param item  The value to place in the specified cell.
 * @pre loc does not reference an external Puzzle, but this one.
 * @post The input items remain unchanged.
 */
void Puzzle::setCell(const PuzzleIterator& loc, const char& item)
{
    content[loc.cur] = item;
} // end setCell(PuzzleIterator&, char&)

/** Provide an iterator to the first item in this Puzzle.
 * @pre None.
 * @post The returned iterator references the first item in this Puzzle.
 * @return An iterator to the first item in this Puzzle.
 */
Puzzle::PuzzleIterator Puzzle::begin(void) const
{
    return PuzzleIterator (this, 0);
} // end begin()

/** Provide an iterator to the last item in this Puzzle.
 * @pre None.
 * @post The returned iterator references the last item in this Puzzle.
 * @return An iterator to the last item in this Puzzle.
 */
Puzzle::PuzzleIterator Puzzle::end(void) const
{
    return PuzzleIterator (this, ROWS * COLUMNS);
} // end Puzzle::end()

/** Determine the number of times rules are broken by row.
 * @param quality  The initial quality to work back from.
 * @pre None.
 * @post None.
 * @return The input quality minus the number of broken rules by row.
 */
int Puzzle::fitRow(int quality) const
{
    // check rows one-at-a-time
    for (int i = 0; i < ROWS * COLUMNS; ++i)
    {
        if (content[i] == '0')  // empty cell
        {
            --quality;
        }
        else
        {
            // If not at end of row, check against remaining cells in row
            for (int j = i + 1; j < (i / ROWS) * COLUMNS + COLUMNS; ++j)
            { // invaraint: i and j are in the same row
                if (content[j] == content[i])   // duplicate found
                {
                    --quality;
                    break;
                } // end if (content[j] == content[i])
            } // end for (int j = i + 1)
        } // end if (content[i] == '0')
    } // end for (int i = 0)

    return quality;
} // end fitRow(int)

/** Determine the number of times rules are broken by column.
 * @param quality  The initial quality to work back from.
 * @pre None.
 * @post None.
 * @return The input quality minus the number of broken rules by column.
 */
int Puzzle::fitColumn(int quality) const
{
    // Traverse puzzle from first cell to last cell of second-to-last row (no
    // need to check last cells against themselves)
    for (int i = 0; i < ROWS * (COLUMNS - 1); ++i)
    { // invariant: i is not in last row
        // Check against remaining cells in column
        for (int j = i + COLUMNS; j < ROWS * COLUMNS; j += COLUMNS)
        { // invaraint: i and i + j are in the same column
            if (content[j] == content[i] && content[i] != '0')  // dup found
            {
                --quality;
                break;
            } // end if (content[j] == content[i] && content[i] != '0')
        } // end for (int j = i + COLUMNS)
    } // end for (int i = 0)

    return quality;
} // end fitColumn(int)

/** Determine the number of times rules are broken by nonet.
 * @param quality  The initial quality to work back from.
 * @pre None.
 * @post None.
 * @return The input quality minus the number of broken rules by nonet.
 */
int Puzzle::fitNonet(int quality) const
{
    int temp;
    // Traverse puzzle from first cell to second-to-last (no need to check last
    // cell against itself)
    for (int i = 0; i < ROWS * COLUMNS - 1; ++i)
    {
        if (content[i] != '0')      // 0's only counted once, use fitRow().
        {
            if (i % 3 > 1)          // at edge of nonet
            {
                temp = i - 2 + COLUMNS;     // drop to next row
            }
            else
            {
                temp = i + 1;
            } // end if (i % 3 > 1)

            while(temp - i < 3 || (temp / ROWS) % 3 > (i / ROWS) % 3)
            {
                if (content[temp] == content[i])    // duplicate found
                {
                    --quality;
                    break;
                }
                else if (temp % 3 > 1)      // at edge of nonet
                {
                    temp += (COLUMNS - 2);  // drop to next row
                }
                else
                {
                    ++temp;
                } // end if (content[temp] == content[i])
            } // end while(temp - i < 3 || (temp / ROWS) % 3 > (i / ROWS) % 3)
        } // end if (content[i] != '0')
    } // end for (int i = 0)

    return quality;
} // end Puzzle::fitNonet()
