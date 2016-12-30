#include "stdafx.h"
#include "DMRGHeisenbergSpinOne.h"

namespace DMRG {
	namespace Heisenberg {


		DMRGHeisenbergSpinOne::DMRGHeisenbergSpinOne(double Jz, double Jxy, unsigned int maxstates)
			: HeisenbergDMRGAlgorithm<Operators::HamiltonianSpinOne, Operators::SzOne, Operators::SplusOne>(Jz, Jxy, maxstates)
		{
		}

	}
}