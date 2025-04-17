#include "MathUtilityForText.h"

float RandomFloat() {
	
	float result = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
	return result;
}
