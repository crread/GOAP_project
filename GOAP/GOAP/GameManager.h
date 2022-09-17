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

	Ressources* cRessourcesAvailable;
	Ressources* cRessourcesBenefits;
	GOAPResolver solver;

	unsigned int cFoodCoastCitizenPerTurn;

	std::vector<int> cBenefitFarm;

	unsigned int cCitizenWinCondition;
	unsigned int cCitizenLoseCondition;

	void initAssets();
public:
	GameManager();
	~GameManager();
	void thick();
};