#include <iostream>
#include <cstddef>
#include <functional>
#include <algorithm>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
    class HashNode {
    public:
        Key key;
        Value value;

        explicit HashNode(const Key &key) : key(key), value() {}

        HashNode(const Key &key, const Value &value) : key(key), value(value) {}

        bool operator==(const HashNode &other) const {
            return key == other.key;
        }

        bool operator!=(const HashNode &other) const {
            return key != other.key;
        }

        bool operator<(const HashNode &other) const {
            return key < other.key;
        }   

        bool operator>(const HashNode &other) const {
            return key > other.key;
        }

        bool operator==(const Key &key_) {
            return key == key_;
        }

        void print() const {
            std::cout << key << " " << value << " ";
        }
    };
private:
    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;
    Hash hashFunction;
    size_t tableSize;
    size_t numElemtens;

    float maxLoadFactor = 0.75;

    size_t hash(const Key &key) const {
        return hashFunction(key) % tableSize;
    }

    void rehash(size_t newSize) {
        std::vector<Bucket> newBuckets(newSize);
        for(Bucket &bucket : buckets) {
            for(HashNode &hashNode : bucket) {
                size_t newIndex = hashFunction(hashNode.key) % newSize;
                newBuckets[newIndex].push_back(hashNode);
            }
        }
        buckets = std::move(newBuckets);
        tableSize = newSize;
    }

public:
    HashTable(size_t size = 10, const Hash &hashFunc = Hash())
        : buckets(size), hashFunction(hashFunc), tableSize(size), numElemtens(0) {}
    
    void insert(const Key &key, const Value &value) {
        if(numElemtens + 1 > maxLoadFactor * tableSize) {
            if(tableSize == 0) tableSize = 1;
            rehash(tableSize * 2);
        }
        size_t index = hash(key);
        std::list<HashNode> &bucket = buckets[index];
        if(std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(HashNode(key, value));
            ++numElemtens;
        }
    }

    void insertKey(const Key &key) {
        insert(key, Value{});
    }

    void erase(const Key &key) {
        size_t index = hash(key);
        auto &bucket = buckets[index];
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if(it != bucket.end()) {
            bucket.erase(it);
            numElemtens--;
        }
    }

    Value *find(const Key &key) {
        size_t index = hash(key);
        auto &bucket = buckets[index];
        auto ans = std::find(bucket.begin(), bucket.end(), key);
        if(ans != bucket.end()) {
            return &ans->value;
        }
        return nullptr;
    }

    size_t size() const {
        return numElemtens;
    }

    void print() const{
        for(size_t i = 0; i < buckets.size(); ++i) {
            for(const HashNode &element : buckets[i]) {
                element.print();
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        this->buckets.clear();
        this->tableSize = 0;
        this->numElemtens = 0;
    }
};

int main() {
    HashTable<int, int> myhashtable;
    myhashtable.insert(5,1);
    myhashtable.erase(5);
    myhashtable.insert(2,1);
    myhashtable.find(2);
    myhashtable.print();
    myhashtable.insert(3,3);
    myhashtable.print();
    myhashtable.clear();
    return 0;
}