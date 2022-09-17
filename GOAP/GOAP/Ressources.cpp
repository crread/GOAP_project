#include "Ressources.h"

#include <iostream>

Ressources::Ressources() 
{
	cRessources.resize((int) RessourceType::LENGTH);
}

void Ressources::addRessource(const RessourceType& ressource, const int& quantity) 
{
	cRessources[(int) ressource] += quantity;
}

int Ressources::getRessource(const RessourceType& ressourceType) const 
{
	return 	cRessources[(int)ressourceType];
}

void Ressources::updateRessources(const RessourceType ressourceType, const Ressources* ressourceApplication, const int citizenNumber) {
	cRessources[(int)ressourceType] += ressourceApplication->getRessource(ressourceType) * citizenNumber;
}

std::ostream& operator<<(std::ostream& os, const Ressources& ressources) {
	os << "----------" << std::endl;
	os << "food : " << ressources.cRessources[(int)RessourceType::FOOD] << std::endl;
	os << "iron : " << ressources.cRessources[(int)RessourceType::IRON] << std::endl;
	os << "wood : " << ressources.cRessources[(int)RessourceType::WOOD] << std::endl;
	os << "house : " << ressources.cRessources[(int)RessourceType::HOUSE] << std::endl;
	os << "citizen : " << ressources.cRessources[(int)RessourceType::CITIZEN] << std::endl;
	os << "space : " << ressources.cRessources[(int)RessourceType::SPACE] << std::endl;
	return os;
}