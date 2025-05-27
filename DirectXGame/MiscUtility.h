#pragma once

#include <string>//string,wstring

//string=>wstring
std::wstring ConvertString(const std::string& str);

//wstring=>string
std::string ConvertString(const std::wstring& str);