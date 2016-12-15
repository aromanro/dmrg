#pragma once
#include "ComputationThread.h"


template<class Algorithm> class DMRGThread :
	public ComputationThread
{
protected:
	int m_Sweeps;
	int m_Sites;

	virtual void Calculate();
public:
	Algorithm dmrg;


	DMRGThread(int sites, int sweeps = 4, int states = 10);
	virtual ~DMRGThread();
};

#ifndef _DMRGThread
#include "DMRGThread.cpp"
#endif