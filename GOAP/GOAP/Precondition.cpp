#include "Precondition.h"

#include "Ressources.h"

Precondition_Ressources_Is_Enough::Precondition_Ressources_Is_Enough(const ComparatorType& comparatorType, const unsigned int& valueComparator, const RessourceType& ressourceType, const FlagType& flag) 
{
	cComparator = comparatorType;
	cValueComparator = valueComparator;
	cRessourceType = ressourceType;
	cFlag = flag;
}

bool const Precondition_Ressources_Is_Enough::isTrue(const unsigned int& currentValue) const 
{

	switch (cComparator)
	{
	case ComparatorType::HIGHER_THAN:
		return currentValue > cValueComparator;
	case ComparatorType::HIGHER_THAN_OR_EQUAL:
		return currentValue >= cValueComparator;
	case ComparatorType::EQUAL:
		return currentValue == cValueComparator;
	case ComparatorType::LOWER_THAN:
		return currentValue < cValueComparator;
	case ComparatorType::LOWER_THAN_OR_EQUAL:
		return currentValue <= cValueComparator;
	default:
		assert(("error happened at Precondition_Ressources_Is_Enough::isTrue switch" && true));
		break;
	}

}

const RessourceType Precondition::getRessourceType() const 
{
	return cRessourceType;
}

int Precondition::citizenNeededForMissingRessources(const Ressources* ressourcesBenefit, const unsigned int currentRessource) const
{
	unsigned int missingValue = cValueComparator - currentRessource;
	unsigned int citizenNeeded = missingValue / ressourcesBenefit->getRessource(cRessourceType);

	if (missingValue % ressourcesBenefit->getRessource(cRessourceType) != 0) {
		citizenNeeded += 1;
	}

 	return citizenNeeded;
}