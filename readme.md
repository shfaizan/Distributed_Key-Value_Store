# Distributed Key-Value Store with Sharding, Replication, and Fault Tolerance

This project implements a distributed key-value store in C++ with features like sharding, replication, and fault tolerance. It supports multiple shards, data replication across nodes, and simulates node health monitoring and recovery.

## Features

- **Sharding**: Distributes data across multiple nodes using consistent hashing.
- **Replication**: Replicates data across multiple nodes to ensure availability and fault tolerance.
- **Fault Tolerance**: Monitors node health and handles node failures by re-replicating data.
- **Thread-safe**: Uses mutexes to ensure thread-safe operations.

## Project Structure

- `include/KeyValueStore.h`: Header file for the Key-Value Store class.
- `src/KeyValueStore.cpp`: Implementation of the Key-Value Store class.
- `include/Node.h`: Header file for the Node class.
- `src/Node.cpp`: Implementation of the Node class.
- `src/main.cpp`: Main driver code for the project.
- `Makefile`: Makefile to compile the project.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++)
- Make utility

### Building the Project

1. Clone the repository or download the project files.
2. Navigate to the project directory.
3. Run the following command to compile the project:

    ```bash
    make
    ```

### Running the Project

1. After building the project, run the executable:

    ```bash
    ./DistributedKeyValueStore
    ```

2. The program will start a key-value store with sharding, replication, and fault tolerance.
3. Test the key-value store by adding, retrieving, and removing keys.

### Cleaning Up

To clean up the compiled files, run:

```bash
make clean
```


### Additional Things I am planning to add in Future

1. **Documentation**: Add detailed comments in the code to explain the functionality of each part.
2. **Testing**: Implement a testing framework using `GoogleTest` or another testing library to demonstrate robustness.
3. **Advanced Features**: Adding more advanced features like:
   - Leader election for handling node failures.
   - Consistent hashing to handle dynamic addition and removal of nodes.
   - A more sophisticated health check mechanism.
4. **Performance Metrics**: Include performance metrics and profiling to show efficiency and scalability.
5. **Containerization**: Use Docker to containerize the application, demonstrating modern deployment practices.




## License
This project is licensed under the MIT License - see the LICENSE file for details.