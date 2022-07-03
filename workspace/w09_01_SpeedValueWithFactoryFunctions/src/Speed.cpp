#include "Speed.h"

using namespace velocity;

constexpr double MpsToKph = 3.6;
constexpr double MpsToMph = 2.23694;

bool velocity::isFasterThanWalking(Speed temprature) {
	return temprature.toKph() > 5.0;
}

Speed::Speed(double value) :
		value { value } {
}




double Speed::toKph() const {
	return value * MpsToKph;
}

double Speed::toMph() const {
	return value * MpsToMph;
}

double Speed::toMps() const {
	return value;
}

Speed Speed::fromMph(double value) {
	return Speed { value / MpsToMph };
}

Speed Speed::fromKph(double value) {
	return Speed { value / MpsToKph};
}

Speed Speed::fromMps(double value) {
	return Speed {value};
}
