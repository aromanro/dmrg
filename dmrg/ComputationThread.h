#pragma once

#include <thread>
#include <atomic>

class ComputationThread
{
public:
	virtual ~ComputationThread() = default;

	std::atomic_bool terminated{false};
	double result = std::numeric_limits<double>::infinity();
	double gapResult = 0;
	
	void Start();

protected:
	ComputationThread() = default;

	virtual void Calculate() = 0;
};

