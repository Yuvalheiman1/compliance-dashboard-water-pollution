# Compliance Dashboard – Water Pollution

A modern C++/Qt desktop application for visualizing, filtering, and analyzing water pollution compliance data. This project was developed as part of the User Interfaces (UI) module at the University of Leeds, in a collaborative group setting. The module focused on practical experience with Qt for building cross-platform desktop applications.

## 🚀 Project Overview

- **Interactive Dashboard:** Visualizes water sample data, pollutant thresholds, and compliance status.
- **Filtering:** Filter by year, location, pollutant, and compliance status.
- **Summary Cards:** Quick stats for key pollutants and locations.
- **Detailed Table:** Explore raw and processed water sample data.
- **Statistics:** Identify best/worst locations, years, and pollutants.
- **CSV Import:** Load and analyze new datasets easily.

## ✨ Features

- Built with C++ and Qt for cross-platform desktop support
- Modular, object-oriented design (separate model, view, and logic)
- Custom widgets for summary, filtering, and data display
- CSV parsing for flexible data import
- Extensible for new pollutants, locations, or compliance rules

## 🛠️ Tech Stack

- C++17+
- Qt 5/6 (Widgets, Core)
- Standard Library (STL)
- Custom CSV parser

## 📦 Getting Started

### Prerequisites

- C++ compiler (GCC, Clang, MSVC)
- Qt 5 or 6 (with qmake or CMake)
- CMake (recommended)

### Build Instructions

```bash
cd compliance-dashboard-water-pollution/test_project
mkdir build
cd build
cmake ..
cmake --build .
./ComplianceDashboard
```

Or use Qt Creator to open `CMakeLists.txt` and build/run the project.

## 🏗️ Project Structure

```
test_project/
  ComplianceDashboard.cpp/hpp  # Main dashboard UI
  dataset.cpp/hpp              # Data loading and model logic
  WaterSample.cpp/hpp          # Water sample data structure
  PollutantSample.cpp/hpp      # Pollutant data structure
  Locations.csv                # List of monitored locations
  main.cpp                     # Application entry point
  ...
```

## 📊 Data

- **Locations.csv:** List of water monitoring locations
- **Y-2024.csv:** Example water sample dataset (add your own for new years)
- **pollutants.csv:** Pollutant definitions and thresholds

## 🤝 Contributing

Pull requests and suggestions are welcome! Please open an issue or PR for improvements.

---

> This project was created as part of the User Interfaces module at the University of Leeds. It provided hands-on experience with Qt and collaborative software development in a group environment.
