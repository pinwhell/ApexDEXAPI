#pragma once

#include <string>

std::string Time2Str(time_t time);
unsigned long long GetCurrentEpochMillis();
std::string HMACSHA256(const std::string& msg, const std::string& secret);
std::string B64Encode(const void* input, int length);
std::string B64Decode(const void* input, int length);

inline std::string B64Encode(const std::string& str)
{
	return B64Encode(str.c_str(), str.size());
}

inline std::string B64Decode(const std::string& str)
{
	return B64Decode(str.c_str(), str.size());
}

