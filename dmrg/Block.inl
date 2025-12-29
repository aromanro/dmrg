#define _BLOCK_IMPL

#include "Block.h"

namespace DMRG {
	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> SzType HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>::SzForNewSite;
		template<class SiteHamiltonianType, class SzType, class SplusType> SplusType HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>::SplusForNewSite;

		template<class SiteHamiltonianType, class SzType, class SplusType> HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>::HeisenbergBlock(bool Left)
			: GenericBlock<SiteHamiltonianType>(Left)
			, m_Jz(1.), m_Jxy(1.)
		{
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> Operators::Hamiltonian HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>::GetInteractionHamiltonian() const
		{
			Operators::Hamiltonian interactionHamiltonian(GenericBlock<SiteHamiltonianType>::hamiltonian.GetSingleSiteSize());

			if (GenericBlock<SiteHamiltonianType>::left)
			{
				interactionHamiltonian.matrix = m_Jz * Operators::Operator::KroneckerProduct(SzForNewSite.matrix, SzForBoundarySite.matrix) +
					0.5 * m_Jxy * (Operators::Operator::KroneckerProduct(SplusForNewSite.matrix, SplusForBoundarySite.matrix.adjoint()) +
						Operators::Operator::KroneckerProduct(SplusForNewSite.matrix.adjoint(), SplusForBoundarySite.matrix));
			}
			else
			{
				interactionHamiltonian.matrix = m_Jz * Operators::Operator::KroneckerProduct(SzForBoundarySite.matrix, SzForNewSite.matrix) +
					0.5 * m_Jxy * (Operators::Operator::KroneckerProduct(SplusForBoundarySite.matrix, SplusForNewSite.matrix.adjoint()) +
						Operators::Operator::KroneckerProduct(SplusForBoundarySite.matrix.adjoint(), SplusForNewSite.matrix));
			}

			return interactionHamiltonian;
		}

		template<class SiteHamiltonianType, class SzType, class SplusType> void HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>::Extend()
		{
			const int BasisSize = static_cast<int>(GenericBlock<SiteHamiltonianType>::hamiltonian.matrix.cols());

			GenericBlock<SiteHamiltonianType>::Extend();

			if (GenericBlock<SiteHamiltonianType>::left)
			{
				SplusForBoundarySite.matrix = Operators::Operator::KroneckerProductWithIdentity(SplusForNewSite.matrix, BasisSize);
				SzForBoundarySite.matrix = Operators::Operator::KroneckerProductWithIdentity(SzForNewSite.matrix, BasisSize);
			}
			else
			{
				SplusForBoundarySite.matrix = Operators::Operator::IdentityKronecker(BasisSize, SplusForNewSite.matrix);
				SzForBoundarySite.matrix = Operators::Operator::IdentityKronecker(BasisSize, SzForNewSite.matrix);
			}
		}
	}
}