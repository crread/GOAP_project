#include "Action.h"

#include <string>
#include <iostream>   

#include "EnumRessourcesType.h"
#include "Ressources.h"

Action::Action(const std::string description, const RessourcesType ressourceType, const unsigned int actionWeight) : cDescription(description), cRessourceType(ressourceType), cActionWeight(actionWeight) {
	cPrecondition = new std::vector<const Precondition*>;
	cDefautWeight = actionWeight;
};

Action::~Action() {
	delete cPrecondition;
}

void Action::AddEffect(const Effect* effect) {
	cEffect.push_back(effect);
}

void Action::AddPrecondition(const Precondition* precondition) {
	cPrecondition->push_back(precondition);
}

void Action::AddPattern(const Pattern* pattern) {
	cPattern = pattern;
}

const Pattern* Action::getPattern() const {
	return cPattern;
}

std::vector<const Effect*> Action::getEffects() const {
	return cEffect;
}

std::vector<const Precondition*>* Action::getPreconditions() const {
	return cPrecondition;
}

void Action::setWeight(unsigned int weight)
{
	cActionWeight = weight;
}

unsigned int Action::getWeight() const
{
	return cActionWeight;
}

void Action::updateWeight(const Ressources* ressources)
{
	auto currentRessourceState = ressources->getRessource(cRessourceType);

	if (currentRessourceState == 0) {
		cActionWeight = 100;
	}
	else if (currentRessourceState < 100) {
		cActionWeight = 100 - (ressources->getRessource(cRessourceType) % 100) + cDefautWeight;

		if (cActionWeight >= 100) {
			cActionWeight = 100;
		}
	}
	else if (currentRessourceState >= 100) {
		cActionWeight = 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Action& action) {
	os << action.cDescription;
	return os;
}
