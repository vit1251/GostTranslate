
#include <algorithm>
#include <iostream>

#include "GostTranslit.hpp"

GostTranslit::GostTranslit() {
//    std::cout << "Initialize" << std::endl;
    // Добавим пунктуацию
    for (const auto& mark: punctuations) {
//        std::cout << "p = '" << mark << "'" << std::endl;
        cyrillic2latin[mark] = mark;
        latin2cyrillic[mark] = mark;
    }
}

static bool startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

std::string GostTranslit::to_latin(const std::string& input) {
    std::string in = input;
    std::string out;
    //
    std::vector<std::pair<std::string, std::string>> elements;
    for (const auto& pair : cyrillic2latin) {
        elements.push_back(pair);
    }
    std::sort(elements.begin(), elements.end(), [](const auto& a, const auto& b) {
        return a.first.length() > b.first.length();
    });
    //
    while (!in.empty()) {
        bool map = false;
        for (const auto& pair : elements) {
            const std::string& key = pair.first;
            const std::string& value = pair.second;

            std::string prefix = key;
            if (startsWith(in, prefix)) {
                out += value;
                size_t prefixSize = prefix.length();
//                std::cout << "key = " << key << " prefix = '" << prefix << "' prefixSize = " << prefixSize << std::endl;
                in.erase(0, prefixSize);
                map = true;
                break;
            }
        }
        if (!map) {
            // не удалось отобразить...
            break;
        }
    }
    return out;
}

std::string GostTranslit::to_cyrillic(const std::string& input) {
    std::string in = input;
    std::string out;
    //
    std::vector<std::pair<std::string, std::string>> elements;
    for (const auto& pair : latin2cyrillic) {
        elements.push_back(pair);
    }
    std::sort(elements.begin(), elements.end(), [](const auto& a, const auto& b) {
        return a.first.length() > b.first.length();
    });
    //
    while (!in.empty()) {
        bool map = false;
        for (const auto& pair : elements) {
            const std::string& key = pair.first;
            const std::string& value = pair.second;
            std::string prefix = key;
            if (startsWith(in, prefix)) {
                out += value;
                size_t prefixSize = prefix.length();
//                std::cout << "key = " << key << " prefix = '" << prefix << "' prefixSize = " << prefixSize << std::endl;
                in.erase(0, prefixSize);
                map = true;
                break;
            }
        }
        if (!map) {
            // не удалось отобразить...
            break;
        }
    }
    return out;
}
