#include "Effect.h"

#include <iostream>

#include "Ressources.h"

Effect_Alter_Ressources::Effect_Alter_Ressources(const RessourceType& ressourceType, const OperandType& operandType, const FlagType& flag) {
	cType = ressourceType;
	cOperandType = operandType;
	cFlag = flag;
}

void Effect_Alter_Ressources::applyEffect(Ressources* ressources,const Ressources* ressourcesAdd,const Ressources* ressourcesRemove, const unsigned int citizens) const {
	
	unsigned int multiplicator = citizens;

	if (citizens == 0) {
		multiplicator = 1;
	}
	
	switch (cOperandType)
	{
	case OperandType::PLUS:
		ressources->updateRessources(cType, ressourcesAdd, multiplicator);
		break;
	case OperandType::MINUS:
		ressources->updateRessources(cType, ressourcesRemove, multiplicator);
		break;
	default:
		assert(("error happened at Effect_Alter_Ressources::updateEffect switch" && true));
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const Effect& effect) {
	
	std::string currentType = "";
	
	switch(effect.cType)
	{
	case RessourceType::CITIZEN:
		currentType = "citizen ";
		break;
	case RessourceType::FOOD:
		currentType = "food ";
		break;
	case RessourceType::WOOD:
		currentType = "wood ";
		break;
	case RessourceType::IRON:
		currentType = "iron ";
		break;
	case RessourceType::SPACE:
		currentType = "space ";
		break;
	case RessourceType::HOUSE:
		currentType = "house ";
		break;
	}

	os << currentType << std::endl;
	return os;
}