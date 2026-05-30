template <typename K, typename V>
class Map {
private:
    std::vector<std::pair<K, V>> data;

    int findIndex(const K& key) const {
        for (int i = 0; i < (int)data.size(); i++) {
            if (data[i].first == key)
                return i;
        }
        return -1;
    }

public:
    Map() = default;

    void add(const K& key, const V& value) {
        int idx = findIndex(key);

        if (idx != -1)
            data[idx].second = value;
        else
            data.push_back({ key, value });
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

        data.push_back({ key, V{} });
        return data.back().second;
    }

    int size() const { return (int)data.size(); }

    bool empty() const { return data.empty(); }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};