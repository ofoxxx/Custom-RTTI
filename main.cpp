#include <iostream>
#include <memory>
#include "Types.h"
#include "UTest.h"

int main()
{
	std::unique_ptr<Base> base = std::make_unique<Derived1>();
	UTestCase test1("dynamic_cast<Derived1*>(Base*) measurement", [&base] {
		Derived1* derived1 = dynamic_cast<Derived1*>(base.get());
		return derived1 && derived1->Specific1() == 1;
	});
	test1();
	std::cout << test1;

	UTestCase test2("dynamic_cast<Derived2*>(Base*) not casted", [&base] {
		Derived2* derived2 = dynamic_cast<Derived2*>(base.get());
		return !derived2;
	});
	test2();
	std::cout << test2;

	base = std::make_unique<Derived3>();
	UTestCase test3("dynamic_cast<Derived3*>(Base*) measurement", [&base] {
		Derived3* derived3 = dynamic_cast<Derived3*>(base.get());
		return derived3 && derived3->Specific3() == 3;
	});
	test3();
	std::cout << test3;

	UTestCase test4("dynamic_cast<Derived2*>(Base* d3) measurement", [&base] {
		Derived2* derived2 = dynamic_cast<Derived2*>(base.get());
		return derived2 && derived2->Specific2() == 2;
	});
	test4();
	std::cout << test4;

	return 0;
}
