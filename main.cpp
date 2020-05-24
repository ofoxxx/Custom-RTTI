#include <iostream>
#include <memory>
#include "TypeMixin/Types.h"
#include "TypeVisitor/TypeDispatcher.h"
#include "TypeVisitor/Types.h"
#include "UTest.h"

int main()
{
	using namespace std;
	{
		using namespace TypeMixin;

		unique_ptr<Base> base = make_unique<Derived1>();

		UTestCase test1("TypeMixin::Base(Derived1) to Derived1 casted", [&base] {
			Derived1* derived1 = Type::Cast<Derived1>(base.get());
			return derived1 && derived1->Specific1() == 1;
		});
		test1();
		cout << test1;

		UTestCase test2("TypeMixin::Base(Derived1) to Derived2 NOT casted", [&base] {
			Derived2* derived2 = Type::Cast<Derived2>(base.get());
			return !derived2;
		});
		test2();
		cout << test2;

		base = make_unique<Derived3>();

		UTestCase test3("TypeMixin::Base(Derived3) to Derived3 casted", [&base] {
			Derived3* derived3 = Type::Cast<Derived3>(base.get());
			return derived3 && derived3->Specific3() == 3;
		});
		test3();
		cout << test3;

		UTestCase test4("TypeMixin::Base(Derived3) to Derived1 casted", [&base] {
			Derived1* derived1 = Type::Cast<Derived1>(base.get());
			return derived1 && derived1->Specific1() == 1;
		});
		test4();
		cout << test4;

		UTestCase test5("TypeMixin::Base(Derived3) to Derived2 casted", [&base] {
			Derived2* derived2 = Type::Cast<Derived2>(base.get());
			return derived2 && derived2->Specific2() == 2;
		});
		test5();
		cout << test5;

		shared_ptr<Base> shared_base = move(base);

		UTestCase test_pc("shared_ptr<TypeMixin::Base(Derived3)> to Derived3 casted", [&shared_base] {
			auto derived3 = Type::Pointer_Cast<Derived3>(shared_base);
			return derived3 && derived3->Specific3() == 3;
		});
		test_pc();
		cout << test_pc;
	}
	{
		using namespace TypeVisitor;

		unique_ptr<Base> base = make_unique<Derived1>();

		UTestCase test1("TypeVisitor::Base(Derived1) to Derived1 casted", [&base] {
			Dispatcher1 dispatcher1;
			base->Cast(dispatcher1);
			Derived1* derived1 = dispatcher1.GetCasted();
			return derived1 && derived1->Specific1() == 1;
		});
		test1();
		cout << test1;

		UTestCase test2("TypeVisitor::Base(Derived1) to Derived2 NOT casted", [&base] {
			Dispatcher2 dispatcher2;
			base->Cast(dispatcher2);
			Derived2* derived2 = dispatcher2.GetCasted();
			return !derived2;
		});
		test2();
		cout << test2;

		base = make_unique<Derived3>();

		UTestCase test3("TypeVisitor::Base(Derived3) to Derived3 casted", [&base] {
			Dispatcher3 dispatcher3;
			base->Cast(dispatcher3);
			Derived3* derived3 = dispatcher3.GetCasted();
			return derived3 && derived3->Specific3() == 3;
		});
		test3();
		cout << test3;

		UTestCase test4("TypeVisitor::Base(Derived3) to Derived1 casted", [&base] {
			Dispatcher1 dispatcher1;
			base->Cast(dispatcher1);
			Derived1* derived1 = dispatcher1.GetCasted();
			return derived1 && derived1->Specific1() == 1;
		});
		test4();
		cout << test4;

		UTestCase test5("TypeVisitor::Base(Derived3) to Derived2 casted", [&base] {
			Dispatcher2 dispatcher2;
			base->Cast(dispatcher2);
			Derived2* derived2 = dispatcher2.GetCasted();
			return derived2 && derived2->Specific2() == 2;
		});
		test5();
		cout << test5;

		UTestCase test_dc("dynamic_cast<Derived3*>(Base*) measurement", [&base] {
			Derived3* derived3 = dynamic_cast<Derived3*>(base.get());
			return derived3 && derived3->Specific3() == 3;
		});
		test_dc();
		cout << test_dc;
	}
	return 0;
}
