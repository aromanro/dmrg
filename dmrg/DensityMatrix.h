#pragma once
#include "DiagonalizableOperator.h"

namespace DMRG {
	namespace Operators {

		class DensityMatrix :
			public DiagonalizableOperator
		{
		public:
			DensityMatrix(const Eigen::VectorXd& GroundState, unsigned int SysBasisSize, unsigned int EnvBasisSize, bool left = true);
			~DensityMatrix();
		};

	}
}
