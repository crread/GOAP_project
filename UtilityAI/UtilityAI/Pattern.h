#pragma once

class Pattern {
public:
	Pattern() {};
	~Pattern() {};
	virtual float getDecisionWeight(const int x) const = 0;
};

class Pattern_Linear : public Pattern {
	int cA;
	int cB;

public:
	Pattern_Linear(const int a, const int b) : cA(a), cB(b) {};
	~Pattern_Linear() {};
	float getDecisionWeight(const int x) const override;
};

class Pattern_Exponential_Reversed : public Pattern {
public:
	float getDecisionWeight(const int x) const override;
};

