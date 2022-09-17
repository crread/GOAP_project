#pragma once

#include <iostream>
#include <vector>

#include "EnumRessourceType.h"

class Ressources {

	std::vector<int> cRessources;

public:

	Ressources();
	~Ressources() {};

	void addRessource(const RessourceType& ressource, const int& quantity);
	void updateRessources(const RessourceType ressourceType, const Ressources* ressourceApplication, const int citizenNumber);
	int getRessource(const RessourceType& ressourceType) const;

	friend std::ostream& operator<<(std::ostream& os, const Ressources& ressources);
};