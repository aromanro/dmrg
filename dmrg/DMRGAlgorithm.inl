#define _DMRG_IMPL

#include "DMRGAlgorithm.h"

namespace DMRG {
	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::HeisenbergDMRGAlgorithm(double Jz, double Jxy, unsigned int maxstates)
			: BaseClass(maxstates), m_Jz(Jz), m_Jxy(Jxy)
		{
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> void HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::ClearInit()
		{
			BaseClass::ClearInit();

			BaseClass::systemBlock->m_Jz = BaseClass::environmentBlock->m_Jz = m_Jz;
			BaseClass::systemBlock->m_Jxy = BaseClass::environmentBlock->m_Jxy = m_Jxy;
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> Operators::Hamiltonian HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::GetInteractionHamiltonian() const
		{
			Operators::Hamiltonian interactionHamiltonian;

			interactionHamiltonian.matrix = m_Jz * Operators::Operator::KroneckerProduct(BaseClass::environmentBlock->SzForBoundarySite.matrix, BaseClass::systemBlock->SzForBoundarySite.matrix) +
				0.5 * m_Jxy * (Operators::Operator::KroneckerProduct(BaseClass::environmentBlock->SplusForBoundarySite.matrix, BaseClass::systemBlock->SplusForBoundarySite.matrix.adjoint()) +
					Operators::Operator::KroneckerProduct(BaseClass::environmentBlock->SplusForBoundarySite.matrix.adjoint(), BaseClass::systemBlock->SplusForBoundarySite.matrix));

			return interactionHamiltonian;
		}


		template<class SiteHamiltonianType, class SzType, class SplusType> void HeisenbergDMRGAlgorithm<SiteHamiltonianType, SzType, SplusType>::TransformOperators(const Eigen::MatrixXd& U, const Eigen::MatrixXd& Ut, bool left)
		{
			BaseClass::TransformOperators(U, Ut, left); // takes care of the system block Hamiltonian

			if (left)
			{
				BaseClass::systemBlock->SplusForBoundarySite.matrix = U * BaseClass::systemBlock->SplusForBoundarySite.matrix * Ut;
				BaseClass::systemBlock->SzForBoundarySite.matrix = U * BaseClass::systemBlock->SzForBoundarySite.matrix * Ut;
			}
			else
			{
				BaseClass::environmentBlock->SplusForBoundarySite.matrix = U * BaseClass::environmentBlock->SplusForBoundarySite.matrix * Ut;
				BaseClass::environmentBlock->SzForBoundarySite.matrix = U * BaseClass::environmentBlock->SzForBoundarySite.matrix * Ut;
			}
		}




	}
}


