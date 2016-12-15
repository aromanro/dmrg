#include "stdafx.h"
#include "Operator.h"

namespace DMRG {

	namespace Operators {


		Operator::Operator(unsigned int size, bool extendChangeSign)
			: changeSign(extendChangeSign), singleSiteSize(size)
		{
			matrix = Eigen::MatrixXd::Zero(size, size);
		}


		Operator::~Operator()
		{
		}


		void Operator::Extend()
		{
			matrix = IdentityKronecker(singleSiteSize, matrix);
		}

	}
}