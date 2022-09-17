#include "AI.h"

#include <algorithm> 
#include <iostream>

#include "Ressources.h"
#include "Precondition.h"
#include "Pattern.h"
#include "Effect.h"
#include "Action.h"

void AI::processStart(Ressources* ressources) 
{
	clearAI();
	getAvailableAction(ressources);
	getCoasts();
	Node nodeSelected = selectBestNode();
	applyEffects(nodeSelected.sAction, ressources);
}

Node AI::selectBestNode() const
{
	float higherWeight = cNodesAvailable[0].sCoast;
	Node higherNode = cNodesAvailable[0];

	for (Node node : cNodesAvailable)
	{
		if (node.sCoast > higherWeight)
		{
			higherWeight = node.sCoast;
			higherNode = node;
		}
	}

	return higherNode;
}

void AI::applyEffects(const Action* action, Ressources* ressources) const
{
	for (const Effect* effect : action->getEffects())
	{
		effect->apply(ressources, cRessourcesAdd, cRessourcesRemove);
	}

	std::cout << *action << std::endl;
}

void AI::getCoasts()
{
	for (Node& node : cNodesAvailable)
	{
		node.sCoast = node.sAction->getPattern()->getDecisionWeight(node.sAction->getWeight());
	}
}

void AI::clearAI()
{
	cNodesAvailable.clear();
}

void AI::getAvailableAction(Ressources* ressources)
{
	for (const Action* action : cActionList)
	{
		if (std::all_of(action->getPreconditions()->begin(), action->getPreconditions()->end(), [&ressources](const Precondition* precondition)
						-> bool {return precondition->isTrue(ressources->getRessource(precondition->getRessourceType()));})
		   )
		{
			cNodesAvailable.push_back(createNode(action));
		}
	}
}

Node AI::createNode(const Action* action) const
{
	return Node(action);
}