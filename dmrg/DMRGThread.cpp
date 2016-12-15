#include "stdafx.h"

#define _DMRGThread

#include "DMRGThread.h"


template<class Algorithm> DMRGThread<Algorithm>::DMRGThread(int sites, int sweeps, int states)
	: dmrg(states), m_Sites(sites), m_Sweeps(sweeps)
{
}


template<class Algorithm> DMRGThread<Algorithm>::~DMRGThread()
{
}


template<class Algorithm> void DMRGThread<Algorithm>::Calculate()
{
	result = dmrg.CalculateFinite(m_Sites, m_Sweeps);
	
	terminated = true;
}