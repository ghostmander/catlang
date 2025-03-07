/*! \file string_utils.h
    \brief Provides string utility functions.
*/
#ifndef CATLANG_STRING_UTILS_H
#define CATLANG_STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <utility>
#include <vector>
#include <sstream>


inline bool isAlnum(const std::string &s);         ///< Returns True if all characters in the string are alphanumeric
inline bool isAlpha(const std::string &s);         ///< Returns True if all characters in the string are in the alphabet
inline bool isDigit(const std::string &s);         ///< Returns True if all characters in the string are digits
inline bool isSpace(const std::string &s);         ///< Returns True if all characters in the string are whitespace
inline bool isHexadecimal(const std::string &s);   ///< Returns True if all characters in the string are hexadecimal digits
inline bool isPunctuation(const std::string &s);   ///< Returns True if all characters in the string are punctuation
inline bool isPrintable(const std::string &s);     ///< Returns True if all characters in the string are printable
inline bool isGraphical(const std::string &s);     ///< Returns True if all characters in the string are graphical
inline bool isEmpty (const std::string &s);        ///< Returns True if the string is empty

bool startsWith(const std::string &s, std::string &prefix);    ///< Return True if the string starts with the specified prefix, otherwise return False
bool endsWith(const std::string &s, std::string &suffix);      ///< Return True if the string ends with the specified suffix, otherwise return False

inline std::string lstrip(std::string s);   ///< Return a copy of the string with leading whitespace removed.
inline std::string rstrip(std::string s);   ///< Return a copy of the string with trailing whitespace removed.
inline std::string strip(std::string s);    ///< Return a copy of the string with leading and trailing whitespace removed.

template<typename Delim> std::string getWord(std::istream& ss, Delim d);
std::vector<std::string> splitHelper(const std::string& s, const std::string& delim = " ", bool enable_trim = true);
std::vector<std::string> split(const std::string& s, const std::string& delim = "", bool enable_trim = false);

inline std::string lstrip(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

inline std::string rstrip(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
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

inline std::vector<std::string> splitHelper(const std::string& s, const std::string& delim, const bool enable_trim) {
    std::stringstream ss(s);
    auto del = [&](char ch) { return std::any_of(delim.begin(), delim.end(), [ch](const char x) { return x == ch; }); };

    std::vector<std::string> words;
    if (enable_trim)
        for (std::string w; !(w = strip(getWord(ss, del))).empty(); ) words.push_back(w);
    else
        for (std::string w; !(w = getWord(ss, del)).empty(); ) words.push_back(w);

    return words;
}

/** Splits a string into individual parts based on the delimiter.
 * This works by creating a stringstream from the input string and then extracting words from the stringstream.
 * @param s The string to split
 * @param delim Delimiter to split the string. Can be 1 character or multiple characters.
 * @param enable_trim Enables/Disables output string trimming, so that the output is only relevant parts.
 * @return A vector containing individual parts of the string. (excluding the split characters)
 */
inline std::vector<std::string> split(const std::string& s, const std::string& delim, const bool enable_trim) {
    return splitHelper(s, delim.empty() ? " ": delim, enable_trim || delim.empty());
}

#endif