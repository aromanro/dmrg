#include "stdafx.h"

#include "Hamiltonian.h"

namespace DMRG {

	namespace Operators {

		Hamiltonian::Hamiltonian(int size)
			: DiagonalizableOperator(size, false)
		{
		}

		void Hamiltonian::Extend(const Hamiltonian& siteHamiltonian, const Hamiltonian& interactionHamiltonian, bool left)
		{
			const int basisSize = static_cast<int>(matrix.cols());

			DiagonalizableOperator::Extend(left);

			if (left)
				matrix += Operator::KroneckerProductWithIdentity(siteHamiltonian.matrix, basisSize);
			else
				matrix += Operator::IdentityKronecker(basisSize, siteHamiltonian.matrix);
				
			matrix += interactionHamiltonian.matrix;
		}


		HamiltonianSpinOne::HamiltonianSpinOne()
			: Hamiltonian(3)
		{
		}

	}
}