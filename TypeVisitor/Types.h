#pragma once

namespace TypeVisitor
{
	class BaseDispatcher;

	class Base
	{
	public:
		virtual ~Base() = default;

		virtual void Cast(BaseDispatcher&) = 0;
	};

	class Derived1 : virtual public Base
	{
	public:
		void Cast(BaseDispatcher&) override;

		int Specific1() const { return 1; }
	};

	class Derived2 : virtual public Base
	{
	public:
		void Cast(BaseDispatcher&) override;

		int Specific2() const { return 2; }
	};

	class Derived3 : public Derived1, public Derived2
	{
	public:
		void Cast(BaseDispatcher&) override;

		int Specific3() const { return 3; }
	};
}
