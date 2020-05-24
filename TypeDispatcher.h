#pragma once

class Derived1;
class Derived2;
class Derived3;

class BaseDispatcher
{
public:
	virtual ~BaseDispatcher() = default;

	virtual void Cast(Derived1*) = 0;
	virtual void Cast(Derived2*) = 0;
	virtual void Cast(Derived3*) = 0;
};

class Dispatcher1 : public BaseDispatcher
{
	Derived1* m_Casted = nullptr;

public:
	using TCasted = Derived1;
	TCasted* GetCasted() { return m_Casted; }
	const TCasted* GetCasted() const { return m_Casted; }

	void Cast(Derived1* d) override { m_Casted = d; }
	void Cast(Derived2* d) override { m_Casted = nullptr; }
	void Cast(Derived3* d) override;
};

class Dispatcher2 : public BaseDispatcher
{
	Derived2* m_Casted = nullptr;

public:
	using TCasted = Derived2;
	TCasted* GetCasted() { return m_Casted; }
	const TCasted* GetCasted() const { return m_Casted; }

	void Cast(Derived1* d) override { m_Casted = nullptr; }
	void Cast(Derived2* d) override { m_Casted = d; }
	void Cast(Derived3* d) override;
};

class Dispatcher3 : public BaseDispatcher
{
	Derived3* m_Casted = nullptr;

public:
	using TCasted = Derived3;
	TCasted* GetCasted() { return m_Casted; }
	const TCasted* GetCasted() const { return m_Casted; }

	void Cast(Derived1*) override { m_Casted = nullptr; }
	void Cast(Derived2*) override { m_Casted = nullptr; }
	void Cast(Derived3* d) override { m_Casted = d; }
};
