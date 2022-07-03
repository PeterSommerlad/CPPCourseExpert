#ifndef N_TIMES_H_
#define N_TIMES_H_



namespace times_literal {


constexpr auto operator"" _times(unsigned long long n) {
	return [n](auto f) {
		for (auto i = 0ull; i < n; i++) {
			f();
		}
	};
}

}


#endif /* N_TIMES_H_ */
