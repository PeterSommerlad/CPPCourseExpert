#include <mutex>

void init() {}

std::once_flag flag;

void f() {
   std::call_once(flag, init);
}

// function static flag, function object
struct initializer {
   void operator()() {}
};

void g() {
   static std::once_flag flag2;
   std::call_once(flag2, initializer());
}

// object flag, member function
class information {
   std::once_flag verified;
   void verifier() {}
public:
    void verify() { std::call_once(verified, &information::verifier, *this); }
};

int main() {
   f();
   g();

   information x{};
   x.verify();
}
