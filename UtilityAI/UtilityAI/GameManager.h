#pragma once

#include <vector>

class Ressources;
class Action;
class Effect;
class Precondition;
class Pattern;
class AI;

class GameManager {

	Ressources* cRessources;
	Ressources* cRessourcesAdd;
	Ressources* cRessourcesRemove;

	AI* cAI;
	std::vector<Action*> cActions;
	std::vector<Precondition* > cPreconditions;
	std::vector<Effect* > cEffects;
	std::vector<Pattern* > cPatterns;

	void init();

public:
	GameManager();
	~GameManager();

	void start(unsigned int numberOfTurn);
};