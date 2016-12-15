#include "stdafx.h"
#include "DensityMatrix.h"

namespace DMRG {

	namespace Operators {


		DensityMatrix::DensityMatrix(const Eigen::VectorXd& GroundState, unsigned int SysBasisSize, unsigned int EnvBasisSize, bool left)
			: DiagonalizableOperator(SysBasisSize, false)
		{
			// the density matrix for the ground state is |GroundState><GroundState|
			// in terms of system and environment states the ground state is |GroundState> = \Sum_{i,j} c_{i,j} |i>|j>
			// where |i> is environment vector and |j> is system vector
			// c_{i,j} = <i|<j|GroundState>

			Eigen::MatrixXd c(EnvBasisSize, SysBasisSize);

			// first construct the coefficients matrix

			for (unsigned int i = 0; i < EnvBasisSize; ++i)
				for (unsigned int j = 0; j < SysBasisSize; ++j)
					c(i, j) = GroundState(i * SysBasisSize + j);

			//trace out environment

			if (left)
				matrix = c.adjoint() * c;
			else
				matrix = c * c.adjoint();

			// this traces out the environment because
			// \rho^{sys} = Tr_{env}|GroundState><GroundState| = \Sum_i <i|GroundState><GroundState|i>
			// sandwiching it between <j| and |k> =>
			// \rho^{sys}_{j,k} = \Sum_i <i|<j|GroundState><GroundState|k>|i>
			// where |i> are environment vectors, |j> and |k> are both for system
			// so \rho^{sys}_{j,k} = \Sum_i c{i,j} * c^*_{i,k}
			// that is, \rho = c^\dagger * c 
		}


		DensityMatrix::~DensityMatrix()
		{
		}


	}
}
