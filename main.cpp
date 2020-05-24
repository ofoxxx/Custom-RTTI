#include <iostream>
#include <memory>
#include "TypeVisitor/TypeDispatcher.h"
#include "TypeVisitor/Types.h"
#include "UTest.h"

int main()
{
	using namespace TypeVisitor;

	std::unique_ptr<Base> base = std::make_unique<Derived1>();

	UTestCase test_v1("Visitor: Base(Derived1) to Derived1 casted", [&base] {
		Dispatcher1 dispatcher1;
		base->Cast(dispatcher1);
		Derived1* derived1 = dispatcher1.GetCasted();
		return derived1 && derived1->Specific1() == 1;
	});
	test_v1();
	std::cout << test_v1;

	UTestCase test_v2("Visitor: Base(Derived1) to Derived2 NOT casted", [&base] {
		Dispatcher2 dispatcher2;
		base->Cast(dispatcher2);
		Derived2* derived2 = dispatcher2.GetCasted();
		return !derived2;
	});
	test_v2();
	std::cout << test_v2;

	base = std::make_unique<Derived3>();

	UTestCase test_v3("Visitor: Base(Derived3) to Derived3 casted", [&base] {
		Dispatcher3 dispatcher3;
		base->Cast(dispatcher3);
		Derived3* derived3 = dispatcher3.GetCasted();
		return derived3 && derived3->Specific3() == 3;
	});
	test_v3();
	std::cout << test_v3;

	UTestCase test_v4("Visitor: Base(Derived3) to Derived1 casted", [&base] {
		Dispatcher1 dispatcher1;
		base->Cast(dispatcher1);
		Derived1* derived1 = dispatcher1.GetCasted();
		return derived1 && derived1->Specific1() == 1;
	});
	test_v4();
	std::cout << test_v4;

	UTestCase test_v5("Visitor: Base(Derived3) to Derived2 casted", [&base] {
		Dispatcher2 dispatcher2;
		base->Cast(dispatcher2);
		Derived2* derived2 = dispatcher2.GetCasted();
		return derived2 && derived2->Specific2() == 2;
	});
	test_v5();
	std::cout << test_v5;

	UTestCase test_dc("dynamic_cast<Derived3*>(Base*) measurement", [&base] {
		Derived3* derived3 = dynamic_cast<Derived3*>(base.get());
		return derived3 && derived3->Specific3() == 3;
	});
	test_dc();
	std::cout << test_dc;

	return 0;
}
