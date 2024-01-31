#pragma once
#include "ComputationThread.h"


template<class Algorithm> class DMRGThread :
	public ComputationThread
{
protected:
	int m_Sweeps;
	int m_Sites;

	void Calculate() override;
public:
	Algorithm dmrg;


	DMRGThread(int sites, double Jz = 1., double Jxy = 1., int sweeps = 4, int states = 10, int nrExcitedStates = 0);
	~DMRGThread() override;
};

#ifndef _DMRGThread
#include "DMRGThread.cpp"
#endif