CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread
TARGET = DistributedKeyValueStore

all: $(TARGET)

$(TARGET): main.o KeyValueStore.o Node.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o KeyValueStore.o Node.o

main.o: src/main.cpp include/KeyValueStore.h include/Node.h
	$(CXX) $(CXXFLAGS) -Iinclude -c src/main.cpp -o main.o

KeyValueStore.o: src/KeyValueStore.cpp include/KeyValueStore.h include/Node.h
	$(CXX) $(CXXFLAGS) -Iinclude -c src/KeyValueStore.cpp -o KeyValueStore.o

Node.o: src/Node.cpp include/Node.h
	$(CXX) $(CXXFLAGS) -Iinclude -c src/Node.cpp -o Node.o

clean:
	rm -f $(TARGET) *.o
