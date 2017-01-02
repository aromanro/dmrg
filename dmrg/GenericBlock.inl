#define _GENERIC_BLOCK_IMPL

#include "GenericBlock.h"

namespace DMRG {

	template<class SiteHamiltonianType> GenericBlock<SiteHamiltonianType>::GenericBlock(bool Left)
	: length(1), left(Left)
	{
	}


	template<class SiteHamiltonianType> GenericBlock<SiteHamiltonianType>::~GenericBlock()
	{
	}

	template<class SiteHamiltonianType> void GenericBlock<SiteHamiltonianType>::Extend()
	{	
		if (0 != length)
		{
			Operators::Hamiltonian interactionHamiltonian = GetInteractionHamiltonian();

			hamiltonian.Extend(SiteHamiltonian, interactionHamiltonian, left);
		}

		++length;
	}



}