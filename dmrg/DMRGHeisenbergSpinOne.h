#pragma once
#include "DMRGAlgorithm.h"


#include "Hamiltonian.h"
#include "SiteOperator.h"

namespace DMRG {

	namespace Heisenberg {

		class DMRGHeisenbergSpinOne :
			public HeisenbergDMRGAlgorithm<Operators::HamiltonianSpinOne, Operators::SzOne, Operators::SplusOne>
		{
		public:
			DMRGHeisenbergSpinOne(unsigned int maxstates = 10);
		};

	}
}

