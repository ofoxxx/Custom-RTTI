#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <string>

using UDuration_ms = std::chrono::duration<double, std::milli>;

class UTestCase
{
public:
	UTestCase(const std::string& name, const std::function<bool()>& f) : m_name(name), m_case{f} {}

	bool operator()()
	{
		auto started = std::chrono::high_resolution_clock::now();
		m_result = m_case();
		m_duration = std::chrono::high_resolution_clock::now() - started;
		return m_result;
	}
	inline operator bool() const { return m_result; }

	inline const std::string& name() const { return m_name; }
	inline const UDuration_ms& duration() const { return m_duration; }
	inline bool done() const { return m_duration != UDuration_ms::zero(); }
	inline bool successful() const { return m_result; }

private:
	std::string m_name;
	std::function<bool()> m_case;
	bool m_result { false };
	UDuration_ms m_duration { UDuration_ms::zero() };
};

std::ostream& operator<<(std::ostream& os, const UTestCase& tc)
{
	if (!tc.name().empty())
	{
		os << tc.name() << ": ";
	}
	if (tc.done())
	{
		if (tc.successful())
		{
			os << "OK (" << tc.duration().count() << " ms)\n";
		}
		else
		{
			os << "failed\n";
		}
	}
	else
	{
		os << "not performed\n";
	}
	return os;
}
