#ifndef Map_h
#define Map_h

#include <vector>

template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, V>> data;

    int findIndex(const K& key) const;

public:
    Map() = default;

    void add(const K& key, const V& value);

    void remove(const K& key);

    V& operator[](const K& key);

    int size() const;

    bool empty() const;

    auto begin();
    auto end();

    auto begin() const;
    auto end() const;
};

#endif