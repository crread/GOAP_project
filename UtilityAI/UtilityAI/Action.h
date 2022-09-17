#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "EnumRessourcesType.h"

class Effect;
class Pattern;
class Precondition;
class Pattern;
class Ressources;

class Action {
	std::vector<const Effect*> cEffect;
	std::vector<const Precondition*>* cPrecondition;
	const RessourcesType cRessourceType;
	const Pattern* cPattern;
	unsigned int cActionWeight;
	unsigned int cDefautWeight;
	std::string cDescription;

public:
	Action(const std::string description, const RessourcesType ressourceType, const unsigned int actionWeight);
	~Action();
	void AddEffect(const Effect* effect);
	void AddPrecondition(const Precondition* precondition);
	void AddPattern(const Pattern* pattern);
	void setWeight(unsigned int weight);

	std::vector<const Effect*> getEffects() const;
	std::vector<const Precondition*>* getPreconditions() const;
	const Pattern* getPattern() const;
	unsigned int getWeight() const;

	void updateWeight(const Ressources* ressources);

	friend std::ostream& operator<<(std::ostream& os, const Action& action);
};