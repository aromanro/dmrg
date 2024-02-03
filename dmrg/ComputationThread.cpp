#include "stdafx.h"
#include "ComputationThread.h"


void ComputationThread::Start()
{
	std::thread([this]() {
		Calculate();
	}).detach();
}