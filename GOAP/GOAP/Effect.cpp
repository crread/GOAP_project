#include "Effect.h"

Effect_Alter_Ressources::Effect_Alter_Ressources(const RessourceType& ressourceType, const OperandType& operandType, const FlagType& flag) {
	cType = ressourceType;
	cOperandType = operandType;
	cFlag = flag;
}

void Effect_Alter_Ressources::updateEffect(unsigned int ressource, const unsigned int& quantity) const
 {

	switch (cOperandType)
	{
	case OperandType::PLUS:
		ressource += quantity;
		break;
	case OperandType::MINUS:
		ressource -= quantity;
		break;
	default:
		assert(("error happened at Effect_Alter_Ressources::updateEffect switch" && true));
		break;
	}

}