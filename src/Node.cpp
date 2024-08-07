#include "Node.h"
#include <random>

Node::Node(int id) : id_(id) {}

void Node::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(nodeMutex_);
    data_[key] = value;
}

std::string Node::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(nodeMutex_);
    if (data_.find(key) != data_.end()) {
        return data_[key];
    }
    return "";
}

void Node::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(nodeMutex_);
    data_.erase(key);
}

bool Node::isHealthy() const {
    // Simulate random node failure for demonstration
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    return dis(gen) > 2; // 80% chance that the node is healthy
}
