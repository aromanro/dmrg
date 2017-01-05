#pragma once

#include "GenericBlock.h"
#include "Hamiltonian.h"

#include <map>
#include <memory>

#include <list>

namespace DMRG {

	template<class SiteHamiltonianType, class BlockType> class GenericDMRGAlgorithm
	{
	protected:
		bool finiteAlgorithm;
		bool oddSites;

		bool addInteractionOperator;

		unsigned int maxStates;

		Eigen::VectorXd GroundState;

		BlockType* systemBlock;
		BlockType* environmentBlock;

		std::map<int, std::unique_ptr<BlockType>> *systemBlocksRepository;
		std::map<int, std::unique_ptr<BlockType>> *environmentBlocksRepository;

		Eigen::VectorXd eigenvals;
		std::list<Operators::Operator> operators;

		virtual Operators::Hamiltonian GetInteractionHamiltonian() const = 0;

		virtual void ClearInit();
		void AddToRepository(int index, BlockType* what, std::map<int, std::unique_ptr<BlockType>> *repository);
		void CopySystemBlockToEnvironment();

		virtual void TransformOperators(const Eigen::MatrixXd& U, const Eigen::MatrixXd& Ut, bool left = true);
		void Extend();
		inline Operators::Hamiltonian CalculateSuperblock(unsigned int SysBasisSize, unsigned int EnvBasisSize);
		double Step(int step);
		void CalculateResults();

		static double LanczosGroundState(const Operators::Hamiltonian& hamiltonian, Eigen::VectorXd& groundState);
	
		GenericDMRGAlgorithm(unsigned int maxstates = 10);
	
	public:
		virtual ~GenericDMRGAlgorithm();

		double truncationError;
		std::list<double> results;
		
		unsigned int nrStates;
		double EnergyGap;

		double CalculateInfinite(int chainLength);
		double CalculateFinite(int chainLength, int numSweeps);
	};

}

#ifndef _GENERIC_DMRG_IMPL

#include "GenericDMRGAlgorithm.inl"

#endif