#pragma once

#include "Hamiltonian.h"


namespace DMRG {

	template<class SiteHamiltonianType> class GenericBlock
	{
	public:
		GenericBlock(bool Left = true);
		virtual ~GenericBlock();


		int length;
		bool left;
		
		SiteHamiltonianType hamiltonian; //we start with a single site hamiltonian
		SiteHamiltonianType SiteHamiltonian;

		virtual void Extend();
		virtual Operators::Hamiltonian GetInteractionHamiltonian() const = 0;

		int GetSingleSiteBasisSize() const { return SiteHamiltonian.cols(); }
	};

}

#ifndef _GENERIC_BLOCK_IMPL

#include "GenericBlock.inl"

#endif

