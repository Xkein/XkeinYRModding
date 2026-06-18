#pragma once
#include <vector>

template <typename T>
void std_vector_add_unique(std::vector<T>& vec, const T& value) {
    if (std::find(vec.begin(), vec.end(), value) == vec.end()) {
        vec.push_back(value);
    }
}