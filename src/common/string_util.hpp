#pragma once
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start
template <class T>
static inline T& ltrim(T &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
template <class T>
static inline T& rtrim(T &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
template <class T>
static inline T & trim(T &s) {
	return ltrim(rtrim(s));
}

template <class T>
T& toUpper(T& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

template <class T>
T& toLower(T& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}