#ifndef SPEED_H_
#define SPEED_H_

namespace velocity {

struct Speed {
	double toKph() const;
	double toMph() const;
	double toMps() const;
	static Speed fromKph(double value);
	static Speed fromMph(double value);
	static Speed fromMps(double value);
private:
	explicit Speed(double value);
	double const value;
};

bool isFasterThanWalking(Speed speed);

namespace literals {
  inline Speed operator"" _kph(long double value) {
	  return Speed::fromKph(value);
  }
  inline Speed operator"" _mph(long double value) {
	  return Speed::fromMph(value);
  }
  inline Speed operator"" _mps(long double value) {
	  return Speed::fromMps(value);
  }
}

}


#endif /* SPEED_H_ */
