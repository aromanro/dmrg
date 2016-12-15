#include "stdafx.h"
#include "ComputationThread.h"



ComputationThread::ComputationThread()
	: result(std::numeric_limits<double>::infinity()), terminated(false)
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