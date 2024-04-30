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

			using BlockType = typename HeisenbergBlock<SiteHamiltonianType, SzType, SplusType>;
			using BaseClass = typename GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>;

			double m_Jz;
			double m_Jxy;

			HeisenbergDMRGAlgorithm(double Jz = 1., double Jxy = 1., unsigned int maxstates = 10);

		public:
			virtual void ClearInit();
		};
	}
}

#ifndef _DMRG_IMPL

#include "DmrgAlgorithm.inl"

#endif