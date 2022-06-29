#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "MemoryOperationCounter.h"
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
struct Box {
	Box() = default;
//	Box(Box const & box)
//	  : items{box.items}{}
//	Box(Box && box)
//	  : items{std::move(box.items)} {}
	template <typename BoxType, typename = std::enable_if_t<std::is_same_v<Box, BoxType>>>
	explicit Box(BoxType && other)
	  : items(std::forward<BoxType>(other).items) {}
	explicit Box(size_t size)
	  : items(size) {}
	template <typename...Param>
	void emplace(Param &&... params) {
		items.emplace_back(std::forward<Param>(params)...);
	}
	T & front() {
		return items.front();
	}
private:
	std::vector<T> items{};
};



void testCopyBox() {
	MemoryOperationCounter const expected{1, 1, true};
	Box<MemoryOperationCounter> b{};
	b.emplace(MemoryOperationCounter{});
	auto copy = b;
	ASSERT_EQUAL(expected, copy.front());
}

void testCopyConstBox() {
	MemoryOperationCounter const expected{1, 1, true};
	Box<MemoryOperationCounter> b{};
	b.emplace(MemoryOperationCounter{});
	Box<MemoryOperationCounter> const & bRef = b;
	auto copy = bRef;
	ASSERT_EQUAL(expected, copy.front());
}

void testMoveBox() {
	MemoryOperationCounter const expected{1, 0, true};
	Box<MemoryOperationCounter> b{};
	b.emplace(MemoryOperationCounter{});
	auto copy = std::move(b);
	ASSERT_EQUAL(expected, copy.front());
}

void testSizeCtor() {
	MemoryOperationCounter const expected{0, 0, true};
	Box<MemoryOperationCounter> b{1};
	ASSERT_EQUAL(expected, b.front());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testCopyBox));
	s.push_back(CUTE(testMoveBox));
	s.push_back(CUTE(testCopyConstBox));
	s.push_back(CUTE(testSizeCtor));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
