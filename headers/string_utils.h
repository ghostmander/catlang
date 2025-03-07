#ifndef PROGAMING_LANGUAGE_STRING_UTILS_H
#define PROGAMING_LANGUAGE_STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>
#include <cstddef>



inline void ltrim_inplace(std::string &s);  // Trims whitespace from start (in place)
inline std::string ltrim(std::string s);    // Trims whitespace from start (copy)
inline void rtrim_inplace(std::string &s);  // Trims whitespace from the end (in place)
inline std::string rtrim(std::string s);    // Trims whitespace from the end (copy)
inline void trim_inplace(std::string &s);   // Trims whitespace from both ends (in place)
inline std::string trim(std::string s);     // Trims whitespace from both ends (copy)
bool isSpace(const std::string &s);         // Checks if the string is all whitespace
bool isEmpty (const std::string &s);        // Checks if the string is empty
template<typename Delim> std::string getWord(std::istream& ss, Delim d);
std::vector<std::string> splitHelper(const std::string& s, const std::string& delim = " ", bool enable_trim = true);
std::vector<std::string> split(const std::string& s, const std::string& delim = "", bool enable_trim = false);

// trim_inplace from start (in place)
inline void ltrim_inplace(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim_inplace from end (in place)
inline void rtrim_inplace(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim_inplace from both ends (in place)
inline void trim_inplace(std::string &s) {
    rtrim_inplace(s);
    ltrim_inplace(s);
}

// trim_inplace from start (copying)
inline std::string ltrim(std::string s) {
    ltrim_inplace(s);
    return s;
}

// trim_inplace from end (copying)
inline std::string rtrim(std::string s) {
    rtrim_inplace(s);
    return s;
}

// trim_inplace from both ends (copying)
inline std::string trim(std::string s) {
    trim_inplace(s);
    return s;
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
        for (std::string w; !(w = trim(getWord(ss, del))).empty(); ) words.push_back(w);
    else
        for (std::string w; !(w = getWord(ss, del)).empty(); ) words.push_back(w);

    return words;
}

std::vector<std::string> split(const std::string& s, const std::string& delim, bool enable_trim) {
    return splitHelper(s, delim.empty() ? " ": delim, enable_trim || delim.empty());
}

#endif