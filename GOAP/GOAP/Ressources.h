#pragma once

#include "EnumRessourceType.h"

#include <vector>

class Ressources {

	std::vector<unsigned int> cRessources;

public:

	Ressources();
	~Ressources() {};

	void addRessource(const RessourceType& ressource, const int& quantity);
	void removeRessource(const RessourceType& ressource, const int& quantity);
	int getRessource(const RessourceType& ressourceType) const;
	void removeUptakeFoodPerTurn(const unsigned int& foodUptakePerCitizen);
	int getPlaceAvailable() const;
};