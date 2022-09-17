#pragma once

#include <vector>

#include "Ressources.h"

struct Action;
class Precondition;

struct Node {
	const Action* sAction;
	int sCitizenNeededForAction;
	unsigned int sCoast;

	Node(const Action* action, const unsigned int coast, int citizenNeededForAction) : sAction(action), sCoast(coast), sCitizenNeededForAction(citizenNeededForAction) {};
	~Node() {};
};

class GOAPResolver {
	const Action* cStart;
	Ressources* cRessourcesCopy;
	const Ressources* cRessourcesAdd;
	const Ressources* cRessourcesRemove;
	std::vector<Action*> cActions;
	std::vector<std::vector<Node>> cNodes;
	unsigned int maxCitizen = 0;

	void generateNodeList(const Action* action, const bool isFirstNode);
	Node createNewNode(const Action* action, const unsigned int coast) const;
	void clearNodes();
	void newActionsList(const bool copyFirstOne);
	void applyEffects(const Node node);
	unsigned int findLowerCoast() const;
	void AstartReversedResolve(const unsigned int idxList);
	void updateNodeList(Node node, const Precondition* precondition);
	void implementNewList();
public:

	GOAPResolver() {};
	GOAPResolver(const Action* action, const Ressources* ressourcesAdd, const Ressources* ressourcesremove, std::vector<Action*> actions) : cStart(action), cRessourcesAdd(ressourcesAdd), cRessourcesRemove(ressourcesremove), cActions(actions) {};
	~GOAPResolver();

	void startResolver(Ressources* ressources);
};