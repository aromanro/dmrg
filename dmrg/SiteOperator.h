#pragma once

#include "Operator.h"


namespace DMRG {

	namespace Operators {

		class SiteOperator :
			public Operator
		{
		public:
			SiteOperator(unsigned int size = 2, bool extendChangeSign = false);
			~SiteOperator() override;
		};



		class SzOneHalf : public SiteOperator
		{
		public:
			SzOneHalf(unsigned int size = 2);
		};


		class SplusOneHalf : public SiteOperator
		{
		public:
			SplusOneHalf(unsigned int size = 2);
		};


		class SzOne : public SiteOperator
		{
		public:
			SzOne(unsigned int size = 3);
		};


		class SplusOne : public SiteOperator
		{
		public:
			SplusOne(unsigned int size = 3);
		};

	}
}
