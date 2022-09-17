#include "Effect.h"

#include <assert.h>

#include "Ressources.h"
#include "EnumOperatorType.h"

void Effect::apply(Ressources* ressources, const Ressources* cRessourcesAdd, const Ressources* cRessourcesRemove) const
{
	switch (cOperatorType)
	{
	case OperatorType::PLUS:
		ressources->operateRessoures(cOperatorType, cRessourceType , cRessourcesAdd->getRessource(cRessourceType));
		break;
	case OperatorType::MINUS:
		ressources->operateRessoures(cOperatorType, cRessourceType , cRessourcesRemove->getRessource(cRessourceType));
		break;
	default:
		assert(("should not be in effect apply default" && true));
		break;
	}
}