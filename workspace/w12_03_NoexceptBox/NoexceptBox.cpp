#include <utility>



template<typename T>
class _box {
	T value;
public:
	explicit _box(T const &t) noexcept(noexcept(T(t))) :
			value(t) {
	}
	explicit _box(T && t) noexcept(noexcept(T(std::move_if_noexcept(t)))) :
			value(std::move_if_noexcept(t)) {
	}
	T & get() noexcept {
		return value;
	}
};

int main() {
	_box b{1};

}
