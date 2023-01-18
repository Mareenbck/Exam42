#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include <iostream>
# include <vector>
# include "ATarget.hpp"

class ATarget;

class TargetGenerator
{
	private:
		TargetGenerator(const TargetGenerator &src);
		TargetGenerator &operator=(const TargetGenerator &rhs);

		std::vector<ATarget *> targets;

	public:
		TargetGenerator(void);
		~TargetGenerator(void);

		void learnTargetType(ATarget *target);
		void forgetTargetType(std::string const &target);
		ATarget* createTarget(std::string const &target);
};

#endif
