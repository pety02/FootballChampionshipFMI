#ifndef Map_h
#define Map_h

#include <stdexcept>
#include <vector>
#include <utility>

#include "ExceptionMessages.h"

template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, std::vector<V>>> data;

    int findIndex(const K& key) const {
        for (int i = 0; i < (int)data.size(); i++)
            if (data[i].first == key)
                return i;
        return -1;
    }

public:
    using value_type = std::pair<K, V>;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    Map() = default;

    void add(const K& key, const V& value) {
        int idx = findIndex(key);
        if (idx != -1)
            data[idx].second.push_back(value);
    }

    void remove(const K& key) {
        int idx = findIndex(key);
        if (idx != -1)
            data[idx].second.clear();
    }

    std::vector<V>& operator[](const K& key) {
        int idx = findIndex(key);
        if (idx != -1)
            return data[idx].second;

        throw std::out_of_range(toString(ExceptionMessages::KEY_NOT_FOUND));
    }

    [[nodiscard]] unsigned size() const {
        int cnt = 0;
        for (const auto& p : data) {
            for (const auto& v : p.second) {
                cnt++;
            }
        }
        return cnt;
    }
    [[nodiscard]] bool empty() const { return data.empty(); }

    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }

    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }

    const std::vector<std::pair<K, std::vector<V>>>& getData() const { return data; }
};

#endif