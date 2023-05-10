#pragma once

#include <fstream>
#include <stdarg.h> 

class Log
{
public:
	Log() {}
	~Log()
	{
		if (LOG.is_open())
		{
			LOG << std::endl;
		}
	}

	template <typename T>
	Log& operator<<(const T& t)
	{
		if (LOG.is_open())
		{
			LOG << t;
		}
		return *this;
	}
private:
	static std::ofstream LOG;
};

static std::ostream& operator<<(std::ostream& os, const wchar_t* wchr)
{
	std::wstring ws(wchr);
	std::string str;
	std::transform(ws.begin(), ws.end(), std::back_inserter(str), [](wchar_t c) {
		return (char)c;
	});

	return os << str;
}

static void logf(char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	auto size = vsnprintf(nullptr, 0, fmt, ap);
	std::string output(size + 1, '\0');
	vsprintf_s(&output[0], size + 1, fmt, ap);
	Log() << output.c_str();
	va_end(ap);
}

static void logf(wchar_t * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef _MSC_VER
#pragma warning(suppress: 4996)
#endif
	auto size = _vsnwprintf(nullptr, 0, fmt, ap);
	std::wstring output(size + 1, '\0');
	vswprintf_s(&output[0], size + 1, fmt, ap);
	Log() << output.c_str();
	va_end(ap);
}
