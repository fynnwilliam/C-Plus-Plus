/**
 * @file
 * @brief          String pattern search - brute force
 */
#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif
#include <vector>

namespace string_search {
/**
 * Find a pattern in a string by comparing the pattern to every substring.
 * @param text     Any string that might contain the pattern.
 * @param pattern  String that we are searching for.
 * @return         i - Index where the pattern starts in the text
 * @return         -1 if the pattern was not found.
 */
int brute_force(const std::string &text, const std::string &pattern) {
    size_t pattern_length = pattern.length();
    size_t text_length    = text.length();

    if (pattern_length <= text_length) {
        for (size_t i = 0; i < text_length - pattern_length + 1; ++i) {
            if (text.substr(i, pattern_length) == pattern) return i;
        }
    }
    return -1;
}
}  // namespace string_search

using string_search::brute_force;

/** set of test cases */
const std::vector<std::vector<std::string>> test_set = {
    // {text, pattern, expected output}
    {"a", "aa", "-1"},  {"a", "a", "0"},    {"ba", "b", "0"},
    {"bba", "bb", "0"}, {"bbca", "c", "2"}, {"ab", "b", "1"}};

/** Main function */
int main() {
    for (const auto &i : test_set) {
        int output = brute_force(i[0], i[1]);

        if (std::to_string(output) == i[2]) {
            std::cout << "success\n";
        } else {
            std::cout << "failure\n";
        }
    }
    return 0;
}
