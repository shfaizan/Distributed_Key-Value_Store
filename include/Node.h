#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <mutex>
#include <string>

class Node {
public:
    Node(int id);
    ~Node() = default;

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    void remove(const std::string& key);
    bool isHealthy() const;

private:
    int id_;
    std::unordered_map<std::string, std::string> data_;
    std::mutex nodeMutex_;
};

#endif // NODE_H
