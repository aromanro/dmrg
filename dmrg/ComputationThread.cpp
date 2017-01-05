#include "stdafx.h"
#include "ComputationThread.h"



ComputationThread::ComputationThread()
	: result(std::numeric_limits<double>::infinity()), terminated(false), gapResult(0)
{
}


ComputationThread::~ComputationThread()
{
}


void ComputationThread::Start()
{
	std::thread([this]() {
		Calculate();
	}).detach();
}