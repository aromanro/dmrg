#define _DMRG_IMPL

#include "DMRGAlgorithm.h"

namespace DMRG {
	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::HeisenbergDMRGAlgorithm(double Jz, double Jxy, unsigned int maxstates)
			: GenericDMRGAlgorithm(maxstates), m_Jz(Jz), m_Jxy(Jxy)
		{
		}


		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::~HeisenbergDMRGAlgorithm()
		{
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> void HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::ClearInit()
		{
			GenericDMRGAlgorithm<SiteHamiltonianType, HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>>::ClearInit();

			systemBlock->m_Jz = environmentBlock->m_Jz = m_Jz;
			systemBlock->m_Jxy = environmentBlock->m_Jxy = m_Jxy;
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> Operators::Hamiltonian HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::GetInteractionHamiltonian() const
		{
			Operators::Hamiltonian interactionHamiltonian;

			interactionHamiltonian.matrix = m_Jz * Operators::Operator::KroneckerProduct(environmentBlock->SzForBoundarySite.matrix, systemBlock->SzForBoundarySite.matrix) +
				0.5 * m_Jxy * (Operators::Operator::KroneckerProduct(environmentBlock->SplusForBoundarySite.matrix, systemBlock->SplusForBoundarySite.matrix.adjoint()) +
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


