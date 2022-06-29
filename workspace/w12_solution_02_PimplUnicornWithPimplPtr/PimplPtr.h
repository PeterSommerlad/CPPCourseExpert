#ifndef PIMPLPTR_H_
#define PIMPLPTR_H_

#include <memory>
#include <utility>


template <typename T>
using PimplPtr = std::unique_ptr<T, void(*)(T *)>;

template <typename Target, typename...Args>
PimplPtr<Target> makeUniquePimpl(Args&&...args) {
	return {new Target{std::forward<Args>(args)...}, std::destroy_at<Target>};
}


#endif /* PIMPLPTR_H_ */
