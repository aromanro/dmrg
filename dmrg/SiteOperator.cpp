#include "stdafx.h"
#include "SiteOperator.h"


namespace DMRG {

	namespace Operators {

		SiteOperator::SiteOperator(unsigned int size, bool extendChangeSign)
			: Operator(size, extendChangeSign)
		{
		}


		SiteOperator::~SiteOperator()
		{
		}

		SzOneHalf::SzOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 2;

			matrix.block(0, 0, subsize, subsize) = 1. / 2. * Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, subsize, subsize, subsize) = -1. / 2. * Eigen::MatrixXd::Identity(subsize, subsize);
		}


		SplusOneHalf::SplusOneHalf(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 2;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
		}

		SzOne::SzOne(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 3;

			matrix.block(0, 0, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(2 * subsize, 2 * subsize, subsize, subsize) = -Eigen::MatrixXd::Identity(subsize, subsize);
		}


		SplusOne::SplusOne(unsigned int size)
			: SiteOperator(size, false)
		{
			const int subsize = size / 3;

			matrix.block(0, subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);
			matrix.block(subsize, 2 * subsize, subsize, subsize) = Eigen::MatrixXd::Identity(subsize, subsize);

			matrix *= sqrt(2.);
		}

	}
}