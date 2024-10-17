#include <iterator>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

int countWords(std::istream& input) {
		int i = 0;
		std::string ignore;
		
    i = std::distance(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>());
		input.clear();
		input.seekg(0);
		return i;
}

std::string intToString(int num) {
		std::ostringstream oss;
    oss << num;
    return oss.str();
}

bool containsInvalidChars(const std::string& str) {
    std::vector<char> invalidChars;
    invalidChars.push_back(' ');
    invalidChars.push_back('@');
    invalidChars.push_back('!');
    invalidChars.push_back('.');
    invalidChars.push_back('+');
    invalidChars.push_back('%');
    invalidChars.push_back('#');
    invalidChars.push_back('&');
    invalidChars.push_back(':');
    invalidChars.push_back('?');

    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        for (std::vector<char>::const_iterator invalidIt = invalidChars.begin(); invalidIt != invalidChars.end(); ++invalidIt) {
            if (*it == *invalidIt) {
                return true;
            }
        }
    }
    return false;
}
