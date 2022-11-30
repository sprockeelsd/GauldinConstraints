#include "Gauldin_csts.h"

using namespace Gecode;
using namespace std;


/***************************************************************************************************************************************
 *                                                                                                                                     *
 * @brief This class models tonal music as described by Gauldin in his book "Harmonic practice in tonal music", second edition.        *
 * It aims to create four-voice texture chord progressions based on the name of chords. TODO add rhythmic aspect to it                 *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

class Gauldin_csts : public Space {
  protected:
    IntVarArray soprano;    // The array of variable representing the soprano voice (highest pitch voice)
    IntVarArray alto;       // The array of variable representing the alto voice (second highest pitch voice)
    IntVarArray tenor;      // The array of variable representing the tenor voice (third highest pitch voice)
    IntVarArray bass;       // The array of variable representing the bass voice (lowest pitch voice)
    int n;              // The number of events TODO change this to a harmonic rhythm

    
  public:

    /**
     * @brief Create an instance of the problem (at the moment, doesn't take any arguments but will in the future -> TODO)
     * 
     */
    Gauldin_csts(): soprano(*this,1, 1, 4), alto(*this,1, 1, 4), tenor(*this,1, 1, 4), bass(*this,1, 1, 4){
      Rnd r1(12U);    //random number generator

      // Constraints posting
      voices_order(1);

      //branching   TODO change
      branch(*this, soprano, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
      branch(*this, alto, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
      branch(*this, tenor, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
      branch(*this, bass, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    /**
     * @brief Posts the constraint that soprano[i] >= alto[i] >= tenor[i] >= bass[i] for all i
     * 
     */
    void voices_order(int n){
      for (int i = 0; i < n; ++i){
        rel(*this, soprano[i], IRT_GQ, alto[i]);     // soprano[i] >= alto[i]
        rel(*this, alto[i], IRT_GQ, tenor[i]);       // alto[i] >= tenor[i]
        rel(*this, tenor[i], IRT_GQ, bass[i]);       // tenor[i] >= bass[i]
      }
    }

    /**
     * @brief This method is called when a Branch and Bound solver is used everytime a solution is found by the solver.
     * 
     * @param _b The solution found by the solver
     */
    virtual void constrain(const Space& _b) {
      // right now, do nothing
      const Gauldin_csts& b = static_cast<const Gauldin_csts&>(_b);// cast the space
    }

    /**
     * @brief search support
     * 
     * @param s 
     */
    Gauldin_csts(Gauldin_csts& s) : Space(s) {
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
    virtual Space* copy(void) {
      return new Gauldin_csts(*this);
    }

    /**
     * @brief Print a solution, TODO change so it looks nice
     * 
     */
    void print(void) const {
        std::cout << "soprano :" << soprano << "alto :" << alto << "tenor :" << tenor << "bass :" << bass << std::endl;
    }
};

// main function

/***************************************************************************************************************************************
 *                                                                                                                                     *
 * @brief This function creates the problem and searches for solutions respecting the constraints specified in the Gauldin_csts class  *
 *                                                                                                                                     *
 ***************************************************************************************************************************************/

int main(int argc, char* argv[]) {

  Gauldin_csts* m = new Gauldin_csts();   // instantiate model (maybe take parameters from command line)

  //Search options
  Gecode::Search::Options opts;
  opts.threads = 0;   // as many as available
  //Gecode::Search::TimeStop maxTime(1000);
  //opts.stop = &maxTime; 

  //Create the search engine
  DFS<Gauldin_csts> e(m);
  delete m;

  int nbSol = 0;
  // search for and print all solutions
  while (Gauldin_csts* s = e.next()) {
    s->print(); delete s;
    ++nbSol;
    //maxTime.reset();
  }

  std::cout << "number of solutions : " << nbSol << "\n";
  return 0;
}