#pragma once
#include <string>

namespace Utils
{
    template<typename T>
    std::string className(T ins) {
        return typeid(ins).name();
    }

    template<typename T>
    std::string className() {
        return typeid(T).name();
    }
} // namespace Utils
