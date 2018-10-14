#pragma once

#ifdef _WIN32
#ifdef COMMON_API_EXPORT
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif // COMMON_DYNAMIC_LIB
#else
#define COMMON_API
#endif // _WIN32

class COMMON_API AsyncTask
{
public:
	AsyncTask();
	virtual ~AsyncTask();
	virtual void wait() = 0;
};

