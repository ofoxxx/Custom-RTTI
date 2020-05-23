#include <chrono>
#include <iostream>
#include <memory>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;
};

class Derived1 : virtual public Base
{
public:
	void Specific1() const { cout << "Derived1::Specific1\n"; }
};

class Derived2 : virtual public Base
{
public:
	void Specific2() const { cout << "Derived2::Specific2\n"; }
};

class Derived3 : public Derived2, Derived1
{
public:
	void Specific3() const { cout << "Derived3::Specific3\n"; }
};

int main()
{
	std::unique_ptr<Base> base = std::make_unique<Derived1>();
	auto started = std::chrono::high_resolution_clock::now();
	Derived1* derived1 = dynamic_cast<Derived1*>(base.get());
	std::chrono::duration<double, std::milli> spent = std::chrono::high_resolution_clock::now() - started;
	if (derived1)
	{
		cout << "1: Base to Derived1 - OK (" << spent.count() << " ms)\n";
		derived1->Specific1();
	}

	Derived2* derived2 = dynamic_cast<Derived2*>(base.get());
	if (!derived2)
	{
		cout << "2: Derived1 to Derived2 - no\n";
	}

	base = std::make_unique<Derived3>();
	started = std::chrono::high_resolution_clock::now();
	Derived3* derived3 = dynamic_cast<Derived3*>(base.get());
	spent = std::chrono::high_resolution_clock::now() - started;
	if (derived3)
	{
		cout << "3: Base to Derived3 - OK (" << spent.count() << " ms)\n";
		derived3->Specific3();
	}

	started = std::chrono::high_resolution_clock::now();
	derived2 = dynamic_cast<Derived2*>(base.get());
	spent = std::chrono::high_resolution_clock::now() - started;
	if (derived2)
	{
		cout << "4: Base to Derived2 - OK (" << spent.count() << " ms)\n";
		derived2->Specific2();
	}

	return 0;
}
