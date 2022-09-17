#pragma once

#include "EnumRessourceType.h";
#include "EnumOperandType.h";
#include "EnumFlagType.h"

#include <assert.h>

class Effect {
public:
	FlagType cFlag;
	RessourceType cType;

	Effect() {};
	~Effect() {};

	virtual void updateEffect() const {};
};

class Effect_Alter_Ressources : public Effect {

	OperandType cOperandType;

public:
	Effect_Alter_Ressources() {};
	Effect_Alter_Ressources(const RessourceType& ressourceType, const OperandType& operandType, const FlagType& flag);

	~Effect_Alter_Ressources() {};

	void updateEffect(unsigned int ressource, const unsigned int& quantity) const;
};