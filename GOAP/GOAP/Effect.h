#pragma once

#include <assert.h>
#include <iostream>

#include "EnumRessourceType.h"
#include "EnumOperandType.h"
#include "EnumFlagType.h"

class Ressources;

class Effect {
public:
	FlagType cFlag;
	RessourceType cType;

	Effect() {};
	~Effect() {};

	virtual void updateEffect() const {};
	virtual void applyEffect(Ressources* ressources, const Ressources* ressourcesAdd, const Ressources* ressourcesRemove, const unsigned int citizens) const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Effect& effect);
};

class Effect_Alter_Ressources : public Effect {

	OperandType cOperandType;

public:
	Effect_Alter_Ressources() {};
	Effect_Alter_Ressources(const RessourceType& ressourceType, const OperandType& operandType, const FlagType& flag);

	~Effect_Alter_Ressources() {};

	void applyEffect(Ressources* ressources, const Ressources* ressourcesAdd, const Ressources* ressourcesRemove, const unsigned int citizens) const override;
};