#ifndef UTIL
#define UTIL

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>

// can't believe this didn't exist in STD prior to c++20
bool ends_with(std::string const& str, std::string const& what) {
    return what.size() <= str.size()
        && str.find(what, str.size() - what.size()) != str.npos;
}

bool starts_with(std::string const& str, std::string const& what) {
    return (str.rfind(what, 0) == 0);
}

#pragma region //https://stackoverflow.com/a/217605/11542917

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string s) {
    return ltrim(rtrim(s));
}

static inline std::vector<std::string> split(std::string str) {
    std::stringstream ss(str);
    std::vector<std::string> vec;

    std::string s;
    while (ss >> s) {
        vec.push_back(s);
    }

    return vec;
}

#pragma endregion

static inline void lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), 
            [](unsigned char ch){return std::tolower(ch);});
}


#define for_each(collection) for(auto item: collection)
#define for_ref_each(collection) for(auto& item: collection)
#endif