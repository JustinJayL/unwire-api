#include "util.hpp"

using string = std::string;
using stringstream = std::stringstream;
using std::map;

string hexlify(string input, bool prefix, bool caps) {
    //std::cout << "hexlify: The length of the string is " << input.length() << std::endl;
    string output;
    string chars [16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    if (prefix) {
        output = "0x";
    }
    else {
        output = "";
    }
    if (caps) {
        chars[10] = 'A';
        chars[11] = 'B';
        chars[12] = 'C';
        chars[13] = 'D';
        chars[14] = 'E';
        chars[15] = 'F';
    }
    else {
        chars[10] = 'a';
        chars[11] = 'b';
        chars[12] = 'c';
        chars[13] = 'd';
        chars[14] = 'e';
        chars[15] = 'f';
    }

    string::iterator it;
    for (it = input.begin(); it != input.end(); it++) {
        output += chars[((int)(unsigned char)it[0]) / 16] + chars[((int)(unsigned char)it[0]) % 16];
    }
    return output;
}

string unhexlify(string input) {
    string output = "";
    map<string, int> charMap{{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3},
        {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"a", 10},
        {"b", 11}, {"c", 12}, {"d", 13}, {"e", 14}, {"f", 15}, {"A", 10},
        {"B", 11}, {"C", 12}, {"D", 13}, {"E", 14}, {"F", 15}};

    if (string(1, input[1]) == "x" || string(1, input[1]) == "X") {
        input = input.substr(2);
    }
    string::iterator it;
    int cur = 0;
    for (it = input.begin(); it != input.end(); it+=2) {
        output += (charMap[std::string(1, it[0])] * 16) + charMap[std::string(1, it[1])];
    }
    return output;
}