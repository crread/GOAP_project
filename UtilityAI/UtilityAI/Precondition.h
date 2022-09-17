#pragma once

enum class SignType;
enum class RessourcesType;

class Precondition {
	unsigned int cValue;
	SignType cSign;
	RessourcesType cRessourcesType;

public:
	Precondition(const SignType sign, const unsigned int value, const RessourcesType ressourcesType) : cSign(sign), cValue(value), cRessourcesType(ressourcesType) {};
	~Precondition() {};

	RessourcesType getRessourceType() const;
	bool isTrue(unsigned int value) const;
};