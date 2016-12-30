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
			DMRGHeisenbergSpinOne(double Jz = 1., double Jxy = 1., unsigned int maxstates = 10);
		};

	}
}

