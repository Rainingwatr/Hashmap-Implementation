#pragma once
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <stdexcept>

template<typename Key, typename Value>
class HashMap {
private:
    static const size_t INITIAL_CAPACITY = 16;
    static const float LOAD_FACTOR;
    std::vector<std::list<std::pair<Key, Value>>> buckets;
    size_t num_elements;
    std::hash<Key> hash_fn;

    void rehash() {
        size_t new_capacity = buckets.size() * 2;
        std::vector<std::list<std::pair<Key, Value>>> new_buckets(new_capacity);

        for (const auto& bucket : buckets) {
            for (const auto& kv : bucket) {
                size_t index = hash_fn(kv.first) % new_capacity;
                new_buckets[index].push_back(kv);
            }
        }

        buckets = std::move(new_buckets);
    }

public:
    HashMap() : buckets(INITIAL_CAPACITY), num_elements(0) {}

    void insert(const Key& key, const Value& value) {
        if ((float)num_elements / buckets.size() > LOAD_FACTOR) {
            rehash();
        }

        size_t index = hash_fn(key) % buckets.size();
        for (auto& kv : buckets[index]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        buckets[index].emplace_back(key, value);
        ++num_elements;
    }

    bool contains(const Key& key) const {
        size_t index = hash_fn(key) % buckets.size();
        for (const auto& kv : buckets[index]) {
            if (kv.first == key)
                return true;
        }
        return false;
    }

    Value& at(const Key& key) {
        size_t index = hash_fn(key) % buckets.size();
        for (auto& kv : buckets[index]) {
            if (kv.first == key)
                return kv.second;
        }
        throw std::out_of_range("Key not found");
    }

    bool remove(const Key& key) {
        size_t index = hash_fn(key) % buckets.size();
        auto& bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --num_elements;
                return true;
            }
        }
        return false;
    }

    size_t size() const {
        return num_elements;
    }
};

template<typename Key, typename Value>
const float HashMap<Key, Value>::LOAD_FACTOR = 0.75f;
