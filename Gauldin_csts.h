#ifndef GAULDIN_CSTS
#define GAULDIN_CSTS

#include <gecode/int.hh>
#include <gecode/search.hh>
#include <iostream>
#include <vector>
#include <string>

using namespace Gecode;

/***************************************************************************************************************************************
 *                                                                                                                                     *
 * @brief This class models tonal music as described by Gauldin in his book "Harmonic practice in tonal music", second edition.        *
 * It aims to create four-voice texture chord progressions based on the name of chords. TODO add rhythmic aspect to it                 *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

class Gauldin_csts : public Space
{
protected:
    IntVarArray soprano; // The array of variable representing the soprano voice (highest pitch voice)
    IntVarArray alto;    // The array of variable representing the alto voice (second highest pitch voice)
    IntVarArray tenor;   // The array of variable representing the tenor voice (third highest pitch voice)
    IntVarArray bass;    // The array of variable representing the bass voice (lowest pitch voice)
    int n;               // The number of events TODO change this to a harmonic rhythm

public:
    /**
     * @brief Create an instance of the problem (at the moment, doesn't take any arguments but will in the future -> TODO)
     *
     */
    Gauldin_csts();

    /**
     * @brief Posts the constraint that soprano[i] >= alto[i] >= tenor[i] >= bass[i] for all i
     *
     * @param n the length of the IntVarArrays      TODO change to a harmonic rhythm
     */
    void voices_order(int n);

    /**
     * @brief This method is called when a Branch and Bound solver is used everytime a solution is found by the solver.
     *
     * @param _b The solution found by the solver
     */
    virtual void constrain(const Space &_b);

    /**
     * @brief search support
     *
     * @param s
     */
    Gauldin_csts(Gauldin_csts &s) : Space(s)
    {
        soprano.update(*this, s.soprano);
        alto.update(*this, s.alto);
        tenor.update(*this, s.tenor);
        bass.update(*this, s.bass);
    }

    /**
     * @brief copies the instance of the problem, don't touch
     *
     * @return Space* a copy of *this
     */
    virtual Space *copy(void)
    {
        return new Gauldin_csts(*this);
    }

    /**
     * @brief Print a solution, TODO change so it looks nice
     *
     */
    void print(void) const;
};
#endif