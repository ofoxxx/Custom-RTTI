#pragma once

#include "TypeMixin.h"

namespace TypeMixin
{
	class Base : public CastMixin<Base>
	{
	public:
		virtual ~Base() = default;
	};

	class Derived1 : public CastMixin<Derived1, Base>
	{
	public:
		int Specific1() const { return 1; }
	};

	class Derived2 : public CastMixin<Derived2, Base>
	{
	public:
		int Specific2() const { return 2; }
	};

	class Derived3 : public CastMixin<Derived3, Derived2, Derived1>
	{
	public:
		int Specific3() const { return 3; }
	};
}
