#ifndef PROGAMING_LANGUAGE_STRING_UTILS_H
#define PROGAMING_LANGUAGE_STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <utility>
#include <vector>
#include <sstream>
#include <cstddef>

bool isAlnum(const std::string &s);         // Returns True if all characters in the string are alphanumeric
bool isAlpha(const std::string &s);         // Returns True if all characters in the string are in the alphabet
bool isDigit(const std::string &s);         // Returns True if all characters in the string are digits
bool isSpace(const std::string &s);         // Returns True if all characters in the string are whitespace
bool isHexadecimal(const std::string &s);   // Returns True if all characters in the string are hexadecimal digits
bool isPunctuation(const std::string &s);   // Returns True if all characters in the string are punctuation
bool isPrintable(const std::string &s);     // Returns True if all characters in the string are printable
bool isGraphical(const std::string &s);     // Returns True if all characters in the string are graphical
bool isEmpty (const std::string &s);        // Returns True if the string is empty

bool startsWith(const std::string &s, std::string &prefix);    // Return True if the string starts with the specified prefix, otherwise return False
bool endsWith(const std::string &s, std::string &suffix);      // Return True if the string ends with the specified suffix, otherwise return False

inline std::string lstrip(std::string s);   // Return a copy of the string with leading whitespace removed.
inline std::string rstrip(std::string s);   // Return a copy of the string with trailing whitespace removed.
inline std::string strip(std::string s);    // Return a copy of the string with leading and trailing whitespace removed.

template<typename Delim> std::string getWord(std::istream& ss, Delim d);
std::vector<std::string> splitHelper(const std::string& s, const std::string& delim = " ", bool enable_trim = true);
std::vector<std::string> split(const std::string& s, const std::string& delim = "", bool enable_trim = false);

inline std::string lstrip(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

inline std::string rstrip(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

inline std::string strip(std::string s) {
    return rstrip(lstrip(std::move(s)));
}

bool isDigit(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isdigit);
}
bool isAlpha(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isalpha);
}
bool isHexadecimal(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isxdigit);
}
bool isPunctuation(const std::string &s) {
    return std::all_of(s.begin(), s.end(), ispunct);
}
bool isAlnum(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isalnum);
}
bool isPrintable(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isprint);
}
bool isGraphical(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isgraph);
}
bool isSpace(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isspace);
}
bool isEmpty (const std::string &s) {
    return s.empty();
}

template<typename Delim> std::string getWord(std::istream& ss, Delim d) {
    std::string word;
    for (char ch; ss.get(ch); )    // skip delimiters
        if (!d(ch)) {
            word.push_back(ch);
            break;
        }
    for (char ch; ss.get(ch); )    // collect word
        if (!d(ch))
            word.push_back(ch);
        else
            break;
    return word;
}

std::vector<std::string> splitHelper(const std::string& s, const std::string& delim, bool enable_trim) {
    std::stringstream ss(s);
    auto del = [&](char ch) { return std::any_of(delim.begin(), delim.end(), [ch](char x) { return x == ch; }); };

    std::vector<std::string> words;
    if (enable_trim)
        for (std::string w; !(w = strip(getWord(ss, del))).empty(); ) words.push_back(w);
    else
        for (std::string w; !(w = getWord(ss, del)).empty(); ) words.push_back(w);

    return words;
}

std::vector<std::string> split(const std::string& s, const std::string& delim, bool enable_trim) {
    return splitHelper(s, delim.empty() ? " ": delim, enable_trim || delim.empty());
}

#endif