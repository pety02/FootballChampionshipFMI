#ifndef Map_h
#define Map_h

#include <ExceptionMessages.h>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, V>> data;

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
            data[idx].second = value;
        else
            data.push_back({key, value});
    }

    void remove(const K& key) {
        int idx = findIndex(key);
        if (idx != -1)
            data.erase(data.begin() + idx);
    }

    V& operator[](const K& key) {
        int idx = findIndex(key);
        if (idx != -1)
            return data[idx].second;

        throw std::out_of_range(toString(ExceptionMessages::KEY_NOT_FOUND));
    }

    [[nodiscard]] unsigned size() const { return data.size(); }
    [[nodiscard]] bool empty() const { return data.empty(); }

    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }

    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }
};

#endif