#include "stdafx.h"

#define _DMRGThread

#include "DMRGThread.h"


template<class Algorithm> DMRGThread<Algorithm>::DMRGThread(int sites, double Jz, double Jxy, int sweeps, int states, int nrExcitedStates)
	: dmrg(Jz, Jxy, states), m_Sites(sites), m_Sweeps(sweeps)
{
	dmrg.nrStates = nrExcitedStates;
}

template<class Algorithm> void DMRGThread<Algorithm>::Calculate()
{
	result = dmrg.CalculateFinite(m_Sites, m_Sweeps);
	gapResult = dmrg.EnergyGap;

	terminated = true;
}