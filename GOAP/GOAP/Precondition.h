#pragma once

#include "EnumComparatorType.h"
#include "EnumRessourceType.h"
#include "EnumFlagType.h"

#include <assert.h>

class Ressources;

class Precondition {
protected:
	ComparatorType cComparator;
	unsigned int cValueComparator;
	RessourceType cRessourceType;

public:
	FlagType cFlag;

	Precondition() {};
	~Precondition() {};

	virtual bool const isTrue(const unsigned int& currentValue) const = 0;
	int citizenNeededForMissingRessources(const Ressources* ressourcesBenefit, const unsigned int currentRessource) const;
	const RessourceType getRessourceType() const;
};

class Precondition_Ressources_Is_Enough : public Precondition {
public:
	Precondition_Ressources_Is_Enough() {};
	Precondition_Ressources_Is_Enough(const ComparatorType& comparatorType, const unsigned int& valueComparator, const RessourceType& ressourceType, const FlagType& flag);
	~Precondition_Ressources_Is_Enough() {};

	virtual bool const isTrue(const unsigned int& currentValue) const override;
};