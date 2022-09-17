#pragma once

#include "Precondition.h"
#include "Effect.h"
#include "Ressources.h"
#include "Action.h"
#include "GOAPResolver.h"

#include "EnumFlagType.h"

#include <vector>
#include <string>

class GameManager {
	std::vector<Action*> cActionsGC;
	std::vector<Precondition*> cPreconditionsGC;
	std::vector<Effect*> cEffectsGC;

	Ressources* cRessources;
	Ressources* cRessourcesAdd;
	Ressources* cRessourcesRemove;
	GOAPResolver solver;

	unsigned int cCitizenWinCondition;

	void initAssets();
public:
	GameManager();
	~GameManager();
	void thick();
};