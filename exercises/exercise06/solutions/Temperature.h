#ifndef TEMPRATURE_H_
#define TEMPRATURE_H_

#include <cmath>
#include <stdexcept>


namespace units {



namespace tags {
struct Kelvin;
struct Celcius;
struct Fahrenheit;
}

template <typename Scale>
struct Temperature {
  constexpr explicit Temperature(double value) : value{value}{};
	constexpr explicit operator double() const {
		return value;
	}
	constexpr bool operator==(Temperature const & other) const {
		return std::abs(value - other.value) < epsilon;
	}
	constexpr auto operator<=>(Temperature const & other) const =default;
	constexpr Temperature & operator+=(Temperature const & other) {
		value += other.value;
		return *this;
	}
  friend
  constexpr Temperature  operator+(Temperature left,Temperature const & right)  {
    return left += right;
  }
	constexpr Temperature & operator-=(Temperature const & other) {
		return value += -other.value;
	}
	friend
  constexpr Temperature  operator-(Temperature left,Temperature const & right)  {
    return left -= right;
  }

	constexpr Temperature operator-() const {
		return Temperature{-value};
	}
	constexpr double operator/(Temperature const & other) const {
		return value / other.value;
	}
private:
	double value;
	constexpr static double epsilon = 0.0001;
};


template <typename Target, typename Source>
struct ConversionTraits {
	constexpr static Temperature<Target> convert(Temperature<Source> sourceValue) = delete;
};

template <typename Same>
struct ConversionTraits<Same, Same> {
	constexpr static auto convert(Temperature<Same> sourceValue) {
		return sourceValue;
	}
};

template <>
struct ConversionTraits<tags::Kelvin, tags::Celcius> {
	constexpr static auto convert(Temperature<tags::Celcius> sourceValue) {
		return Temperature<tags::Kelvin>{static_cast<double>(sourceValue) + 273.15};
	}
};

template <>
struct ConversionTraits<tags::Celcius, tags::Kelvin> {
	constexpr static auto convert(Temperature<tags::Kelvin> sourceValue) {
		return Temperature<tags::Celcius>{static_cast<double>(sourceValue) - 273.15};
	}
};

template <>
struct ConversionTraits<tags::Fahrenheit, tags::Celcius> {
	constexpr static auto convert(Temperature<tags::Celcius> sourceValue) {
		return Temperature<tags::Fahrenheit>{static_cast<double>(sourceValue) * 1.8 + 32.0};
	}
};

template <>
struct ConversionTraits<tags::Celcius, tags::Fahrenheit> {
	constexpr static auto convert(Temperature<tags::Fahrenheit> sourceValue) {
		return Temperature<tags::Celcius>{(static_cast<double>(sourceValue) - 32.0) * 5.0 / 9.0};
	}
};


template <>
struct ConversionTraits<tags::Kelvin, tags::Fahrenheit> {
	constexpr static auto convert(Temperature<tags::Fahrenheit> sourceValue) {
		return Temperature<tags::Kelvin>{(static_cast<double>(sourceValue) + 459.67) * 5.0 / 9.0};
	}
};

template <>
struct ConversionTraits<tags::Fahrenheit, tags::Kelvin> {
	constexpr static auto convert(Temperature<tags::Kelvin> sourceValue) {
		return Temperature<tags::Fahrenheit>{static_cast<double>(sourceValue) * 1.8 - 459.67};
	}
};


template <typename Target, typename Source>
constexpr Temperature<Target> temperatureCast(Temperature<Source> const & source) {
	return ConversionTraits<Target, Source>::convert(source);
}

template <typename LeftTag, typename RightTag>
constexpr bool operator==(Temperature<LeftTag> const & lhs, Temperature<RightTag> const & rhs) {
	return lhs == temperatureCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator<=>(Temperature<LeftTag> const & lhs, Temperature<RightTag> const & rhs) {
	return lhs <=> temperatureCast<LeftTag>(rhs);
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

inline constexpr auto operator"" _C(unsigned long long value) {
	return Temperature<tags::Celcius>{safeToDouble(value)};
}

inline constexpr auto operator"" _K(unsigned long long value) {
	return Temperature<tags::Kelvin>{safeToDouble(value)};
}

inline constexpr auto operator"" _F(unsigned long long value) {
	return Temperature<tags::Fahrenheit>{safeToDouble(value)};
}

inline constexpr auto operator"" _C(long double value) {
	return Temperature<tags::Celcius>{safeToDouble(value)};
}

inline constexpr auto operator"" _K(long double value) {
	return Temperature<tags::Kelvin>{safeToDouble(value)};
}

inline constexpr auto operator"" _F(long double value) {
	return Temperature<tags::Fahrenheit>{safeToDouble(value)};
}

}

}

#endif /* TEMPRATURE_H_ */
