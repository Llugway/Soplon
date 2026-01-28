# Soplon

**Soplon** is a modular C++ application developed in 2021 for the **Challenge IA & Cyber 2021**, a national competition organized by the French **Direction Générale de l'Armement (DGA)** and the **Pôle d'Excellence Cyber**.
It was built by the **Cyberens** team during the competition.

The **Cyberens** team secured **2nd place overall**.

The solution demonstrates a clean MVC-inspired architecture for handling data sources, filtering, database interactions, and presentation logic — with a focus on robustness and extensibility in a cybersecurity context.

## Features

- Model-View-Controller (MVC) structure for clean separation of concerns
- Modular components: controllers, models, views, filters, and data sources
- CMake-based build system
- JSON configuration support (`config.json`)
- Basic database client interface (`DbClient.h`)
- Unit/integration test directory (`test/`)

## Tech Stack

- **Language**: C++ (C++98 compatible)
- **Build**: CMake
- **Configuration**: JSON
- **Other**: Potential local server/DB setup (`localhost`)

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
├── DbClient.h
├── config.json
├── localhost          # Local setup/mocks
└── main.cc            # Application entry point
```

## Getting Started

### Prerequisites
- CMake ≥ 3.10
- C++ compiler (g++ / clang++)

### Build & Run

```bash
# Clone the repo
git clone https://github.com/Llugway/Soplon.git
cd Soplon

# Create build directory
mkdir build && cd build

# Configure & build
cmake ..
make

# Run 
./soplon
```

## Authors & Acknowledgments

**Cyberens Team**
- **Bernard Roussely** (CTO)
- **Antonin Lerouge** (Developer)

## License

MIT License
