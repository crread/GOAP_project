#pragma once

#include <vector>
#include <iostream>

enum class RessourcesType;
enum class OperatorType;

class Ressources {

	std::vector<int> cRessources;

public:
	Ressources();
	~Ressources() {};
	int getRessource(const RessourcesType ressourceType) const;
	void setRessource(const RessourcesType ressourceType, const int quantity);
	void operateRessoures(const OperatorType operatorType, const RessourcesType ressourceType, const unsigned int quantity);

	friend std::ostream& operator<<(std::ostream& os, const Ressources& ressources);
};