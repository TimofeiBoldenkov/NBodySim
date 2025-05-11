#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "utils.hpp"

using std::string;
using std::vector;
using std::isspace;
using std::find_if;

namespace {
    bool space(char c)
    {
        return isspace(c);
    }

    bool not_space(char c)
    {
        return !isspace(c);
    }
}

vector<string> utils::split(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);

        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }

    return ret;
}

bool utils::isSpace(string str)
{
    return std::find_if(str.begin(), str.end(), not_space) == str.end();
}

sf::FloatRect utils::viewForVideoMode(const sf::FloatRect& view, const sf::VideoMode& videoMode)
{
    if (view.height == 0 && view.width == 0)
        return sf::FloatRect(0, 0, videoMode.width, videoMode.height);

    if (view.height / view.width > static_cast<float>(videoMode.height) / videoMode.width) {
        float newWidth = static_cast<float>(videoMode.width) / videoMode.height * view.height;
        return sf::FloatRect(view.left - (newWidth - view.width) / 2, view.top, newWidth, view.height);
        
    } else {
        float newHeight = static_cast<float>(videoMode.height) / videoMode.width * view.width;
        return sf::FloatRect(view.left, view.top - (newHeight - view.height) / 2, view.width, newHeight);
    }
}
