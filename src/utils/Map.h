#ifndef Map_h
#define Map_h

#include <stdexcept>
#include <vector>
#include <utility>
#include <algorithm>

#include "ExceptionMessages.h"

/**
 * Simple associative container:
 * - One key maps to multiple values (vector<V>)
 */
template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, std::vector<V>>> data;

    /**
     * Finds index of a key in the internal storage.
     *
     * @return index if found, -1 otherwise
     */
    int findIndex(const K& key) const {
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].first == key)
                return static_cast<int>(i);
        }
        return -1;
    }

public:
    using iterator = typename std::vector<std::pair<K, std::vector<V>>>::iterator;
    using const_iterator = typename std::vector<std::pair<K, std::vector<V>>>::const_iterator;

    /**
     * Default constructor.
     */
    Map() = default;

    /**
     * Adds a value under a key.
     */
    void add(const K& key, const V& value) {
        int idx = findIndex(key);

        if (idx == -1) {
            data.push_back({ key, std::vector<V>{ value } });
        } else {
            data[idx].second.push_back(value);
        }
    }

    /**
     * Clears all values for a key (does NOT erase key entry).
     */
    void remove(const K& key) {
        int idx = findIndex(key);
        if (idx != -1) {
            data[idx].second.clear();
        }
    }

    /**
     * Access values for a key (throws if missing).
     */
    std::vector<V>& operator[](const K& key) {
        int idx = findIndex(key);

        if (idx == -1) {
            throw std::out_of_range(toString(ExceptionMessages::KEY_NOT_FOUND));
        }

        return data[idx].second;
    }

    /**
     * Const access version.
     */
    const std::vector<V>& operator[](const K& key) const {
        int idx = findIndex(key);

        if (idx == -1) {
            throw std::out_of_range(toString(ExceptionMessages::KEY_NOT_FOUND));
        }

        return data[idx].second;
    }

    /**
     * Number of stored keys (NOT total values).
     */
    [[nodiscard]] unsigned size() const {
        return static_cast<unsigned>(data.size());
    }

    /**
     * Checks if map has no keys.
     */
    [[nodiscard]] bool empty() const {
        return data.empty();
    }

    /**
     * Iterators.
     */
    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }

    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }

    const_iterator cbegin() const { return data.cbegin(); }
    const_iterator cend() const { return data.cend(); }

    /**
     * Exposes internal structure (read-only).
     */
    const std::vector<std::pair<K, std::vector<V>>>& getData() const {
        return data;
    }

    /**
     * Sorts entries using comparator on keys.
     */
    template<typename Compare>
    void sortBy(Compare comp) {
        std::sort(data.begin(), data.end(),
            [&](const auto& a, const auto& b) {
                return comp(a.first, b.first);
            }
        );
    }
};

#endif