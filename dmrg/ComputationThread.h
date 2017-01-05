#pragma once

#include <thread>
#include <atomic>

class ComputationThread
{
public:
	std::atomic_bool terminated;
	double result;
	double gapResult;
	
	void Start();
	virtual ~ComputationThread();
protected:
	ComputationThread();

	virtual void Calculate() = 0;
};

