#include "sha2_256.h"
#include "support.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>

template<std::size_t N>
constexpr auto hash_password(char const (&pwd)[N]) {
	using HashByte = Chocobo1::SHA2_256::Byte;
	constexpr auto byteLength = N - 1;

	auto bytes = std::array<HashByte, byteLength> { };
	hsr::transform(&pwd[0], &pwd[byteLength], bytes.data(), hsr::byte_cast);

	return Chocobo1::SHA2_256 { }.addData(bytes).finalize().toArray();
}

int main() {
	constexpr auto hashed_password = hash_password("MySuperSecurePassword");
	constexpr auto hexified_hash = hsr::hexify(hashed_password);

	std::ostream_iterator<char> output { std::cout };
	std::copy(std::cbegin(hexified_hash), std::cend(hexified_hash), output);
	std::cout << '\n';
}
