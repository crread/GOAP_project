#pragma once

#include <vector>

#include "Ressources.h"

struct Action;
class Precondition;

struct Node {
	const Action* sAction;
	const Precondition* sPrecondition;
	const unsigned int sCoast;
	const unsigned int sCitizenNeededForAction;

	Node(const Action* action, const Precondition* precondition, const unsigned int coast, const unsigned int citizenNeededForAction) : sAction(action), sPrecondition(precondition), sCoast(coast), sCitizenNeededForAction(citizenNeededForAction) {};
	~Node() {
		delete sAction;
		delete sPrecondition;
	};
};

class GOAPResolver {
	const Action* cStart;
	Ressources cRessources;
	const Ressources* cRessourcesBenefits;
	std::vector<Action*> cActions;
	std::vector<std::vector<Node>> cNodes;
	unsigned int maxCitizen = 0;

	void checkPrecondition(const Action* action);
	Node createNewNode(const Action* action, const Precondition* precondition, const unsigned int coast, const Node* previousNode = nullptr) const;
	void AddNewNodes(const Precondition* precondition, const unsigned int neededCitizen);
	void updateWorld();
	void clearNodes();
	void newActionsList(const bool copyFirstOne);
	void applyEffects(const Action* action, const int quantity);
	void resolveGOAP();
public:

	GOAPResolver();
	GOAPResolver(const Action* action, const Ressources* ressourcesBenefits) : cStart(action), cRessourcesBenefits(ressourcesBenefits) {};
	~GOAPResolver() {};

	Ressources startResolver(const Ressources ressources);
};