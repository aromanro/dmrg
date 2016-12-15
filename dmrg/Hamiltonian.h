#pragma once

#include "SiteOperator.h"
#include "DiagonalizableOperator.h"

namespace DMRG {
	namespace Operators {

		class Hamiltonian : public DiagonalizableOperator
		{
		public:
			Hamiltonian(int size = 2);

			void Extend(const Hamiltonian& siteHamiltonian, const Hamiltonian& interactionHamiltonian, bool left = true);
		};

		class HamiltonianSpinOne : public Hamiltonian
		{
		public:
			HamiltonianSpinOne();
		};


	}
}
