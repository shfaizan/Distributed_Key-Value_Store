#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <vector>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>
#include "Node.h"

class KeyValueStore {
public:
    KeyValueStore(int shardCount, int replicationFactor);
    ~KeyValueStore();

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    void remove(const std::string& key);

    void start();
    void stop();

private:
    int shardCount_;
    int replicationFactor_;
    std::vector<Node*> nodes_;
    std::mutex storeMutex_;
    std::condition_variable cv_;
    bool running_;

    int getShardIndex(const std::string& key);
    void replicate(const std::string& key, const std::string& value, int shardIndex);
    void handleNodeFailure(int nodeIndex);
    void monitorNodes();
};

#endif // KEYVALUESTORE_H
