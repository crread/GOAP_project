#include "GameManager.h"

#define NEEDED_FOOD_FOR_CITIZEN 100
#define NEEDED_WOOD_FOR_HOUSE 50
#define NEEDED_IRON_FOR_HOUSE 25

GameManager::GameManager() {
	cRessourcesAvailable = new Ressources();
	cRessourcesBenefits = new Ressources();

	cRessourcesAvailable->addRessource(RessourceType::WOOD, 0);
	cRessourcesAvailable->addRessource(RessourceType::IRON, 0);
	cRessourcesAvailable->addRessource(RessourceType::FOOD, 100);
	cRessourcesAvailable->addRessource(RessourceType::CITIZEN, 10);
	cRessourcesAvailable->addRessource(RessourceType::HOUSE, 5);

	cRessourcesBenefits->addRessource(RessourceType::WOOD, 10);
	cRessourcesBenefits->addRessource(RessourceType::IRON, 5);
	cRessourcesBenefits->addRessource(RessourceType::FOOD, 10);
	cRessourcesBenefits->addRessource(RessourceType::CITIZEN, 1);
	cRessourcesBenefits->addRessource(RessourceType::HOUSE, 1);

	cFoodCoastCitizenPerTurn = 10;
	cCitizenWinCondition = 100;
	cCitizenLoseCondition = 1;

	initAssets();

	GOAPResolver solver = GOAPResolver(cActionsGC[cActionsGC.size() - 1], cRessourcesBenefits);
}

void GameManager::initAssets() {

	Precondition* preconditionFreeCitizen = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, 1, RessourceType::CITIZEN, FlagType::DECREASE_FREE_CITIZEN);
	cPreconditionsGC.push_back(preconditionFreeCitizen);
	Precondition* preconditionEnoughFood = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, NEEDED_FOOD_FOR_CITIZEN, RessourceType::FOOD, FlagType::INCREASE_FOOD);
	cPreconditionsGC.push_back(preconditionEnoughFood);
	Precondition* preconditionEnoughWood = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, NEEDED_WOOD_FOR_HOUSE, RessourceType::WOOD, FlagType::INCREASE_WOOD);
	cPreconditionsGC.push_back(preconditionEnoughWood);
	Precondition* preconditionEnoughIron = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, NEEDED_IRON_FOR_HOUSE, RessourceType::IRON, FlagType::INCREASE_IRON);
	cPreconditionsGC.push_back(preconditionEnoughIron);
	Precondition* preconditionEnoughFreePlace = new Precondition_Ressources_Is_Enough(ComparatorType::HIGHER_THAN_OR_EQUAL, 1, RessourceType::CITIZEN, FlagType::INCREASE_HOUSE);
	cPreconditionsGC.push_back(preconditionEnoughFreePlace);

	Effect* effectRemoveFreeCitizen = new Effect_Alter_Ressources(RessourceType::CITIZEN, OperandType::MINUS, FlagType::DECREASE_FREE_CITIZEN);
	cEffectsGC.push_back(effectRemoveFreeCitizen);
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

	Action* actionFarmFood = new Action("Envoyez des villageois récolter de la nourriture" ,3);
	actionFarmFood->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmFood->sEffects.push_back(effectRemoveFreeCitizen);
	actionFarmFood->sEffects.push_back(effectAddFood);

	Action* actionFarmWood = new Action("Envoyez des villageois couper du bois", 5);
	actionFarmWood->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmWood->sEffects.push_back(effectRemoveFreeCitizen);
	actionFarmWood->sEffects.push_back(effectAddWood);
	cActionsGC.push_back(actionFarmWood);

	Action* actionFarmIron = new Action("Envoyez des villageois récolter du fer", 7);
	actionFarmWood->sPreconditions.push_back(preconditionFreeCitizen);
	actionFarmWood->sEffects.push_back(effectRemoveFreeCitizen);
	actionFarmWood->sEffects.push_back(effectAddIron);
	cActionsGC.push_back(actionFarmIron);

	Action* actionBuildHouse = new Action("Construire des maison", 10);
	actionFarmWood->sPreconditions.push_back(preconditionEnoughWood);
	actionFarmWood->sPreconditions.push_back(preconditionEnoughIron);
	actionFarmWood->sEffects.push_back(effectAddHouse);
	actionFarmWood->sEffects.push_back(effectRemoveIron);
	actionFarmWood->sEffects.push_back(effectRemoveWood);
	cActionsGC.push_back(actionBuildHouse);

	Action* actionNewCitizen = new Action("Ajoute un citoyen", 1);
	actionFarmWood->sPreconditions.push_back(preconditionEnoughFreePlace);
	actionFarmWood->sPreconditions.push_back(preconditionEnoughFood);
	actionFarmWood->sEffects.push_back(effectAddCitizen);
	cActionsGC.push_back(actionNewCitizen);
}

GameManager::~GameManager() {

	for (auto it = cPreconditionsGC.begin(); it != cPreconditionsGC.end(); it++) {
		delete& it;
	}

	for (auto it = cEffectsGC.begin(); it != cEffectsGC.end(); it++) {
		delete& it;
	}

	for (auto it = cActionsGC.begin(); it != cActionsGC.end(); it++) {
		delete& it;
	}

	delete cRessourcesBenefits;
	delete cRessourcesAvailable;

}

void GameManager::thick() {
	
	// ne copie pas l'état du monde courent, à modifier.
	*cRessourcesAvailable = solver.startResolver(*cRessourcesAvailable);



	// Permet d'enlever de la nourriture par tour, à conserver pour peut-être rajouter plus tard
	//cRessourcesAvailable.removeUptakeFoodPerTurn(cFoodCoastCitizenPerTurn);

}