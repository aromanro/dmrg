#include "stdafx.h"
#include "DiagonalizableOperator.h"

namespace DMRG {

	namespace Operators {

		DiagonalizableOperator::DiagonalizableOperator(unsigned int size, bool extendChangeSign)
			: Operator(size, extendChangeSign)
		{
		}


		DiagonalizableOperator::~DiagonalizableOperator()
		{
		}

		void DiagonalizableOperator::Diagonalize()
		{
			solver.compute(matrix);

			ASSERT(solver.info() == Eigen::ComputationInfo::Success);

			// the eigenvalues and eigenvectors are already sorted
			// the eigenvectors are normalized
			// the SelfAdjointEigenSolver diagonalization from Eigen takes care of those
			// for another solver, sorting needs to be done afterwards

			matrix = eigenvalues().asDiagonal();
		}



	}
}
