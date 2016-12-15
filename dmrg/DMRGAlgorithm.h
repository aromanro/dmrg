#pragma once


#include "Block.h"
#include "Hamiltonian.h"
#include "GenericDMRGAlgorithm.h"

namespace DMRG {
	namespace Heisenberg {

		template<class SiteHamiltonianType, class SzType, class SplusType> class HeisenbergDMRGAlgorithm : public GenericDMRGAlgorithm<SiteHamiltonianType, HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>>
		{
		protected:
			virtual Operators::Hamiltonian GetInteractionHamiltonian() const;
			virtual void TransformOperators(const Eigen::MatrixXd& U, const Eigen::MatrixXd& Ut, bool left = true);

			//typedef typename HeisenbergBlock<SiteHamiltonianType, SzType, SplusType> BlockType;
		public:
			HeisenbergDMRGAlgorithm(unsigned int maxstates = 10);
			virtual ~HeisenbergDMRGAlgorithm();
		};
	}
}

#ifndef _DMRG_IMPL

#include "DmrgAlgorithm.inl"

#endif