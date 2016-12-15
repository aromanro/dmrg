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
			int basisSize = (int)matrix.cols();
			int enlargeBasis = (int)siteHamiltonian.matrix.cols();

			if (left)
				matrix = Operator::IdentityKronecker(enlargeBasis, matrix) + Operator::KroneckerProductWithIdentity(siteHamiltonian.matrix, basisSize);
			else
				matrix = Operator::KroneckerProductWithIdentity(matrix, enlargeBasis) + Operator::IdentityKronecker(basisSize, siteHamiltonian.matrix);
				
			matrix += interactionHamiltonian.matrix;
		}


		HamiltonianSpinOne::HamiltonianSpinOne()
			: Hamiltonian(3)
		{
		}

	}
}