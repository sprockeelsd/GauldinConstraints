#include "Gauldin_csts.h"
#include "Utilities.h"

using namespace Gecode;
using namespace std;

/***************************************************************************************************************************************
 *                                                                                                                                     *
 * @brief This class models tonal music as described by Gauldin in his book "Harmonic practice in tonal music", second edition.        *
 * It aims to create four-voice texture chord progressions based on the name of chords. TODO add rhythmic aspect to it                 *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

/**
 * @brief TODO :
 * Generalize the constructor so everything depends on n
 * Take Arguments from command line
 * Generalize the diff Array (maybe an IntVar Array?) in the structure constraints
 * Change n so it works with harmonic rhythm
 * Exclusive constraint between open/closed/neutral structure (maybe not necessary, I need to think about it)
 * Constraints generating major/minor/diminished/7th chords from a note puis ajouter les inversions
 */

/**
 * @brief REMARKS
 * Idk how to print the reified variables when they are assigned, so i created a test function that assigns it to true or false to check if it works
 *
 */

/**
 * @brief Construct a new Gauldin_csts::Gauldin_csts object
 *
 * @param size the size of the arrays
 * @param lowest_note the lowest bound for the domain
 * @param highest_note the highest bound for the domain
 */
Gauldin_csts::Gauldin_csts(int size, int lowest_note, int highest_note)
{
    // Initialisation
    n = size;

    soprano = IntVarArray(*this, n, lowest_note, highest_note);
    alto = IntVarArray(*this, n, lowest_note, highest_note);
    tenor = IntVarArray(*this, n, lowest_note, highest_note);
    bass = IntVarArray(*this, n, lowest_note, highest_note);

    isCloseStructure = BoolVarArray(*this, n, false, true);
    isOpenStructure = BoolVarArray(*this, n, false, true);

    diffSopranoTenor = IntVarArgs(n);
    for(int i = 0; i < n; ++i){
        diffSopranoTenor[i] = expr(*this, soprano[i] - tenor[i]);
    }


    Rnd r1(12U); // random number generator

    // Constraints posting
    voices_order();

    close_structure();

    open_structure();

    // branching   TODO change
    branch(*this, soprano, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, alto, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, tenor, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, bass, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
}

/**
 * @brief Posts the constraint that soprano[i] >= alto[i] >= tenor[i] >= bass[i] for all i
 *
 */
void Gauldin_csts::voices_order()
{
    for (int i = 0; i < n; ++i)
    {
        rel(*this, soprano[i], IRT_GQ, alto[i]); // soprano[i] >= alto[i]
        rel(*this, alto[i], IRT_GQ, tenor[i]);   // alto[i] >= tenor[i]
        rel(*this, tenor[i], IRT_GQ, bass[i]);   // tenor[i] >= bass[i]
    }
}

/**
 * @brief Posts the constraint that isCloseStructure is true if the chord formed by the 4 voices is in close structure, false if it is not.
 * A chord is in close structure if the interval between the soprano voice and the tenor voice is smaller than an octave.
 */
void Gauldin_csts::close_structure()
{
    //IntVarArgs diffSopranoTenor(n);
    for (int i = 0; i < n; ++i)
    {
        //diffSopranoTenor[i] = expr(*this, soprano[i] - tenor[i]);
        rel(*this, diffSopranoTenor[i], IRT_LE, 12, eqv(isCloseStructure[i])); // posts the reified constraint diff < 12 <=> isClosedStructure == 1
    }
}

void Gauldin_csts::open_structure()
{
    //IntVarArgs diffSopranoTenor(n);
    for (int i = 0; i < n; ++i)
    {
        //diffSopranoTenor[i] = expr(*this, soprano[i] - tenor[i]);
        rel(*this, diffSopranoTenor[i], IRT_GR, 12, eqv(isOpenStructure[i])); // posts the reified constraint diff > 12 <=> isOpenStructure == 1
    }
}

/**
 * @brief This method is called when a Branch and Bound solver is used everytime a solution is found by the solver.
 *
 * @param _b The solution found by the solver
 */
void Gauldin_csts::constrain(const Space &_b)
{
    // right now, do nothing
    const Gauldin_csts &b = static_cast<const Gauldin_csts &>(_b); // cast the space
}

/**
 * @brief Print a solution
 *
 */
void Gauldin_csts::print(void) const
{
    std::cout << "soprano :" << soprano << std::endl
              << "alto    :" << alto << std::endl
              << "tenor   :" << tenor << std::endl
              << "bass    :" << bass << std::endl
              << std::endl;
}

/**
 * @brief This method assigns a value to the array of boolean variables used for reification to force a given behaviour so we can check if it works or not
 * Calling this function will force all elements of array to have value value
 *
 * @param array ABoolVarArray of variables used for reification
 * @param value a boolean value that we want to force so we can check the behaviour
 */
void Gauldin_csts::testReified(BoolVarArray array, bool value)
{
    for (int i = 0; i < n; ++i)
    {
        rel(*this, array[i], IRT_EQ, value);
    }
}