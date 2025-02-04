/**
 * @file
 * @brief Horspool's algorithm that finds if a string contains a substring
 * (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)
 * @author [Harry Kontakis](https://github.com/ckontakis)
 */

#include <cassert>
#include <iostream>
#include <unordered_map>

/**
 * @namespace strings
 * @brief Algorithms with strings
 */
namespace strings {
/**
 * @namespace horspool
 * @brief Functions for
 * [Horspool's](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)
 * algorithm
 */
namespace horspool {
/**
 * A function that finds the shift table of the given prototype string that we
 * need in Horpool's algorithm.
 * @param prototype is the substring that we use to find shift table
 * @return Shift Table of Horspool's algorithm
 */
std::unordered_map<char, size_t> findShiftTable(const std::string &prototype) {
    std::unordered_map<char, size_t>
        shiftTable;  // A HashMap for shift table that has characters for keys
                     // and unsigned integers for values

    for (size_t i = 0, last_index = prototype.size() - 1; i < last_index + 1;
         ++i) {  // Checking all characters of prototype string
        if (shiftTable.count(prototype[i])) {
            if (i != last_index) {
                shiftTable[prototype[i]] = last_index - i;
            }
        } else {
            // Insert the current character as key. Insert the size of prototype
            // string - i - 1 as value if 'i' is the index of the last
            // character, size of prototype string, otherwise.
            shiftTable.emplace(prototype[i], i != last_index ? last_index - i
                                                             : last_index + 1);
        }
    }
    return shiftTable;
}

/**
 * A function that implements Horspool's algorithm.
 * @param text is the string that we are searching if there is a substring
 * @param prototype is the substring that we are searching in text
 * @returns true if text string contains prototype string
 * @returns false if text string does not contain prototype string
 */
bool horspool(const std::string &text, const std::string &prototype) {
    auto shiftTable = findShiftTable(prototype);  // Initialise shift table

    auto prototype_size = prototype.size();
    auto i = prototype_size - 1;  // Index that we shift in text to find the substring
    while (i < text.size()) {
        // Return 'true', if the returned substring is equal to prototype.
        if (text.substr(i - prototype_size + 1, prototype_size) == prototype)
            return true;

        // shift index as many steps as value at shiftTable[text[i]], if
        // character at text[i] is found in shiftTable, shift as many steps as
        // size of prototype otherwise.
        i += shiftTable.count(text[i]) ? shiftTable[text[i]] : prototype_size;
    }
    return false;
}
}  // namespace horspool
}  // namespace strings

/**
 * @brief Function with test cases for Horspool's algorithm
 * @returns void
 */
static void test() {
    assert(strings::horspool::horspool("Hello World", "World") == true);
    assert(strings::horspool::horspool("Hello World", " World") == true);
    assert(strings::horspool::horspool("Hello World", "ello") == true);
    assert(strings::horspool::horspool("Hello World", "rld") == true);
    assert(strings::horspool::horspool("Hello", "Helo") == false);
    assert(strings::horspool::horspool("c++_algorithms", "c++_algorithms") == true);
    assert(strings::horspool::horspool("c++_algorithms", "c++_") == true);
    assert(strings::horspool::horspool("Hello", "Hello World") == false);
    assert(strings::horspool::horspool("c++_algorithms", "") == false);
    assert(strings::horspool::horspool("c++", "c") == true);
    assert(strings::horspool::horspool("3458934793", "4793") == true);
    assert(strings::horspool::horspool("3458934793", "123") == false);
}

/**
 * @brief Main Function that calls test function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
