#include "stdafx.h"
#include "DMRGHeisenbergSpinOne.h"

namespace DMRG {
	namespace Heisenberg {


		DMRGHeisenbergSpinOne::DMRGHeisenbergSpinOne(unsigned int maxstates)
			: HeisenbergDMRGAlgorithm<Operators::HamiltonianSpinOne, Operators::SzOne, Operators::SplusOne>(maxstates)
		{
		}

	}
}