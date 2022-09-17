#include "Precondition.h"

#include "Ressources.h"

Precondition_Ressources_Is_Enough::Precondition_Ressources_Is_Enough(const ComparatorType& comparatorType, const unsigned int& valueComparator, const RessourceType& ressourceType, const FlagType& flag) 
{
	cComparator = comparatorType;
	cValue = valueComparator;
	cRessourceType = ressourceType;
	cFlag = flag;
}

bool const Precondition_Ressources_Is_Enough::isTrue(const unsigned int& currentValue) const 
{

	switch (cComparator)
	{
	case ComparatorType::HIGHER_THAN:
		return currentValue > cValue;
	case ComparatorType::HIGHER_THAN_OR_EQUAL:
		return currentValue >= cValue;
	case ComparatorType::EQUAL:
		return currentValue == cValue;
	case ComparatorType::LOWER_THAN:
		return currentValue < cValue;
	case ComparatorType::LOWER_THAN_OR_EQUAL:
		return currentValue <= cValue;
	default:
		assert(("error happened at Precondition_Ressources_Is_Enough::isTrue switch" && true));
		break;
	}

}

const RessourceType Precondition::getRessourceType() const {
	return cRessourceType;
}

int Precondition::citizenNeededForMissingRessources(const Ressources* ressourcesAdd, const unsigned int currentRessource) const {
	
	unsigned int missingValue = cValue - currentRessource;
	unsigned int ressourcesMadeByOneCitizen = ressourcesAdd->getRessource(cRessourceType);

	unsigned int citizenNeeded = missingValue / ressourcesMadeByOneCitizen;

	if (missingValue % ressourcesMadeByOneCitizen > 0) {
		citizenNeeded += 1;
	}

 	return citizenNeeded;
}