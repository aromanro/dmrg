#include "stdafx.h"
#include "Operator.h"

namespace DMRG {

	namespace Operators {


		Operator::Operator(unsigned int size, bool extendChangeSign)
			: changeSign(extendChangeSign), singleSiteSize(size)
		{
			matrix = Eigen::MatrixXd::Zero(size, size);
		}

		void Operator::Extend(bool left)
		{
			if (left)
				matrix = IdentityKronecker(singleSiteSize, matrix);
			else
				matrix = KroneckerProductWithIdentity(matrix, singleSiteSize);
		}

	}
}