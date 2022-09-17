#pragma once

#include <vector>

class Ressources;
class Action;

struct Node {
	const Action* sAction;
	float sCoast;

	Node(const Action* action): sAction(action), sCoast(0) {};
	~Node() {};
};

class AI {

	std::vector<Action* > cActionList;
	std::vector<Node> cNodesAvailable;

	const Ressources* cRessourcesAdd;
	const Ressources* cRessourcesRemove;

	void getAvailableAction(Ressources* ressources);
	void clearAI();
	void getCoasts();
	void applyEffects(const Action* action, Ressources* ressources) const;
	Node selectBestNode() const;
	Node createNode(const Action* action) const;

public:
	AI(const std::vector<Action*> actionList, const Ressources* ressourcesAdd, const Ressources* ressourcesRemove): cActionList(actionList), cRessourcesAdd(ressourcesAdd), cRessourcesRemove(ressourcesRemove) {};
	~AI() {};

	void processStart(Ressources* ressources);
};