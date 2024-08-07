#include "KeyValueStore.h"
#include <iostream>

KeyValueStore::KeyValueStore(int shardCount, int replicationFactor)
    : shardCount_(shardCount), replicationFactor_(replicationFactor), running_(false) {
    for (int i = 0; i < shardCount; ++i) {
        nodes_.push_back(new Node(i));
    }
}

KeyValueStore::~KeyValueStore() {
    stop();
    for (auto node : nodes_) {
        delete node;
    }
}

void KeyValueStore::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(storeMutex_);
    int shardIndex = getShardIndex(key);
    nodes_[shardIndex]->put(key, value);
    replicate(key, value, shardIndex);
}

std::string KeyValueStore::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex_);
    int shardIndex = getShardIndex(key);
    return nodes_[shardIndex]->get(key);
}

void KeyValueStore::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex_);
    int shardIndex = getShardIndex(key);
    nodes_[shardIndex]->remove(key);
    replicate(key, "", shardIndex); // Replicate removal
}

void KeyValueStore::start() {
    running_ = true;
    std::thread(&KeyValueStore::monitorNodes, this).detach();
}

void KeyValueStore::stop() {
    {
        std::lock_guard<std::mutex> lock(storeMutex_);
        running_ = false;
    }
    cv_.notify_all();
}

int KeyValueStore::getShardIndex(const std::string& key) {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % shardCount_;
}

void KeyValueStore::replicate(const std::string& key, const std::string& value, int shardIndex) {
    for (int i = 1; i < replicationFactor_; ++i) {
        int nextShard = (shardIndex + i) % shardCount_;
        nodes_[nextShard]->put(key, value);
    }
}

void KeyValueStore::handleNodeFailure(int nodeIndex) {
    std::lock_guard<std::mutex> lock(storeMutex_);
    std::cout << "Node " << nodeIndex << " failed. Re-replicating data..." << std::endl;
    // Handle node failure and re-replicate data
    // This can be enhanced with more sophisticated fault-tolerant mechanisms
}

void KeyValueStore::monitorNodes() {
    while (running_) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        for (size_t i = 0; i < nodes_.size(); ++i) {
            if (!nodes_[i]->isHealthy()) {
                handleNodeFailure(i);
            }
        }
    }
}
