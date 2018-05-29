#ifndef LATTICETESTERCONFIG_H
#define LATTICETESTERCONFIG_H
#include "latticetester/Types.h"
#include "latticetester/Const.h"
#include "latticetester/Util.h"


namespace LatticeTester {

  /**
   * This class is used to save the configuration of a lattice test. It is used
   * to keep all the parameters read in the data file and passed to different
   * methods for the spectral, Beyer or \f$P_{\alpha}\f$ tests.
   *
   */
  template<typename Int, typename BasIntMat>
    class LatticeTesterConfig {
      public:
        static const int MAX_WORD_SIZE = 64;

        /**
         * Constructor.
         */
        LatticeTesterConfig();

        /**
         * Destructor.
         */
        ~LatticeTesterConfig();

        /**
         * Frees the memory used by this object.
         */
        void kill();

        /**
         * For debugging: writes the configuration on the console.
         */
        void write();

        /**
         * This flag is set `true` if the generator is to be read from a file,
         * otherwise it is set `false`.
         */
        bool readGenFile;

        /**
         * If `readGenFile` is `true`, the name of the file from which to read
         * the generator.
         */
        std::string fileName;

        /*
         * The dimensin of the lattice
         */
        int dim;

        /**
         * The bound used for the normalization in the definition of \f$S_t\f$.
         * Only applicable for the spectral test.
         */
        NormaType normalizer;

        /**
         * The bound used for the normalization in the definition of \f$S_t\f$.
         * Only applicable for the spectral test.
         */
        PreReductionType prereduction;

        /**
         * This flag indicates to print more detailed results if `detailF`
         * \f$>0\f$. Default value: 0.
         */
        int detailF;

        /**
         * Norm used to measure the length of vectors. See module `Const` for a
         * definition of the possible norms.
         */
        NormType norm;

        /**
         * The criterion for which the test will be performed. See module
         * `Const` for the possible criterion types.
         */
        CriterionType test;

        /**
         * The precision in which the test will be performed. See module
         * `Const` for the possible precision types.
         */
        PrecisionType precision;

        /**
         * The maximum number of nodes to be examined in any given
         * branch-and-bound procedure when computing \f$d_t\f$ or \f$q_t\f$.
         */
        long maxNodesBB;

        /**
         * The basis of the Lattice where the test will be apply
         */
        BasIntMat basis;

        /**
         * The modulo of the rank1 lattice for Palpha test
         */
        Int modulo;

        /**
         * The alpha coefficient for Palpha test (for rank 1 lattices)
         */
        int alpha;

        /**
         * Used in LLL and BKZ. See Reducer. It must be smaller than
         * 1. If `fact` is closer to 1, the basis will be (typically) "more
         * reduced", but that will require more work.
         */
        double fact;

        /**
         * Used in BKZ. It stocks the number of blocks used for the BKZ reduction.
         * The more it is large, the more the basis will be reduced.
         */
        int blocksize;


        /**
         * File format used to store the results. See `Const` for a definition
         * of the possible output types.
         */
        OutputType outputType;
    }; // End class LatticeTesterConfig

  //===========================================================================

  template<typename Int, typename BasIntMat>
    LatticeTesterConfig<Int, BasIntMat>::LatticeTesterConfig()
    {
      fileName.reserve(MAX_WORD_SIZE);
      //a.SetLength(1+maxDim);
      detailF = 0;
    }

  //===========================================================================

  template<typename Int, typename BasIntMat>
    LatticeTesterConfig<Int, BasIntMat>::~LatticeTesterConfig()
    {
      kill();
    }

  //===========================================================================

  template<typename Int, typename BasIntMat>
    void LatticeTesterConfig<Int, BasIntMat>::kill()
    {
    }

  //===========================================================================

  template<typename Int, typename BasIntMat>
    void LatticeTesterConfig<Int, BasIntMat>::write()
    {

      switch(test) {

        case SPECTRAL:
          cout << "\n----- LatticeTesterConfig::write -----" << endl;
          cout << "Criterion: " << toStringCriterion(test) << endl;
          cout << "Norm: " << toStringNorm(norm) << endl;
          cout << "Normalizer: " << toStringNorma (normalizer) << endl;

          cout << "Prereduction: " << toStringPreRed (prereduction);
          cout << " (with " << toStringPrecision(precision) << " precision";
          cout << " and fact = " << fact << ")" << endl;

          cout << "Dimension of the basis: " << dim << endl;
          cout << "Lattice Basis = \n" << basis << endl;
          cout << "maxNodesBB: " << maxNodesBB << endl;
          break;

        case PALPHA:
          cout << "\n----- LatticeTesterConfig::write -----" << endl;
          cout << "Criterion: " << toStringCriterion(test) << endl;
          cout << "alpha: " << alpha << endl;
          cout << "modulo: " << modulo << endl;

          cout << "Dimension of the basis: " << dim << endl;
          cout << "Lattice Basis = \n" << basis << endl;
          cout << "maxNodesBB: " << maxNodesBB << endl;
          break;

        case BEYER:
          cout << "\n----- LatticeTesterConfig::write -----" << endl;
          cout << "Criterion: " << toStringCriterion(test) << endl;
          cout << "Dimension of the basis: " << dim << endl;
          cout << "Lattice Basis = \n" << basis << endl;
          cout << "maxNodesBB: " << maxNodesBB << endl;
          break;

        default:
          MyExit(1, "LatticeTesterConfig::write:  NO SUCH CASE");
          break;
      }
    }

} // End namespace LatticeTester
#endif
