
#include <algorithm>
#include <iostream>

#include "GostTranslit.hpp"

GostTranslit::GostTranslit() {
    // Добавляем знаки пунктуации
    for (const auto& mark: punctuations) {
        cyrillic2latin[mark] = mark;
        latin2cyrillic[mark] = mark;
    }
    // Подготавливаем кеш преобразования
    for (const auto& pair : latin2cyrillic) {
        m_cache_latin2cyrillic.push_back(pair);
    }
    std::sort(m_cache_latin2cyrillic.begin(), m_cache_latin2cyrillic.end(), [](const auto& a, const auto& b) {
        return a.first.length() > b.first.length();
    });
    // Подготавливаем кеш преобразования
    for (const auto& pair : cyrillic2latin) {
        m_cache_cyrillic2latin.push_back(pair);
    }
    std::sort(m_cache_cyrillic2latin.begin(), m_cache_cyrillic2latin.end(), [](const auto& a, const auto& b) {
        return a.first.length() > b.first.length();
    });
}

static bool startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

std::string GostTranslit::to_latin(const std::string& input) {
    std::string in = input;
    std::string out;
    //
    while (!in.empty()) {
        bool map = false;
        for (const auto& pair : m_cache_cyrillic2latin) {
            if (startsWith(in, pair.first)) {
                out += pair.second;
                size_t prefixSize = pair.first.length();
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
    while (!in.empty()) {
        bool map = false;
        for (const auto& pair : m_cache_latin2cyrillic) {
            if (startsWith(in, pair.first)) {
                out += pair.second;
                size_t prefixSize = pair.first.length();
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
