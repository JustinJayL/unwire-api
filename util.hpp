
#ifndef UTIL_HPP_
#define UTIL_HPP_
#include <string>
#include <iostream>
#include <map>

using string = std::string;

string hexlify(string input, bool prefix = false, bool caps = false);
string unhexlify(string input);

#endif

