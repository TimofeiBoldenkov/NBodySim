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

namespace 
{
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

namespace 
{

sf::FloatRect coveringRect(const Universe& universe)
{
    float minX, maxX, minY, maxY;

    for (int i = 0; i < universe.size(); i++) {
        sf::Vector2f position = Vector2Utils::convert<float>(universe[i].getPosition());
        float radius = universe[i].getShape().getRadius();
        if (i == 0) {
            minX = position.x - radius;
            maxX = position.x + radius;
            minY = position.y - radius;
            maxY = position.y + radius;
        } else {
            if (position.x - radius < minX) minX = position.x - radius;
            else if (position.x + radius > maxX) maxX = position.x + radius;
            if (position.y - radius < minY) minY = position.y - radius;
            else if (position.y + radius > maxY) maxY = position.y + radius;
        }
    }

    return sf::FloatRect({minX, minY}, {maxX - minX, maxY - minY});
}

}

sf::FloatRect utils::convenientView(const Universe& universe, const sf::VideoMode& videoMode)
{
    sf::FloatRect view = coveringRect(universe);

    if (view.height == 0 && view.width == 0)
        return sf::FloatRect(0, 0, videoMode.width, videoMode.height);
    else if (view.height / view.width > static_cast<float>(videoMode.height) / videoMode.width) {
        float newWidth = static_cast<float>(videoMode.width) / videoMode.height * view.height;
        return sf::FloatRect(view.left - (newWidth - view.width) / 2, view.top, newWidth, view.height);    
    } else {
        float newHeight = static_cast<float>(videoMode.height) / videoMode.width * view.width;
        return sf::FloatRect(view.left, view.top - (newHeight - view.height) / 2, view.width, newHeight);
    }
}
