#pragma once

#include <string>
#include <list>

#include "Precondition.h"
#include "Effect.h"

struct Action
{
	std::string sDescription;
	std::list<Precondition*> sPreconditions;
	std::list<Effect*> sEffects;
	unsigned int sCoast;

	Action(const std::string description,const unsigned int coast) : sDescription(description), sCoast(coast) {};
};