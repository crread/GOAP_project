#include "GameManager.h"

#include <iostream>
#include<chrono>
#include<thread>

#include "EnumRessourcesType.h"
#include "EnumOperatorType.h"
#include "EnumSignType.h"
#include "Ressources.h"
#include "Action.h"
#include "Precondition.h"
#include "Effect.h"
#include "Pattern.h"
#include "AI.h"

#define ADD_FOOD_VALUE 25
#define ADD_WOOD_VALUE 20
#define ADD_IRON_VALUE 10
#define ADD_HOUSE_VALUE 1
#define ADD_CITIZEN_VALUE 1
#define ADD_SOLDIER_VALUE 1
#define ADD_SPACE_VALUE 2

#define REMOVE_FOOD_VALUE 70
#define REMOVE_WOOD_VALUE 50
#define REMOVE_IRON_VALUE 25
#define REMOVE_HOUSE_VALUE 1
#define REMOVE_CITIZEN_VALUE 1
#define REMOVE_SOLDIER_VALUE 1
#define REMOVE_SPACE_VALUE 1

#include <iostream>

GameManager::GameManager() {
	cRessources = new Ressources();
	cRessources->setRessource(RessourcesType::FOOD, 100);
	cRessources->setRessource(RessourcesType::WOOD, 20);
	cRessources->setRessource(RessourcesType::IRON, 15);
	cRessources->setRessource(RessourcesType::HOUSE, 5);
	cRessources->setRessource(RessourcesType::CITIZEN, 5);
	cRessources->setRessource(RessourcesType::SOLDIER, 5);
	cRessources->setRessource(RessourcesType::SPACE, 0);

	cRessourcesAdd = new Ressources();
	cRessourcesAdd->setRessource(RessourcesType::FOOD, ADD_FOOD_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::WOOD, ADD_WOOD_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::IRON, ADD_IRON_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::HOUSE, ADD_HOUSE_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::CITIZEN, ADD_CITIZEN_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::SOLDIER, ADD_SOLDIER_VALUE);
	cRessourcesAdd->setRessource(RessourcesType::SPACE, ADD_SPACE_VALUE);

	cRessourcesRemove = new Ressources();
	cRessourcesRemove->setRessource(RessourcesType::FOOD, REMOVE_FOOD_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::WOOD, REMOVE_WOOD_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::IRON, REMOVE_IRON_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::HOUSE, REMOVE_HOUSE_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::CITIZEN, REMOVE_CITIZEN_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::SOLDIER, REMOVE_SOLDIER_VALUE);
	cRessourcesRemove->setRessource(RessourcesType::SPACE, REMOVE_SPACE_VALUE);

	init();

	cAI = new AI(cActions, cRessourcesAdd, cRessourcesRemove);
}

GameManager::~GameManager() {

	delete cRessources;
	delete cAI;

	for (const Precondition* precondition : cPreconditions)
	{
		delete precondition;
	}

	for (const Effect* effect : cEffects)
	{
		delete effect;
	}

	for (const Pattern* pattern : cPatterns)
	{
		delete pattern;
	}

	for (const Action* action : cActions)
	{
		delete action;
	}

}

void GameManager::init()
{
	cPatterns.reserve(2);

	Pattern* patternLinear = new Pattern_Linear(1 ,1); // valeurs choisis aléatoirement
	Pattern* patternExponential = new Pattern_Exponential_Reversed();

	cPatterns.push_back(patternLinear);
	cPatterns.push_back(patternExponential);

	// iron effect
	Effect* effectAddIron = new Effect(OperatorType::PLUS, RessourcesType::IRON);
	cEffects.push_back(effectAddIron);
	Effect* effectRemoveIron = new Effect(OperatorType::MINUS, RessourcesType::IRON);
	cEffects.push_back(effectRemoveIron);

	// wood effect
	Effect* effectAddWood = new Effect(OperatorType::PLUS, RessourcesType::WOOD);
	cEffects.push_back(effectAddWood);
	Effect* effectRemoveWood = new Effect(OperatorType::MINUS, RessourcesType::WOOD);
	cEffects.push_back(effectRemoveWood);

	// food effect
	Effect* effectAddFood = new Effect(OperatorType::PLUS, RessourcesType::FOOD);
	cEffects.push_back(effectAddFood);
	Effect* effectRemoveFood = new Effect(OperatorType::MINUS, RessourcesType::FOOD);
	cEffects.push_back(effectRemoveFood);

	// citizen effect
	Effect* effectAddCitizen = new Effect(OperatorType::PLUS, RessourcesType::CITIZEN);
	cEffects.push_back(effectAddCitizen);
	Effect* effectRemoveCitizen = new Effect(OperatorType::MINUS, RessourcesType::CITIZEN);
	cEffects.push_back(effectRemoveCitizen);

	// soldier effect
	Effect* effectAddSoldier = new Effect(OperatorType::PLUS, RessourcesType::SOLDIER);
	cEffects.push_back(effectAddSoldier);
	Effect* effectRemoveSoldier = new Effect(OperatorType::MINUS, RessourcesType::SOLDIER);
	cEffects.push_back(effectRemoveSoldier);

	// house effect
	Effect* effectAddHouse = new Effect(OperatorType::PLUS, RessourcesType::HOUSE);
	cEffects.push_back(effectAddHouse);
	Effect* effectRemoveHouse = new Effect(OperatorType::MINUS, RessourcesType::HOUSE);
	cEffects.push_back(effectRemoveHouse);

	// space effect
	Effect* effectAddSpace = new Effect(OperatorType::PLUS, RessourcesType::SPACE);
	cEffects.push_back(effectAddSpace);
	Effect* effectRemoveSpace = new Effect(OperatorType::MINUS, RessourcesType::SPACE);
	cEffects.push_back(effectRemoveSpace);

	// précondition nouveau villageois
	Precondition* preconditionEnoughCitizen = new Precondition(SignType::HIGHER_OR_EQUAL, 25, RessourcesType::CITIZEN);
	cPreconditions.push_back(preconditionEnoughCitizen);

	// précondition farm nourriture
	Precondition* preconditionEnoughFood = new Precondition(SignType::HIGHER_OR_EQUAL, REMOVE_FOOD_VALUE, RessourcesType::FOOD);
	cPreconditions.push_back(preconditionEnoughFood);

	// précondition farm bois
	Precondition* preconditionEnoughWood = new Precondition(SignType::HIGHER_OR_EQUAL, REMOVE_WOOD_VALUE, RessourcesType::WOOD);
	cPreconditions.push_back(preconditionEnoughWood);

	// précondition farm fer
	Precondition* preconditionEnoughIron = new Precondition(SignType::HIGHER_OR_EQUAL, ADD_IRON_VALUE, RessourcesType::IRON);
	cPreconditions.push_back(preconditionEnoughIron);

	// précondition suffisament de place
	Precondition* preconditionEnoughPlace = new Precondition(SignType::HIGHER_OR_EQUAL, 1, RessourcesType::SPACE);
	cPreconditions.push_back(preconditionEnoughPlace);

	Action* actionCitizenAdd = new Action("Create a new citizen", RessourcesType::CITIZEN, 10);
	actionCitizenAdd->AddEffect(effectRemoveFood);
	actionCitizenAdd->AddEffect(effectAddCitizen);
	actionCitizenAdd->AddEffect(effectRemoveSpace);
	actionCitizenAdd->AddPrecondition(preconditionEnoughFood);
	actionCitizenAdd->AddPrecondition(preconditionEnoughPlace);
	actionCitizenAdd->AddPattern(patternExponential);
	cActions.push_back(actionCitizenAdd);

	Action* actionSoldierAdd = new Action("Create a new soldier", RessourcesType::SOLDIER, 15);
	actionSoldierAdd->AddEffect(effectRemoveFood);
	actionSoldierAdd->AddEffect(effectAddSoldier);
	actionSoldierAdd->AddEffect(effectRemoveSpace);
	actionSoldierAdd->AddPrecondition(preconditionEnoughFood);
	actionSoldierAdd->AddPrecondition(preconditionEnoughPlace);
	actionSoldierAdd->AddPattern(patternExponential);
	cActions.push_back(actionSoldierAdd);

	Action* actionHouseAdd = new Action("Create a new house", RessourcesType::HOUSE, 40);
	actionHouseAdd->AddEffect(effectAddHouse);
	actionHouseAdd->AddEffect(effectRemoveWood);
	actionHouseAdd->AddEffect(effectRemoveIron);
	actionHouseAdd->AddEffect(effectAddSpace);
	actionHouseAdd->AddPrecondition(preconditionEnoughWood);
	actionHouseAdd->AddPrecondition(preconditionEnoughIron);
	actionHouseAdd->AddPattern(patternExponential);
	cActions.push_back(actionHouseAdd);

	Action* actionWoodAdd = new Action("farm some wood", RessourcesType::WOOD, 5);
	actionWoodAdd->AddEffect(effectAddWood);
	actionWoodAdd->AddPattern(patternLinear);
	cActions.push_back(actionWoodAdd);

	Action* actionIronAdd = new Action("farm some iron", RessourcesType::IRON, 5);
	actionIronAdd->AddEffect(effectAddIron);
	actionIronAdd->AddPattern(patternLinear);
	cActions.push_back(actionIronAdd);

	Action* actionFoodAdd = new Action("farm some food", RessourcesType::FOOD, 35);
	actionFoodAdd->AddEffect(effectAddFood);
	actionFoodAdd->AddPattern(patternLinear);
	cActions.push_back(actionFoodAdd);
}

void GameManager::start(unsigned int numberOfTurn)
{
	for (unsigned int i = 0; i < numberOfTurn; i++)
	{
		std::cout << "new turn : " << (i + 1) << std::endl;
		cAI->processStart(cRessources);
		std::cout << *cRessources << std::endl;

		for (Action* action : cActions)
		{
			action->updateWeight(cRessources);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}