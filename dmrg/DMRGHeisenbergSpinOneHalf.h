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
			DMRGHeisenbergSpinOneHalf(unsigned int maxstates = 18);
			~DMRGHeisenbergSpinOneHalf();
		};
	}
}