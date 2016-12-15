#include "stdafx.h"
#include "DMRGHeisenbergSpinOneHalf.h"


namespace DMRG {
	namespace Heisenberg {

		DMRGHeisenbergSpinOneHalf::DMRGHeisenbergSpinOneHalf(unsigned int maxstates)
			: HeisenbergDMRGAlgorithm<Operators::Hamiltonian, Operators::SzOneHalf, Operators::SplusOneHalf>(maxstates)
		{
		}


		DMRGHeisenbergSpinOneHalf::~DMRGHeisenbergSpinOneHalf()
		{
		}

	}
}