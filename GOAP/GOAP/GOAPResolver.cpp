#include "GOAPResolver.h"

#include <vector>
#include <assert.h>
#include <iostream>

#include "Action.h"
#include "Precondition.h"
#include "EnumFlagType.h"

GOAPResolver::~GOAPResolver() {
}

void GOAPResolver::startResolver(Ressources* ressources) {
	cRessourcesCopy = ressources;
	maxCitizen = cRessourcesCopy->getRessource(RessourceType::CITIZEN);

	while (cRessourcesCopy->getRessource(RessourceType::CITIZEN) > 0 && cRessourcesCopy->getRessource(RessourceType::CITIZEN) < 100) {
		clearNodes();
		newActionsList(false);
		Node newNode = createNewNode(cStart, 0);
		updateNodeList(newNode, nullptr);
		generateNodeList(cStart, true);
		const unsigned int idxListWithLowerCoast = findLowerCoast();
		AstartReversedResolve(idxListWithLowerCoast);
		std::cout << *cRessourcesCopy << std::endl;
	}

	cRessourcesCopy->addRessource(RessourceType::CITIZEN, maxCitizen);
}

void GOAPResolver::AstartReversedResolve(const unsigned int idxList)
{
	for (int i = cNodes[idxList].size() - 1; i >= 0; i--)
	{
		if (cRessourcesCopy->getRessource(RessourceType::CITIZEN) < 0) {
			return;
		}
		applyEffects(cNodes[idxList][i]);
	}
}

unsigned int GOAPResolver::findLowerCoast() const
{
	unsigned int idxLowerCoast = cNodes.size() - 1;

	for (unsigned int i = 0; i < cNodes.size() - 1; i++) 
	{
		if (cNodes[idxLowerCoast][cNodes[0].size() - 1].sCoast > cNodes[i][cNodes[0].size() - 1].sCoast) {
			idxLowerCoast = cNodes[i][cNodes[0].size() - 1].sCoast;
		}
	}

	return idxLowerCoast;
}

void GOAPResolver::generateNodeList(const Action* currentAction, const bool isFirstNode) {
	for (const Precondition* precondition : currentAction->sPreconditions)
	{
		int ressourceQuantity = cRessourcesCopy->getRessource(precondition->getRessourceType());

		if (!precondition->isTrue(ressourceQuantity) && precondition->cFlag != FlagType::END_SEARCH) {

			if (!isFirstNode)
			{
				int neededCitizen = precondition->citizenNeededForMissingRessources(cRessourcesAdd, ressourceQuantity);
				Node newNode = createNewNode(currentAction, neededCitizen);
				updateNodeList(newNode, precondition);
			}

			for (const Action* action : cActions)
			{
				for (const Effect* effect : action->sEffects)
				{
					if (effect->cFlag == precondition->cFlag)
					{
						generateNodeList(action, false);
					}
				}
			}
		}
	}
}

void GOAPResolver::updateNodeList(Node node, const Precondition* precondition) {

	if (cNodes.size() == 1) {
		if (cNodes[0].size() > 1) {
			node.sCoast += cNodes[0][cNodes[0].size() - 1].sCoast;
		}
		cNodes[0].push_back(node);
	}
	else {
		for (unsigned int i = 0; i < cNodes.size(); i++)
		{
			Node lastNodeImplemented = cNodes[i][cNodes[i].size() - 1];

			if (precondition != nullptr)
			{
				for (const Effect* effect : lastNodeImplemented.sAction->sEffects)
				{
					if (effect->cFlag == precondition->cFlag)
					{
						node.sCoast += lastNodeImplemented.sCoast;
						cNodes[i].push_back(node);
						break;
					}
				}
			}
			else {
				std::cout << "precondition is nullptr" << std::endl;
				cNodes[i].push_back(node);
			}
		}
	}
}

Node GOAPResolver::createNewNode(const Action* action, const unsigned int citizenNeeded) const
{
	return Node(action, action->sCoast, citizenNeeded);
}

void GOAPResolver::newActionsList(const bool copyFirstOne)
{
	cNodes.push_back(std::vector<Node>());

	if (copyFirstOne)
	{
		for (unsigned int i = 0; i < cNodes[0].size() - 1; i++) 
		{
			cNodes[cNodes.size() - 1].push_back(cNodes[0][i]);
		}
	}
}

void GOAPResolver::applyEffects(const Node node)
{
	for (Effect* effect : node.sAction->sEffects)
	{
		unsigned int citizensNeeded = node.sCitizenNeededForAction;

		if (effect->cFlag == FlagType::INCREASE_HOUSE ||
			effect->cFlag == FlagType::INCREASE_SPACE ||
			effect->cFlag == FlagType::DECREASE_SPACE ||
			effect->cFlag == FlagType::INCREASE_CITIZEN)
		{
			citizensNeeded = 0;
		}
		else if (citizensNeeded > cRessourcesCopy->getRessource(RessourceType::CITIZEN)) {
			citizensNeeded = cRessourcesCopy->getRessource(RessourceType::CITIZEN);
		}

		if (effect->cFlag == FlagType::INCREASE_CITIZEN) {
			maxCitizen += 1;
		}

		effect->applyEffect(cRessourcesCopy, cRessourcesAdd, cRessourcesRemove, citizensNeeded);
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