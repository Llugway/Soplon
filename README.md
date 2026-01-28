# Soplon

**Soplon** is a modular C++ web application developed in 2021 by the **Cyberens** team for the **Challenge IA & Cyber 2021**, a national competition organized by the French **Direction Générale de l'Armement (DGA)** and the **Pôle d'Excellence Cyber**.

The team achieved **2nd place nationally** and was awarded a **€100,000 development grant** to pursue the project.

The name *Soplon* comes from Spanish *soplón* ("informer" or "snitch") — a subtle nod to discreet anomaly detection and monitoring in cybersecurity.

## Project Overview

Soplon is **not** the core AI algorithm from the challenge (which focused on code style recognition). Instead, it is a **web-based interface + backend platform** built on top of the winning solution, designed to:

- Interact with processed data
- Visualize big-data problems
- Manage and query results in a structured database

The original vision was to evolve it into a full **big-data visualization and exploration platform** for cybersecurity and code analysis use cases.

## Features

- Model-View-Controller (MVC) architecture powered by **Drogon** (high-performance C++ HTTP framework)
- Modular components: controllers, models, views, filters and data sources
- **Multithreading** for efficient parallel processing (ThreadPool, concurrent chunk analysis)
- Database integration (MariaDB / MySQL via **X DevAPI**)
- Cross-platform build system with **CMake**
- JSON configuration support (`config.json`)

## Tech Stack

- **Language**: C++ (C++98 compatible)
- **Web Framework**: [Drogon](https://github.com/drogonframework/drogon)
- **Database Client**: MySQL Connector/C++ (X DevAPI)
- **Build Tool**: CMake
- **Package Manager**: vcpkg (recommended)

## Project Structure

```plaintext
Soplon/
├── controllers/       # Request handling & business logic
├── datasets/          # Data Folder
├── filters/           # Data validation & processing pipelines
├── models/            # Core data entities
├── sources/           # Data ingestion modules
├── test/              # Unit & integration tests
├── views/             # Output rendering & presentation
├── CMakeLists.txt
├── config.json
├── localhost          # Local setup/mocks
└── main.cc            # Application entry point
```

## Build & Run

### Prerequisites
- CMake ≥ 3.10
- C++ compiler (g++ / clang++)
- vcpkg (recommended) or system packages

### Windows (vcpkg)

```bash
vcpkg install drogon mysql-connector-cpp:x64-windows

git clone https://github.com/Llugway/Soplon.git
cd Soplon

mkdir build && cd build

cmake ..
cmake --build . --config Release

# Run 
./soplon
```

### Linux ()

```bash
sudo apt update
sudo apt install cmake g++ libssl-dev uuid-dev zlib1g-dev libmysqlcppconn8-dev
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Author

**Antonin Lerouge** (Developer)

## License

MIT License
