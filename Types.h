#pragma once

class Base
{
public:
	virtual ~Base() = default;
};

class Derived1 : virtual public Base
{
public:
	int Specific1() const { return 1; }
};

class Derived2 : virtual public Base
{
public:
	int Specific2() const { return 2; }
};

class Derived3 : public Derived2, Derived1
{
public:
	int Specific3() const { return 3; }
};
