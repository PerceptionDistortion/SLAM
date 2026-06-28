# Modular SLAM Framework

> A production-oriented modular SLAM framework built from first principles using Modern C++, ROS2, and OpenCV.

![Language](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![ROS2](https://img.shields.io/badge/ROS2-Jazzy-blue)
![Platform](https://img.shields.io/badge/Linux-Ubuntu%2024.04-orange)
![Status](https://img.shields.io/badge/Status-Active%20Development-success)

---

## Overview

This project is a complete implementation of a modular Simultaneous Localization and Mapping (SLAM) framework designed with production-quality software architecture in mind.

Rather than implementing only a SLAM algorithm, the goal is to build an extensible robotics framework capable of supporting multiple sensors, localization methods, mapping techniques, and visualization backends.

The project emphasizes clean architecture, modular design, scalability, and maintainability while implementing state-of-the-art computer vision and robotics algorithms from first principles.

---

## Current Features

- Modular sensor abstraction
- ROS2 integration
- EuRoC dataset playback
- Camera calibration management
- ORB feature extraction
- Descriptor matching
- Temporal feature tracking
- Essential Matrix estimation
- PnP pose estimation
- Landmark triangulation
- Landmark observations
- Keyframe management
- Local map management
- OpenCV visualization
- Modern CMake build system

---

## Planned Features

- Visual-Inertial SLAM
- LiDAR integration
- Stereo camera support
- RGB-D support
- Bundle Adjustment
- Pose Graph Optimization
- Loop Closure Detection
- IMU Preintegration
- Multi-camera support
- Gazebo simulation
- RViz visualization
- OpenGL map visualization
- Dense Mapping
- Octomap integration

---

# Architecture

```
                   +----------------------+
                   |    Sensor Manager    |
                   +----------+-----------+
                              |
        +---------------------+----------------------+
        |                                            |
+---------------+                          +----------------+
| Camera Driver |                          | Dataset Driver |
+---------------+                          +----------------+
        |                                            |
        +---------------------+----------------------+
                              |
                     Camera Buffer
                              |
                      Visual Frontend
                              |
       +----------------------+----------------------+
       |                                             |
 Feature Tracking                        Pose Estimation
       |                                             |
       +----------------------+----------------------+
                              |
                        Mapping Module
                              |
                    Local Map / Landmarks
                              |
                     Backend Optimization
                              |
                     Visualization Layer
```

---

# Repository Structure

```
SLAM
│
├── modular_slam/
│   ├── frontend/
│   ├── mapping/
│   ├── backend/
│   ├── sensors/
│   ├── system/
│   └── visualization/
│
├── ros2_ws/
│   └── src/
│       └── dataset_driver/
│
├── docs/
│
├── datasets/
│
└── README.md
```

---

# Technology Stack

## Languages

- C++20
- Python (utilities)

## Robotics

- ROS2 Jazzy

## Computer Vision

- OpenCV

## Mathematics

- Eigen
- Sophus (planned)

## Optimization

- Ceres Solver (planned)

## Visualization

- OpenGL
- RViz (planned)

---

# SLAM Pipeline

```
Raw Camera Frames
        │
        ▼
Image Preprocessing
        │
        ▼
ORB Feature Detection
        │
        ▼
Feature Matching
        │
        ▼
Outlier Rejection
        │
        ▼
Essential Matrix
        │
        ▼
Pose Recovery
        │
        ▼
Track Management
        │
        ▼
Triangulation
        │
        ▼
Landmark Creation
        │
        ▼
PnP Localization
        │
        ▼
Map Update
```

---

# Design Philosophy

This project is designed around modular software engineering principles commonly used in production robotics systems.

Core objectives include:

- Separation of concerns
- Low coupling between modules
- High extensibility
- Clear ownership of data
- Reusable sensor interfaces
- Scalable architecture
- Modern C++ design patterns

The framework is intended to support multiple SLAM implementations while sharing common infrastructure for sensors, calibration, visualization, mapping, and optimization.

---

# Algorithms

Current implementation includes:

- ORB Features
- Brute Force Hamming Matching
- Lowe Ratio Test
- Cross Check Matching
- Essential Matrix Estimation
- RANSAC
- Pose Recovery
- Triangulation
- Perspective-n-Point (PnP)

Planned:

- Bundle Adjustment
- Pose Graph Optimization
- IMU Preintegration
- Visual-Inertial Fusion
- Loop Closure
- Dense Reconstruction

---

# Build

```bash
git clone https://github.com/PerceptionDistortion/SLAM.git

cd SLAM

mkdir build

cd build

cmake ..

make
```

---

# Dataset

Current support:

- EuRoC MAV Dataset

Planned:

- KITTI
- TUM RGB-D
- Custom camera streams
- Gazebo simulation

---

# Roadmap

- [x] Modular project architecture
- [x] ROS2 dataset driver
- [x] Feature extraction
- [x] Feature matching
- [x] Essential Matrix estimation
- [x] Landmark triangulation
- [x] PnP localization
- [x] Local mapping

---

- [ ] Bundle Adjustment
- [ ] Loop Closure
- [ ] Pose Graph Optimization
- [ ] Visual-Inertial SLAM
- [ ] LiDAR Mapping
- [ ] Stereo SLAM
- [ ] Multi-camera support
- [ ] Gazebo integration
- [ ] RViz visualization

---

# Learning Objectives

This repository serves as a long-term engineering project focused on understanding the complete SLAM stack from first principles, including:

- Computer Vision
- Robotics
- Estimation Theory
- Sensor Fusion
- Software Architecture
- High Performance C++
- ROS2
- Modern Robotics Systems

---

# License

This project is licensed under the MIT License.

---

## Author

**Anupam Chauhan**

Senior Software Engineer

M.Sc. Informatics – Technical University of Munich

Specializations:

- SLAM
- Computer Vision
- Robotics
- XR
- Modern C++

GitHub: https://github.com/PerceptionDistortion
