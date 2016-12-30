#include "stdafx.h"
#include "DMRGHeisenbergSpinOneHalf.h"


namespace DMRG {
	namespace Heisenberg {

		DMRGHeisenbergSpinOneHalf::DMRGHeisenbergSpinOneHalf(double Jz, double Jxy, unsigned int maxstates)
			: HeisenbergDMRGAlgorithm<Operators::Hamiltonian, Operators::SzOneHalf, Operators::SplusOneHalf>(Jz, Jxy, maxstates)
		{
		}

	}
}