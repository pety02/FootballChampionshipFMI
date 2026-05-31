//
// Created by User on 5/31/2026.
//

#include "Map.h"

template <typename K, typename V>
int Map<K, V>::findIndex(const K& key) const {
    for (int i = 0; i < (int)data.size(); i++) {
        if (data[i].first == key)
            return i;
    }
    return -1;
}

template <typename K, typename V>
void Map<K, V>::add(const K& key, const V& value) {
    int idx = findIndex(key);

    if (idx != -1)
        data[idx].second = value;
    else
        data.push_back({ key, value });
}

template <typename K, typename V>
void Map<K, V>::remove(const K& key) {
    int idx = findIndex(key);

    if (idx != -1)
        data.erase(data.begin() + idx);
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
    int idx = findIndex(key);

    if (idx != -1)
        return data[idx].second;

    data.push_back({ key, V{} });
    return data.back().second;
}

template <typename K, typename V>
int Map<K, V>::size() const {
    return (int)data.size();
}

template <typename K, typename V>
bool Map<K, V>::empty() const {
    return data.empty();
}

template <typename K, typename V>
auto Map<K, V>::begin() {
    return data.begin();
}

template <typename K, typename V>
auto Map<K, V>::end() {
    return data.end();
}

template <typename K, typename V>
auto Map<K, V>::begin() const {
    return data.begin();
}

template <typename K, typename V>
auto Map<K, V>::end() const {
    return data.end();
}