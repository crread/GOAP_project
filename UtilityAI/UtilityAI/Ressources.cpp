#include "Ressources.h"

#include <assert.h>
#include <iostream>

#include "EnumRessourcesType.h"
#include "EnumOperatorType.h"

Ressources::Ressources() {
	cRessources.resize((size_t)RessourcesType::LENGTH, 0);
}

int Ressources::getRessource(const RessourcesType ressourceType) const {
	return cRessources[(int) ressourceType];
}

void Ressources::setRessource(const RessourcesType ressourceType, const int quantity) {
	cRessources[(int) ressourceType] = quantity;
}

void Ressources::operateRessoures(const OperatorType operatorType, const RessourcesType ressourceType, const unsigned int quantity)
{
	switch (operatorType)
	{
	case OperatorType::PLUS:
		cRessources[(int)ressourceType] += quantity;
		break;
	case OperatorType::MINUS:
		cRessources[(int)ressourceType] -= quantity;
		break;
	default:
		assert(("should not be in ressources operatorRessources default switch") && true);
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const Ressources& ressources)
{
	os << "---------------" << std::endl;
	os << "food state : " << (int) ressources.getRessource(RessourcesType::FOOD) << std::endl;
	os << "wood state : " << (int) ressources.getRessource(RessourcesType::WOOD) << std::endl;
	os << "iron state : " << (int) ressources.getRessource(RessourcesType::IRON) << std::endl;
	os << "citizen state : " << (int) ressources.getRessource(RessourcesType::CITIZEN) << std::endl;
	os << "soldier state : " << (int) ressources.getRessource(RessourcesType::SOLDIER) << std::endl;
	os << "house state : " << (int) ressources.getRessource(RessourcesType::HOUSE) << std::endl;
	os << "free space state : " << (int)ressources.getRessource(RessourcesType::SPACE) << std::endl;
	os << "---------------" << std::endl;
	return os;
}