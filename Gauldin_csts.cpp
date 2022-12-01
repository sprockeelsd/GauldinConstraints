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
 * @brief Create an instance of the problem (at the moment, doesn't take any arguments but will in the future -> TODO)
 *
 */
Gauldin_csts::Gauldin_csts() : soprano(*this, 1, 1, 4), alto(*this, 1, 1, 4), tenor(*this, 1, 1, 4), bass(*this, 1, 1, 4)
{
    Rnd r1(12U); // random number generator

    // Constraints posting
    voices_order(1);

    // branching   TODO change
    branch(*this, soprano, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, alto, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, tenor, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    branch(*this, bass, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
}

/**
 * @brief Posts the constraint that soprano[i] >= alto[i] >= tenor[i] >= bass[i] for all i
 *
 * @param n the length of the IntVarArrays      TODO change to a harmonic rhythm
 */
void Gauldin_csts::voices_order(int n)
{
    for (int i = 0; i < n; ++i)
    {
        rel(*this, soprano[i], IRT_GQ, alto[i]); // soprano[i] >= alto[i]
        rel(*this, alto[i], IRT_GQ, tenor[i]);   // alto[i] >= tenor[i]
        rel(*this, tenor[i], IRT_GQ, bass[i]);   // tenor[i] >= bass[i]
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
 * @brief Print a solution, TODO change so it looks nice
 *
 */
void Gauldin_csts::print(void) const
{
    std::cout << "soprano :" << soprano << "alto :" << alto << "tenor :" << tenor << "bass :" << bass << std::endl;
}