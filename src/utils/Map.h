#ifndef Map_h
#define Map_h

#include <vector>

template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, V>> data;
    using iterator = typename std::vector<V>::iterator;
    using const_iterator = typename std::vector<V>::const_iterator;

    int findIndex(const K& key) const;

public:
    Map() = default;

    void add(const K& key, const V& value);

    void remove(const K& key);

    V& operator[](const K& key);

    int size() const;

    bool empty() const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
};

#endif