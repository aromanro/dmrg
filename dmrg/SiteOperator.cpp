#include "stdafx.h"
#include "SiteOperator.h"


namespace DMRG {

	namespace Operators {

		SiteOperator::SiteOperator(unsigned int size, bool extendChangeSign)
			: Operator(size, extendChangeSign)
		{
		}

		SzOneHalf::SzOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 2;

			matrix.topLeftCorner(subsize, subsize) = 0.5 * Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomRightCorner(subsize, subsize) = -0.5 * Eigen::MatrixXd::Identity(subsize, subsize);
		}


		SplusOneHalf::SplusOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 2;

			matrix.topRightCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		SzOne::SzOne(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 3;

			matrix.topLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomRightCorner(subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}


		SplusOne::SplusOne(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 3;

			matrix.topRightCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.bottomLeftCorner(subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);

			matrix *= sqrt(2.);
		}

	}
}