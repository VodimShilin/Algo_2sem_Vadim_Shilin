#include <iostream>
#include "unordered_map.h"
#include <string>

int main() {
    List<std::string> l;
    std::string x = "asb";
    l.push_back(std::move(x));
    std::cout << x;
    return 0;
}
