#pragma once

#include "Operator.h"

namespace DMRG {
	namespace Operators {

		class DiagonalizableOperator : public Operator
		{
		protected:
			Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver;
		public:
			DiagonalizableOperator(unsigned int size = 2, bool extendChangeSign = false);
			~DiagonalizableOperator();

			void Diagonalize();
			const Eigen::MatrixXd& eigenvectors() const { return solver.eigenvectors(); }
			const Eigen::VectorXd& eigenvalues() const { return solver.eigenvalues(); }
		};

	}
}