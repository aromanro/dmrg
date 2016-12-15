#define _DMRG_IMPL

#include "DMRGAlgorithm.h"

namespace DMRG {
	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::HeisenbergDMRGAlgorithm(unsigned int maxstates)
			: GenericDMRGAlgorithm(maxstates)
		{
		}


		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::~HeisenbergDMRGAlgorithm()
		{
		}


		template<class SiteHamiltonianType, class SzType, class SplusType> Operators::Hamiltonian HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::GetInteractionHamiltonian() const
		{
			Operators::Hamiltonian interactionHamiltonian;

			interactionHamiltonian.matrix = Operators::Operator::KroneckerProduct(environmentBlock->SzForBoundarySite.matrix, systemBlock->SzForBoundarySite.matrix) +
				1. / 2. * (Operators::Operator::KroneckerProduct(environmentBlock->SplusForBoundarySite.matrix, systemBlock->SplusForBoundarySite.matrix.adjoint()) +
					Operators::Operator::KroneckerProduct(environmentBlock->SplusForBoundarySite.matrix.adjoint(), systemBlock->SplusForBoundarySite.matrix));

			return interactionHamiltonian;
		}


		template<class SiteHamiltonianType, class SzType, class SplusType> void HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::TransformOperators(const Eigen::MatrixXd& U, const Eigen::MatrixXd& Ut, bool left)
		{
			GenericDMRGAlgorithm::TransformOperators(U, Ut, left); // takes care of the system block Hamiltonian

			if (left)
			{
				systemBlock->SplusForBoundarySite.matrix = U * systemBlock->SplusForBoundarySite.matrix * Ut;
				systemBlock->SzForBoundarySite.matrix = U * systemBlock->SzForBoundarySite.matrix * Ut;
			}
			else
			{
				environmentBlock->SplusForBoundarySite.matrix = U * environmentBlock->SplusForBoundarySite.matrix * Ut;
				environmentBlock->SzForBoundarySite.matrix = U * environmentBlock->SzForBoundarySite.matrix * Ut;
			}
		}




	}
}


