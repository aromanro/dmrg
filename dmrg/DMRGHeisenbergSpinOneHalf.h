#pragma once
#include "DMRGAlgorithm.h"

#include "Hamiltonian.h"
#include "SiteOperator.h"

namespace DMRG {

	namespace Heisenberg {

		class DMRGHeisenbergSpinOneHalf :
			public HeisenbergDMRGAlgorithm<Operators::Hamiltonian, Operators::SzOneHalf, Operators::SplusOneHalf>
		{
		public:
			DMRGHeisenbergSpinOneHalf(double Jz = 1., double Jxy = 1., unsigned int maxstates = 18);
		};
	}
}