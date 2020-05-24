#include "TypeDispatcher.h"
#include "Types.h"

void Derived1::Cast(BaseDispatcher& d)
{
	d.Cast(this);
}

void Derived2::Cast(BaseDispatcher& d)
{
	d.Cast(this);
}

void Derived3::Cast(BaseDispatcher& d)
{
	d.Cast(this);
}

void Dispatcher1::Cast(Derived3* d)
{
	m_Casted = d;
}

void Dispatcher2::Cast(Derived3* d)
{
	m_Casted = d;
}
