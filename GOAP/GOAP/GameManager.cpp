#include "GameManager.h"

#include <iostream>

#include "Ressources.h"

#define DEFAULT_RESSOURCE_FOOD 100
#define DEFAULT_RESSOURCE_IRON 10
#define DEFAULT_RESSOURCE_WOOD 25
#define DEFAULT_RESSOURCE_CITIZEN 10
#define DEFAULT_RESSOURCE_HOME 5
#define DEFAULT_RESSOURCE_SPACE 0

#define ADD_RESSOURCE_FOOD 10
#define ADD_RESSOURCE_IRON 4
#define ADD_RESSOURCE_WOOD 5
#define ADD_RESSOURCE_CITIZEN 1
#define ADD_RESSOURCE_HOME 1
#define ADD_RESSOURCE_SPACE 2

#define REMOVE_RESSOURCE_FOOD -100
#define REMOVE_RESSOURCE_IRON -25
#define REMOVE_RESSOURCE_WOOD -50
#define REMOVE_RESSOURCE_CITIZEN -1
#define REMOVE_RESSOURCE_HOME -1
#define REMOVE_RESSOURCE_SPACE -1

GameManager::GameManager() {
	cRessources = new Ressources();
	cRessourcesAdd = new Ressources();
	cRessourcesRemove = new Ressources();

	cRessources->addRessource(RessourceType::WOOD, DEFAULT_RESSOURCE_WOOD);
	cRessources->addRessource(RessourceType::IRON, DEFAULT_RESSOURCE_IRON);
	cRessources->addRessource(RessourceType::FOOD, DEFAULT_RESSOURCE_FOOD);
	cRessources->addRessource(RessourceType::CITIZEN, DEFAULT_RESSOURCE_CITIZEN);
	cRessources->addRessource(RessourceType::HOUSE, DEFAULT_RESSOURCE_HOME);
	cRessources->addRessource(RessourceType::SPACE, DEFAULT_RESSOURCE_SPACE);

	cRessourcesAdd->addRessource(RessourceType::WOOD, ADD_RESSOURCE_WOOD);
	cRessourcesAdd->addRessource(RessourceType::IRON, ADD_RESSOURCE_IRON);
	cRessourcesAdd->addRessource(RessourceType::FOOD, ADD_RESSOURCE_FOOD);
	cRessourcesAdd->addRessource(RessourceType::CITIZEN, ADD_RESSOURCE_CITIZEN);
	cRessourcesAdd->addRessource(RessourceType::HOUSE, ADD_RESSOURCE_HOME);
	cRessourcesAdd->addRessource(RessourceType::SPACE, ADD_RESSOURCE_SPACE);

	cRessourcesRemove->addRessource(RessourceType::WOOD, REMOVE_RESSOURCE_WOOD);
	cRessourcesRemove->addRessource(RessourceType::IRON, REMOVE_RESSOURCE_IRON);
	cRessourcesRemove->addRessource(RessourceType::FOOD, REMOVE_RESSOURCE_FOOD);
	cRessourcesRemove->addRessource(RessourceType::CITIZEN, REMOVE_RESSOURCE_CITIZEN);
	cRessourcesRemove->addRessource(RessourceType::HOUSE, REMOVE_RESSOURCE_HOME);
	cRessourcesRemove->addRessource(RessourceType::SPACE, REMOVE_RESSOURCE_SPACE);

	initAssets();

	solver = GOAPResolver(cActionsGC[cActionsGC.size() - 1], cRessourcesAdd, cRessourcesRemove, cActionsGC);
}

void GameManager::initAssets() {
	Precondition* preconditionFreeCitizen = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, REMOVE_RESSOURCE_CITIZEN, RessourceType::CITIZEN, FlagType::END_SEARCH);
	cPreconditionsGC.push_back(preconditionFreeCitizen);
	Precondition* preconditionEnoughFood = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, REMOVE_RESSOURCE_FOOD, RessourceType::FOOD, FlagType::INCREASE_FOOD);
	cPreconditionsGC.push_back(preconditionEnoughFood);
	Precondition* preconditionEnoughWood = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, REMOVE_RESSOURCE_WOOD, RessourceType::WOOD, FlagType::INCREASE_WOOD);
	cPreconditionsGC.push_back(preconditionEnoughWood);
	Precondition* preconditionEnoughIron = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, REMOVE_RESSOURCE_IRON, RessourceType::IRON, FlagType::INCREASE_IRON);
	cPreconditionsGC.push_back(preconditionEnoughIron);
	Precondition* preconditionEnoughFreePlace = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, REMOVE_RESSOURCE_SPACE, RessourceType::SPACE, FlagType::INCREASE_HOUSE);
	cPreconditionsGC.push_back(preconditionEnoughFreePlace);

	Effect* effectRemoveCitizen = new Effect_Alter_Ressources(RessourceType::CITIZEN, OperandType::MINUS, FlagType::DECREASE_CITIZEN);
	cEffectsGC.push_back(effectRemoveCitizen);
	Effect* effectRemoveFood = new Effect_Alter_Ressources(RessourceType::FOOD, OperandType::MINUS, FlagType::DECREASE_FOOD);
	cEffectsGC.push_back(effectRemoveFood);
	Effect* effectAddFood = new Effect_Alter_Ressources(RessourceType::FOOD, OperandType::PLUS, FlagType::INCREASE_FOOD);
	cEffectsGC.push_back(effectAddFood);
	Effect* effectRemoveIron = new Effect_Alter_Ressources(RessourceType::IRON, OperandType::MINUS, FlagType::DECREASE_IRON);
	cEffectsGC.push_back(effectRemoveIron);
	Effect* effectRemoveWood = new Effect_Alter_Ressources(RessourceType::WOOD, OperandType::MINUS, FlagType::DECREASE_WOOD);
	cEffectsGC.push_back(effectRemoveWood);
	Effect* effectAddWood = new Effect_Alter_Ressources(RessourceType::WOOD, OperandType::PLUS, FlagType::INCREASE_WOOD);
	cEffectsGC.push_back(effectAddWood);
	Effect* effectAddIron = new Effect_Alter_Ressources(RessourceType::IRON, OperandType::PLUS, FlagType::INCREASE_IRON);
	cEffectsGC.push_back(effectAddIron);
	Effect* effectAddCitizen = new Effect_Alter_Ressources(RessourceType::CITIZEN, OperandType::PLUS, FlagType::INCREASE_CITIZEN);
	cEffectsGC.push_back(effectAddCitizen);
	Effect* effectAddHouse = new Effect_Alter_Ressources(RessourceType::HOUSE, OperandType::PLUS, FlagType::INCREASE_HOUSE);
	cEffectsGC.push_back(effectAddHouse);
	Effect* effectAddSpace = new Effect_Alter_Ressources(RessourceType::SPACE, OperandType::PLUS, FlagType::INCREASE_SPACE);
	cEffectsGC.push_back(effectAddSpace);
	Effect* effectRemoveSpace = new Effect_Alter_Ressources(RessourceType::SPACE, OperandType::MINUS, FlagType::DECREASE_SPACE);
	cEffectsGC.push_back(effectRemoveSpace);

	Action* actionFarmFood = new Action("Send citizen to farm some food" ,3);
	actionFarmFood->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmFood->sEffects.push_back(effectRemoveCitizen);
	actionFarmFood->sEffects.push_back(effectAddFood);
	cActionsGC.push_back(actionFarmFood);

	Action* actionFarmWood = new Action("Send citizen to farm some wood", 5);
	actionFarmWood->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmWood->sEffects.push_back(effectRemoveCitizen);
	actionFarmWood->sEffects.push_back(effectAddWood);
	cActionsGC.push_back(actionFarmWood);

	Action* actionFarmIron = new Action("Send citizen to farm some iron", 7);
	actionFarmIron->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmIron->sEffects.push_back(effectRemoveCitizen);
	actionFarmIron->sEffects.push_back(effectAddIron);
	cActionsGC.push_back(actionFarmIron);

	Action* actionBuildHouse = new Action("Build a house", 10);
	actionBuildHouse->sPreconditions.push_back(preconditionEnoughWood);
	actionBuildHouse->sPreconditions.push_back(preconditionEnoughIron);
	actionBuildHouse->sEffects.push_back(effectAddHouse);
	actionBuildHouse->sEffects.push_back(effectRemoveIron);
	actionBuildHouse->sEffects.push_back(effectRemoveWood);
	actionBuildHouse->sEffects.push_back(effectAddSpace);
	cActionsGC.push_back(actionBuildHouse);

	Action* actionNewCitizen = new Action("create new citizen", 1);
	actionNewCitizen->sPreconditions.push_back(preconditionEnoughFreePlace);
	actionNewCitizen->sPreconditions.push_back(preconditionEnoughFood);
	actionNewCitizen->sEffects.push_back(effectAddCitizen);
	actionNewCitizen->sEffects.push_back(effectRemoveFood);
	actionNewCitizen->sEffects.push_back(effectRemoveSpace);
	cActionsGC.push_back(actionNewCitizen);
}

GameManager::~GameManager() {
	for (const Precondition* precondition : cPreconditionsGC) {
		delete precondition;
	}

	for (const Effect* effect : cEffectsGC) {
		delete effect;
	}

	for (const Action* action : cActionsGC) {
		delete action;
	}


	delete cRessources;
	delete cRessourcesAdd;
	delete cRessourcesRemove;
}

void GameManager::thick() {
	cCitizenWinCondition = 100;

	int i = 1;

	while ((unsigned int) cRessources->getRessource(RessourceType::CITIZEN) <= cCitizenWinCondition)
	{
		std::cout << "tour : " << i << std::endl;
		solver.startResolver(cRessources);
		i++;
	}
}