#pragma once

enum class OperatorType;
enum class RessourcesType;
class Ressources;
 
class Effect {

	OperatorType cOperatorType;
	RessourcesType cRessourceType;

public:
	Effect(const OperatorType operatorType, const RessourcesType ressourceType) : cOperatorType(operatorType), cRessourceType(ressourceType) {};	
	~Effect() {};
	void apply(Ressources* ressources, const Ressources* cRessourcesAdd, const Ressources* cRessourcesRemove) const;
};
