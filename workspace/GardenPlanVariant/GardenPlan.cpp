#include "Shapes.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <vector>

using namespace std;
using namespace Gardening;

using GardenPlan = vector<Shape>;

namespace Gardening {
ostream & operator<<(ostream & out, Shape const & shape) {
	Print(out,shape);
	return out;
}
}

void printPlan(GardenPlan const & plan, ostream & out){
	copy(plan.begin(), plan.end(), ostream_iterator<Shape>{out, "\n"});
}

template<typename F>
auto mapReduce(GardenPlan const & plan, F const & function) {
	return accumulate(plan.begin(), plan.end(), 0, [&function](auto lhs, auto rhs) {
		return lhs + function(rhs);
	});
}

int main() {
	GardenPlan plan {
		Triangle(3, 6, 6.70820393),
		Triangle(3, 4, 4),
		Triangle(3, 4, 4),
		Diamond(4, 60),
		Square(3),
		Square(3),
		Rectangle(4, 9),
		Circle(4),
		Ellipse(5, 3)
	};
	printPlan(plan, cout);

	cout << "pegs needed: " << mapReduce(plan, Gardening::Pegs) << '\n';

	cout << "seeds needed: " << mapReduce(plan, Gardening::Seeds) <<" kg\n";

	cout << "rope needed: " << mapReduce(plan, Gardening::Ropes) << " m\n";
}


