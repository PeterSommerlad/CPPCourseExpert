#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace velocity {

constexpr double MPH_TO_KMH { 1.60934 };

struct speed {
	constexpr
	explicit
	speed(long double kmh) :
			kmh { kmh } {
	}
	operator long double() const {
		return kmh;
	}
	long double const kmh;
};

constexpr speed operator"" _kmh(long double kmh) {
	return speed { kmh };
}

constexpr speed operator"" _kmh(unsigned long long kmh) {
	return speed { static_cast<long double>(kmh) };
}

constexpr speed operator"" _mph(long double mph) {
	return speed { mph * MPH_TO_KMH };
}

}

#endif /* VELOCITY_HPP_ */
