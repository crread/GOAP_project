#include "Precondition.h"

#include <assert.h>

#include "EnumRessourcesType.h"
#include "EnumSignType.h"

bool Precondition::isTrue(unsigned int value) const {
	switch (cSign)
	{
	case SignType::HIGHER_THAN:
		return value > cValue;
	case SignType::HIGHER_OR_EQUAL:
		return value >= cValue;
	case SignType::EQUAL:
		return value == cValue;
	case SignType::LOWER_OR_EQUAL:
		return value <= cValue;
	case SignType::LOWER_THAN:
		return value < cValue;
	default:
		assert(("should not be in precondition::isTrue default switch" && true));
		break;
	}
}

RessourcesType Precondition::getRessourceType() const {
	return cRessourcesType;
}