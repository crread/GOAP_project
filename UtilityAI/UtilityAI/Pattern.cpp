#include "Pattern.h"

#include <math.h>

float Pattern_Linear::getDecisionWeight(const int x) const {
	float result = cA * x + cB;

	if (result >= 100)
		result = 100;

	return result;
}

float Pattern_Exponential_Reversed::getDecisionWeight(const int x) const {
	float result = log(exp(x));

	if (result >= 100)
		result = 100;

	return result;
}