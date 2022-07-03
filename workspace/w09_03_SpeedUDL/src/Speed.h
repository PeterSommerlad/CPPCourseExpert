#ifndef SPEED_H_
#define SPEED_H_

#include <cmath>
#include <stdexcept>

namespace velocity {

namespace tags {

struct Kph;
struct Mph;
struct Mps;

}

template <typename Scale>
struct Speed {
	constexpr explicit Speed(double value) :
			value { value } {
	}

	constexpr explicit operator double() const {
		return value;
	}
	constexpr Speed & operator+=(Speed const & other)& {
		value += other.value;
		return *this;
	}
  friend constexpr
  Speed operator+(Speed l, Speed const &r){
    return l += r;
  }
	constexpr Speed & operator-=(Speed const & other) & {
		return (*this) += -other;
	}
  friend constexpr
  Speed operator-(Speed l, Speed const &r){
    return l -= r;
  }

	constexpr Speed operator-() const {
		return Speed { -value };
	}

	constexpr bool operator==(Speed const & other) const {
		return std::abs(value - other.value) < epsilon;
	} // cannot rely on defaulted version

  constexpr auto operator<=>(Speed const & other) const = default;

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
constexpr auto operator<=>(Speed<LeftTag> const & lhs, Speed<RightTag> const & rhs) {
	return lhs <=> speedCast<LeftTag>(rhs);
}


namespace literals {

static constexpr inline double safeToDouble(long double value) {
	if (value > std::numeric_limits<double>::max() || value < std::numeric_limits<double>::min()) {
		throw std::invalid_argument{"Speed must be within double range"};
	}
	return static_cast<double>(value);
}

static constexpr inline double safeToDouble(unsigned long long value) {
	if (value > std::numeric_limits<double>::max()) {
		throw std::invalid_argument{"Speed must be within double range"};
	}
	return static_cast<double>(value);
}


constexpr inline Speed<tags::Kph> operator"" _kph(unsigned long long value) {
	return Speed<tags::Kph>{safeToDouble(value)};
}

constexpr inline Speed<tags::Kph> operator"" _kph(long double value) {
	return Speed<tags::Kph>{safeToDouble(value)};
}

constexpr inline Speed<tags::Mph> operator"" _mph(unsigned long long value) {
	return Speed<tags::Mph>{safeToDouble(value)};
}

constexpr inline Speed<tags::Mph> operator"" _mph(long double value) {
	return Speed<tags::Mph>{safeToDouble(value)};
}

constexpr inline Speed<tags::Mps> operator"" _mps(unsigned long long value) {
	return Speed<tags::Mps>{safeToDouble(value)};
}

constexpr inline Speed<tags::Mps> operator"" _mps(long double value) {
	return Speed<tags::Mps>{safeToDouble(value)};
}

}

}

#endif /* SPEED_H_ */
