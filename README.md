# Soplon

**Soplon** is a modular C++ application originally developed in 2021 as part of the **Challenge IA & Cyber** organized by the French Directorate General of Armaments (DGA) and the Cyber Excellence Pole.  
It was built by the **Cyberens** team during the competition.

The project demonstrates a clean MVC-inspired architecture for handling data sources, filtering, database interactions, and presentation logic — with a focus on robustness and extensibility in a cybersecurity context.

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
- Other: JSON config, potential local server/DB setup (`localhost`)

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

## Authors

**Cyberens Team**
- **Bernard Roussely** (CTO)
- **Antonin Lerouge** (Developer)

## License

MIT License
