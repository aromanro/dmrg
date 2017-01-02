#include "stdafx.h"

#define _GENERIC_DMRG_IMPL

#include "GenericDMRGAlgorithm.h"
#include "DensityMatrix.h"


#include <algorithm>


namespace DMRG {

	template<class SiteHamiltonianType, class BlockType> GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::GenericDMRGAlgorithm(unsigned int maxstates)
		: finiteAlgorithm(false), oddSites(false), addInteractionOperator(false), maxStates(maxstates), systemBlock(nullptr), environmentBlock(nullptr), systemBlocksRepository(nullptr), environmentBlocksRepository(nullptr),
		truncationError(0)
	{
	}


	template<class SiteHamiltonianType, class BlockType> GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::~GenericDMRGAlgorithm()
	{
		delete systemBlocksRepository;
		delete environmentBlocksRepository;

		delete systemBlock;
		delete environmentBlock;
	}

	template<class SiteHamiltonianType, class BlockType> void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::ClearInit()
	{
		delete systemBlocksRepository;
		delete environmentBlocksRepository;

		systemBlocksRepository = environmentBlocksRepository = nullptr;

		delete systemBlock;
		delete environmentBlock;

		systemBlock = new BlockType();
		environmentBlock = new BlockType();

		if (oddSites) environmentBlock->length = 0;

		results.clear();
		operators.clear();
	}


	template<class SiteHamiltonianType, class BlockType>  void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::AddToRepository(int index, BlockType* what, std::map<int, std::unique_ptr<BlockType>> *repository)
	{
		(*repository)[index] = std::unique_ptr<BlockType>(new BlockType(*what));
	}

	template<class SiteHamiltonianType, class BlockType> void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::CopySystemBlockToEnvironment()
	{
		*environmentBlock = *systemBlock;
	}


	template<class SiteHamiltonianType, class BlockType> void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::TransformOperators(const Eigen::MatrixXd& U, const Eigen::MatrixXd& Ut, bool left)
	{
		if (left)
		{
			if (!systemBlock) return;

			// truncate and transform the operators to the new basis
			systemBlock->hamiltonian.matrix = U * systemBlock->hamiltonian.matrix * Ut;
		}
		else
		{
			if (!environmentBlock) return;

			// truncate and transform the operators to the new basis
			environmentBlock->hamiltonian.matrix = U * environmentBlock->hamiltonian.matrix * Ut;			
		}

		for (auto& op : operators)
			op.matrix = U * op.matrix * Ut;
	}


	template<class SiteHamiltonianType, class BlockType> void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::Extend()
	{
		// ******************* Measurement operators ********************************************************

		// this assumes that all operators are for the system block - this toy program only deals with such operators
		for (auto& op : operators) op.Extend();

		if (addInteractionOperator)
		{
			Operators::Hamiltonian interaction = systemBlock->GetInteractionHamiltonian();
			
			operators.push_back(interaction);
		}

		// ****************************************************************************************************

		systemBlock->Extend();
	}

	template<class SiteHamiltonianType, class BlockType> Operators::Hamiltonian GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::CalculateSuperblock(unsigned int SysBasisSize, unsigned int EnvBasisSize)
	{
		Operators::Hamiltonian superblockHamiltonian;

		// Hsuperblock = Hsystem + Hinteraction + Henvironment

		Operators::Hamiltonian SystemEnvironmentInteraction = GetInteractionHamiltonian();

		superblockHamiltonian.matrix = Operators::Operator::IdentityKronecker(EnvBasisSize, systemBlock->hamiltonian.matrix) +
									   SystemEnvironmentInteraction.matrix +
									   Operators::Operator::KroneckerProductWithIdentity(environmentBlock->hamiltonian.matrix, SysBasisSize);

		return superblockHamiltonian;
	}


	template<class SiteHamiltonianType, class BlockType> double GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::Step(int step)
	{
		// extend blocks and operators
		Extend();

		// a simple copy is enough for this toy program
		// one might need to construct the right block too, depending on the model
		// if mirror symmetry does not exist
		if (!finiteAlgorithm) {
			if (oddSites)
			{
				int key = systemBlock->length - 1;
				*environmentBlock = *((*systemBlocksRepository)[key]);
			}
			else CopySystemBlockToEnvironment();
		}

		unsigned int SysBasisSize = (unsigned int)systemBlock->hamiltonian.matrix.cols();
		unsigned int EnvBasisSize = (unsigned int)environmentBlock->hamiltonian.matrix.cols();

		// join the system block and the environment block into the superblock
		Operators::Hamiltonian superblockHamiltonian = CalculateSuperblock(SysBasisSize, EnvBasisSize);

		// get the ground state of the superblock hamiltonian

		// originally I used the commented code to develop the code, knowing that I'll have to switch to Lanczos
		// computing all eigenvectors and eigenvalues when one needs only one is costly
		// this is good for tests, though, Eigen is pretty reliable

		//superblockHamiltonian.Diagonalize();
		//Eigen::VectorXd GroundState = superblockHamiltonian.eigenvectors().col(0);
		//double GroundStateEnergy = superblockHamiltonian.eigenvalues()[0];

		double GroundStateEnergy = LanczosGroundState(superblockHamiltonian, GroundState);

		TRACE(L"Energy/site: %f for system length: %d (Sys: %d, Env: %d) at step: %d\n", GroundStateEnergy / (systemBlock->length + environmentBlock->length), (systemBlock->length + environmentBlock->length), systemBlock->length, environmentBlock->length, step);

		// construct the reduced density matrix

		// the density matrix for the ground state is |GroundState><GroundState|
		// in terms of system and environment basis states the ground state is |GroundState> = \Sum_{i,j} c_{i,j} |i>|j>
		// where |i> is system vector and |j> is environment vector
		// c_{i,j} = <i|<j|GroundState>
		// the density matrix constructor takes care of getting the reduced density matrix from c_{i,j}

		Operators::DensityMatrix densityMatrix(GroundState, SysBasisSize, EnvBasisSize);
		densityMatrix.Diagonalize();

		const Eigen::MatrixXd& eigenV = densityMatrix.eigenvectors();
		eigenvals = densityMatrix.eigenvalues();

		// now pick the ones that have the biggest values
		// they are ordered with the lowest eigenvalue first

		unsigned int keepStates = std::min<unsigned int>(maxStates, SysBasisSize);

		// construct the transform matrix from the chosen vectors (the ones with the higher probability)
		Eigen::MatrixXd Ut(eigenV.rows(), keepStates);

		int numStates = (int)eigenV.cols();
		truncationError = 1.; // also calculate the truncation error
		for (unsigned int i = 0; i < keepStates; ++i)
		{
			int index = numStates - i - 1;
			
			Ut.col(i) = eigenV.col(index);
			truncationError -= eigenvals(index);
		}

		TRACE("Truncation Error: %f\n", truncationError);

		const Eigen::MatrixXd U = Ut.adjoint();

		TransformOperators(U, Ut);

		return GroundStateEnergy;
	}

	template<class SiteHamiltonianType, class BlockType> double GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::CalculateInfinite(int chainLength)
	{
		if (chainLength % 2) ++chainLength;
		if (chainLength <= 0) return std::numeric_limits<double>::infinity();

		oddSites = false;

		ClearInit();

		finiteAlgorithm = false;

		double result = 0;

		truncationError = 0;

		for (int i = 0; 2 * systemBlock->length < chainLength; ++i)
			result = Step(i);

		return result;
	}

	template<class SiteHamiltonianType, class BlockType> double GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::CalculateFinite(int chainLength, int numSweeps)
	{
		//if (chainLength % 2) ++chainLength;
		if (chainLength <= 0) return std::numeric_limits<double>::infinity();

		if (chainLength % 2) oddSites = true;

		ClearInit();

		finiteAlgorithm = false;
		truncationError = 0;

		systemBlocksRepository = new std::map<int, std::unique_ptr<BlockType>>();
		environmentBlocksRepository = new std::map<int, std::unique_ptr<BlockType>>();

		double result = 0;

		// infinite size algorithm

		AddToRepository(systemBlock->length, systemBlock, systemBlocksRepository);
		if (environmentBlock->length) AddToRepository(environmentBlock->length, environmentBlock, environmentBlocksRepository);

		for (int i = 0; systemBlock->length + environmentBlock->length < chainLength; ++i)
		{
			result = Step(i);

			AddToRepository(systemBlock->length, systemBlock, systemBlocksRepository);
			AddToRepository(environmentBlock->length, environmentBlock, environmentBlocksRepository);
		}


		// finite size algorithm

		bool left = false;
		finiteAlgorithm = true;

		int step = 0;
		for (int i = 0; i < numSweeps; ++i)
		{
			TRACE("SWEEP NUMBER %d\n", i);

			for (;; ++step)
			{
				int key = chainLength - systemBlock->length - 1;

				delete environmentBlock;
				environmentBlock = (*environmentBlocksRepository)[key].release();
				environmentBlocksRepository->erase(key);

				if (1 == environmentBlock->length)
				{
					// we reached the end of the chain, start sweeping in the other direction

					std::swap(environmentBlock, systemBlock);
					std::swap(environmentBlocksRepository, systemBlocksRepository);
					left = !left;

					// put the state we're starting with to the systems repository (it just switched from environment)
					// we removed it from there and we need it back
					AddToRepository(systemBlock->length, systemBlock, systemBlocksRepository);
				
				    if (!left && numSweeps - 1 == i)
						addInteractionOperator = true;
				}

				result = Step(step);

				AddToRepository(systemBlock->length, systemBlock, systemBlocksRepository);				

				if (!left && systemBlock->length == (chainLength + 1) / 2) break;
			}
		}

		CalculateResults();

		return result;
	}

	template<class SiteHamiltonianType, class BlockType> void GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::CalculateResults()
	{
		int eigensize = (int)eigenvals.rows();

		for (auto &op : operators)
		{
			double result = 0;

			for (int i = 0; i < op.matrix.cols(); ++i)
				result += op.matrix(i, i) * eigenvals(eigensize - 1 - i);

			results.push_back(result);
		}
	}

	// the following code is inspired from https://github.com/iglpdc/tiny_dmrg
	// modified quite a bit to be easier to understand!!!!!!

	// this was originally with MIT license (compatible with GPL), so I'll let it here:

	/*
	Copyright (c) 2012 Ivan Gonzalez

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
	*/


	// Dec 7 2016: modified to use Eigen vectors, replaced call to tqli with Eigen computeFromTridiagonal
	// also cleaned it a little and adjusted for my method signature
	// also limited the max iteration number by the matrix size and got rid of reallocations


#define PRECISION_LIMIT 1E-5

	template<class SiteHamiltonianType, class BlockType> double GenericDMRGAlgorithm<SiteHamiltonianType, BlockType>::LanczosGroundState(const Operators::Hamiltonian& hamiltonian, Eigen::VectorXd& groundState)
	{
		bool diagonalized = false;
		double GroundEnergy = std::numeric_limits<double>::infinity();

		const int BasisSize = (int)hamiltonian.matrix.cols();
		int iterLim = BasisSize;

		Eigen::VectorXd Vorig(BasisSize);

		Eigen::VectorXd v0(BasisSize);
		Eigen::VectorXd v1(BasisSize);
		Eigen::VectorXd v2(BasisSize);

		Eigen::VectorXd alpha(BasisSize);
		Eigen::VectorXd beta(BasisSize + 1);

		Eigen::MatrixXd Hmatrix = Eigen::MatrixXd::Zero(BasisSize, BasisSize);

		Vorig.setRandom();
		Vorig.normalize();

		Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver;

		for (int getEigen = 0; getEigen < 2; ++getEigen)
		{
			v0 = Vorig;

			if (getEigen) groundState = v0 * Hmatrix(0, 0);

			beta(0) = 0;

			v1 = hamiltonian.matrix * v0; // |v1> = H |v0> 

			alpha(0) = v0.adjoint() * v1;

			v1 -= alpha(0) * v0; // now |v1> = H |v0> - <v0|v1> |v0>

			beta(1) = v1.norm();

			if (fabs(pow(beta(1), 2)) < PRECISION_LIMIT) {
				if (!getEigen) groundState = v0;

				return alpha(0);
			}

			v1 /= beta(1); // now it's also normalized


			// at this point v0 and v1 are orthonormal

			if (getEigen) groundState += v1 * Hmatrix(1, 0);
			else GroundEnergy = std::numeric_limits<double>::infinity();

			int i; // need it outside the loop
			for (i = 1; i < iterLim; ++i)
			{
				// construct a vector V2 orthonormal on both V1 and V0

				v2 = hamiltonian.matrix * v1; // |v2> = H |v1>
				alpha(i) = v1.adjoint() * v2;  // alpha = <v1|v2>
				v2 -= alpha(i) * v1 + beta(i) * v0;  // now |v2> =  H |v1> - <v1|v2>|v1> - <v0|v1>|v0>
				beta(i + 1) = v2.norm();
				v2 /= beta(i + 1); // normalize it

				// now v2 is orthonormal on both v1 and v0

				if (getEigen) groundState += v2 * Hmatrix(i + 1, 0);

				v0 = v1;
				v1 = v2;

				if (i > 3 && !getEigen)
				{
					int dim = i + 1;
					solver.computeFromTridiagonal(alpha.head(dim), beta.segment(1, i));
					Hmatrix.block(0, 0, dim, dim) = solver.eigenvectors();

					double eigenval = solver.eigenvalues()(0);
					if (GroundEnergy - eigenval < PRECISION_LIMIT) {
						GroundEnergy = eigenval;
						++i;
						diagonalized = true;
						break;
					}

					GroundEnergy = eigenval;
				}
			}

			if (!getEigen) {
				iterLim = i;

				if (!diagonalized)
				{
					solver.computeFromTridiagonal(alpha.head(i), beta.segment(1, i - 1));
					Hmatrix.block(0, 0, i, i) = solver.eigenvectors();
					GroundEnergy = solver.eigenvalues()(0);
				}
			}
		}

		groundState.normalize();

		return GroundEnergy;
	}

}