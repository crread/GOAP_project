#include "GOAPResolver.h"

#include <vector>
#include <assert.h>

#include "Action.h"
#include "Precondition.h"
#include "EnumFlagType.h"

Ressources GOAPResolver::startResolver(const Ressources ressources) 
{
	cRessources = ressources;
	maxCitizen = cRessources.getRessource(RessourceType::CITIZEN);

	while (cRessources.getRessource(RessourceType::CITIZEN) > 0) {
		assert(("while loop should have stopped" && cRessources.getRessource(RessourceType::CITIZEN) <= 0));
		clearNodes();
		newActionsList(false);
		checkPrecondition(cStart);
		resolveGOAP();
	}

	cRessources.addRessource(RessourceType::CITIZEN, maxCitizen);
	return cRessources;
}

void GOAPResolver::resolveGOAP()
{
	unsigned int lowerCoast = cNodes[0][cNodes[0].size() - 1].sCoast;
	unsigned int idxListNodeLowerCoast = 0;

	for (unsigned int i = 1; i < cNodes.size(); i++)
	{
		unsigned int coastListNode = cNodes[i][cNodes[i].size() - 1].sCoast;

		if (lowerCoast > coastListNode)
		{
			lowerCoast = coastListNode;
			idxListNodeLowerCoast = i;
		}
	}

	std::vector<Node> listSelected = cNodes[idxListNodeLowerCoast];

	for (unsigned int i = listSelected.size() - 1; i >= 0; i--)
	{
		Node currentNode = listSelected[i];
	}
}

void GOAPResolver::newActionsList(const bool copyFirstOne)
{
	cNodes.push_back(std::vector<Node>());

	if (copyFirstOne) 
	{
		for (unsigned int i = 0; i < cNodes[0].size() - 2; i++) 
		{
			cNodes[cNodes.size() - 1].push_back(cNodes[0][i]);
		}
	}
}

void GOAPResolver::clearNodes() 
{
	for (auto listAction : cNodes) 
	{
		listAction.clear();
	}

	cNodes.clear();
}

Node GOAPResolver::createNewNode(const Action* action, const Precondition* precondition, const unsigned int citizenNeeded, const Node* previousNode = nullptr) const
{
	if (previousNode != nullptr) {
		return Node(action, precondition, previousNode->sCoast + action->sCoast, citizenNeeded);
	}
	return Node(action, precondition, action->sCoast, citizenNeeded);
}

void GOAPResolver::updateWorld() 
{
	//for () 
	//{

	//}
}

void GOAPResolver::AddNewNodes(const Precondition* precondition, const unsigned int neededCitizen)
{
	auto listNode = cNodes[0];
	int idx = 0;

	for (const Action* action : cActions)
	{
		for (const Effect* effect : action->sEffects)
		{
			if (effect->cFlag == precondition->cFlag)
			{
				if (listNode[listNode.size() - 1].sPrecondition->cFlag == precondition->cFlag)
				{
					newActionsList(true);
					idx = cNodes.size() - 1;
				}

				Node newNode = createNewNode(action, precondition, neededCitizen);
				cNodes[idx].push_back(newNode);
				idx = 0;
				break;
			}
		}
	}
}

void GOAPResolver::checkPrecondition(const Action* action)
{
	for (const Precondition* precondition : action->sPreconditions)
	{
		int ressourceQuantity = cRessources.getRessource(precondition->getRessourceType());

		if (precondition->cFlag == FlagType::INCREASE_HOUSE)
		{
			ressourceQuantity = cRessources.getPlaceAvailable();
		}

		if (!precondition->isTrue(ressourceQuantity))
		{
			AddNewNodes(precondition, precondition->citizenNeededForMissingRessources(cRessourcesBenefits, ressourceQuantity));
		}
	}
}

void GOAPResolver::applyEffects(const Action* action, const int quantity)
{
	for (const Effect* effect : action->sEffects)
	{
		int benefitPerAction = cRessourcesBenefits->getRessource(currentNode.sPrecondition->getRessourceType());

		switch (effect->cFlag)
		{
		case FlagType::INCREASE_FOOD:
		case FlagType::INCREASE_WOOD:
		case FlagType::INCREASE_IRON:
			cRessources.addRessource(effect->cType, quantity);
			break;
		case FlagType::DECREASE_FOOD:
		case FlagType::DECREASE_WOOD:
		case FlagType::DECREASE_IRON:
			cRessources.removeRessource(effect->cType, quantity);
			break;
		case FlagType::INCREASE_HOUSE:
		case FlagType::INCREASE_CITIZEN:
			cRessources.removeRessource(effect->cType, 1);
			break;
		default:
			break;
		}
	}
}