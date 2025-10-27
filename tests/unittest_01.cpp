
#include <string>
#include <iostream>
#include <assert.h>
#include <GostTranslit.hpp>

GostTranslit gt;

void Test1() {
    std::cout << "--- Test 1 ---" << std::endl;
    
    std::string input = "Под этим солнцем и небом мы тепло приветствуем тебя.";
    std::cout << "I = '" << input << "'" << std::endl;
    
    std::string output = gt.to_latin(input);
    std::cout << "O = '" << output << "'" << std::endl;

    std::string verify = "Pod e`tim solncem i nebom my` teplo privetstvuem tebya.";
    std::cout << "V = '" << verify << "'" << std::endl;
    assert(output == verify);
}

void Test2() {
    std::cout << "--- Test 2 ---" << std::endl;

    std::string input = "Pod e`tim solncem i nebom my` teplo privetstvuem tebya.";
    std::cout << "I = '" << input << "'" << std::endl;

    std::string output = gt.to_cyrillic(input);
    std::cout << "O = '" << output << "'" << std::endl;

    std::string verify = "Под этим солнцем и небом мы тепло приветствуем тебя.";
    std::cout << "V = '" << verify << "'" << std::endl;
    assert(output == verify);

}

int main() {
    Test1();
    Test2();
    return 0;
}
