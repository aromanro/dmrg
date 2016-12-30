#pragma once

#include "SiteOperator.h"
#include "GenericBlock.h"

namespace DMRG {

	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> class HeisenbergBlock : public GenericBlock<SiteHamiltonianType>
		{
		public:
			HeisenbergBlock(bool Left = true);
			virtual ~HeisenbergBlock();

			SzType SzForBoundarySite;
			SplusType SplusForBoundarySite;

			static SzType SzForNewSite;
			static SplusType SplusForNewSite;

			double m_Jz;
			double m_Jxy;

			virtual Operators::Hamiltonian GetInteractionHamiltonian() const;
			virtual void Extend();
		};
	}
}

#ifndef _BLOCK_IMPL

#include "Block.inl"

#endif // !_BLOCK_IMPL
