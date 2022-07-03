#ifndef SPEED_H_
#define SPEED_H_

#include <boost/operators.hpp>
#include <cmath>

namespace velocity {

namespace tags {

struct Kph;
struct Mph;
struct Mps;

}

template <typename Scale>
struct Speed: boost::addable<Speed<Scale>>,
			  boost::subtractable<Speed<Scale>>,
			  boost::equality_comparable<Speed<Scale>>,
			  boost::less_than_comparable<Speed<Scale>> {
	constexpr explicit Speed(double value) :
			value { value } {
	}

	constexpr explicit operator double() const {
		return value;
	}
	constexpr Speed & operator+=(Speed const & other) {
		value += other.value;
		return *this;
	}

	constexpr Speed & operator-=(Speed const & other) {
		return (*this) += -other;
	}

	constexpr Speed operator-() const {
		return Speed { -value };
	}

	constexpr bool operator==(Speed const & other) const {
		return std::abs(value - other.value) < epsilon;
	}

	constexpr bool operator<(Speed const & other) const {
		return value < other.value;
	}

private:
	constexpr static double epsilon = 0.0001;
	double value;
};

static constexpr double mphToKphFactor { 1.609344 };
static constexpr double mpsToKphFactor { 3.6 };
static constexpr double mpsToMphFactor { mpsToKphFactor / mphToKphFactor };

template<typename Target, typename Source>
struct ConversionTraits {
	constexpr static Speed<Target> convert(Speed<Source> sourceValue) = delete;
};

template<typename Same>
struct ConversionTraits<Same, Same> {
	constexpr static Speed<Same> convert(Speed<Same> sourceValue) {
		return sourceValue;
	}
};

template<>
struct ConversionTraits<tags::Mps, tags::Kph> {
	constexpr static Speed<tags::Mps> convert(Speed<tags::Kph> sourceValue) {
		return Speed<tags::Mps>{static_cast<double>(sourceValue) / mpsToKphFactor};
	}
};

template<>
struct ConversionTraits<tags::Kph, tags::Mps> {
	constexpr static Speed<tags::Kph> convert(Speed<tags::Mps> sourceValue) {
		return Speed<tags::Kph>{static_cast<double>(sourceValue) * mpsToKphFactor};
	}
};

template<>
struct ConversionTraits<tags::Mph, tags::Kph> {
	constexpr static Speed<tags::Mph> convert(Speed<tags::Kph> sourceValue) {
		return Speed<tags::Mph>{static_cast<double>(sourceValue) / mphToKphFactor};
	}
};

template<>
struct ConversionTraits<tags::Kph, tags::Mph> {
	constexpr static Speed<tags::Kph> convert(Speed<tags::Mph> sourceValue) {
		return Speed<tags::Kph>{static_cast<double>(sourceValue) * mphToKphFactor};
	}
};

template<>
struct ConversionTraits<tags::Mps, tags::Mph> {
	constexpr static Speed<tags::Mps> convert(Speed<tags::Mph> sourceValue) {
		return Speed<tags::Mps>{static_cast<double>(sourceValue) / mpsToMphFactor};
	}
};

template<>
struct ConversionTraits<tags::Mph, tags::Mps> {
	constexpr static Speed<tags::Mph> convert(Speed<tags::Mps> sourceValue) {
		return Speed<tags::Mph>{static_cast<double>(sourceValue) * mpsToMphFactor};
	}
};

template<typename Target, typename Source>
constexpr Speed<Target> speedCast(Speed<Source> const & source) {
	return Speed<Target>{ ConversionTraits<Target, Source>::convert(source) };
}



template <typename LeftTag, typename RightTag>
constexpr bool operator==(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return lhs == speedCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr bool operator<(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return lhs < speedCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr bool operator>(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return rhs < lhs;
}

template <typename LeftTag, typename RightTag>
constexpr bool operator<=(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return !(rhs < lhs);
}

template <typename LeftTag, typename RightTag>
constexpr bool operator>=(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return !(lhs < rhs);
}

}

#endif /* SPEED_H_ */
