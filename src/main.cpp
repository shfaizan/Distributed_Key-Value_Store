#include <iostream>
#include "KeyValueStore.h"

int main() {
    KeyValueStore store(5, 3);
    store.start();

    store.put("key1", "value1");
    store.put("key2", "value2");
    store.put("key3", "value3");

    std::cout << "Get key1: " << store.get("key1") << std::endl;
    std::cout << "Get key2: " << store.get("key2") << std::endl;

    store.remove("key1");
    std::cout << "Get key1 after removal: " << store.get("key1") << std::endl;

    store.stop();
    return 0;
}
