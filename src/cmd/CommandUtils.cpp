#include <iterator>
#include <string>
#include <sstream>

int countWords(std::istream& input) {
    return std::distance(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>());
}

std::string intToString(int num) {
		std::ostringstream oss;
    oss << num;
    return oss.str();
}
