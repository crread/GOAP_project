#include "Ressources.h"

Ressources::Ressources() 
{
	cRessources.reserve((int) RessourceType::LENGTH);
}

void Ressources::addRessource(const RessourceType& ressource, const int& quantity) 
{
	cRessources[(int) ressource] += quantity;
}

void Ressources::removeRessource(const RessourceType& ressource, const int& quantity) 
{
	if (cRessources[(int)ressource] < quantity) 
	{
		cRessources[(int)ressource] = 0;
	} else {
		cRessources[(int)ressource] -= quantity;
	}
}

int Ressources::getRessource(const RessourceType& ressourceType) const 
{
	return 	cRessources[(int)ressourceType];
}

int Ressources::getPlaceAvailable() const 
{
	return cRessources[(int) RessourceType::HOUSE] * 2 - cRessources[(int)RessourceType::CITIZEN];
}

void Ressources::removeUptakeFoodPerTurn(const unsigned int& foodUptakePerCitizen) 
{
	unsigned int foodUsed = cRessources[(int)RessourceType::CITIZEN] * foodUptakePerCitizen;
	this->removeRessource(RessourceType::FOOD, foodUsed);
}