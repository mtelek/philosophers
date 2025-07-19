# Philosophers

[![Build Status](https://github.com/mtelek/philosophers/actions/workflows/build.yml/badge.svg?cache_buster=1)](https://github.com/mtelek/philosophers/actions)
[![Code Size](https://img.shields.io/github/languages/code-size/mtelek/philosophers?style=flat-square)](https://github.com/mtelek/philosophers)
![Project Score](https://img.shields.io/badge/Philosophers-100%25-brightgreen)

*A visualization of the Dining Philosophers problem.*

## 📖 Project Description
This project solves the **Dining Philosophers problem**, a classic synchronization challenge where multiple philosophers (threads) share forks (mutexes) to eat, think, and sleep without deadlocks or starvation. The goal is to ensure threads safely access shared resources while logging their states in real-time.  
*For background on this classic CS problem:* [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Key Features:
- **Thread-based simulation**: Each philosopher is a thread, and forks are protected by mutexes.
- **Starvation prevention**: Philosophers must eat within `time_to_die` or the program terminates.
- **Real-time logging**: Timestamped output for all actions (eating, sleeping, thinking, etc.).
- **Configurable parameters**: Adjust philosopher count, timings, and optional meal limits.

---

## 🛠 Installation
### Prerequisites:
- C Compiler (`cc`/`gcc`/`clang`)
- **Make** (GNU Make)
- **Unix-based OS** (Linux/macOS)

### Steps:
  Clone the repository:
   ```bash
   git clone git@github.com:mtelek/philosophers.git
   cd philosophers/philo
   make
   ```
## 🚀 Usage
  ```bash
   ./philo <philos> <die> <eat> <sleep> [<meals>]
  ```
### Parameters
| Parameter | Description | Example Value |
|-----------|-------------|---------------|
| philos | Number of philosophers | 4 |
| die | Time until starvation | 800 |
| eat | Time spent eating | 200 |
| sleep | Time spent sleeping | 200 |
| meals | Optional meal count to stop simulation | 5 |

## 🌈 Visualizing the Simulation

The philosopher states can be visualized using this interactive tool created by [nafuka11](https://github.com/nafuka11):  
[**Philosophers Visualizer**](https://nafuka11.github.io/philosophers-visualizer/)

### How to Use:
1. Run your program and redirect the output to a file:
   ```bash
   ./philo 4 800 200 200 > output.txt
   ```
2. Paste your `output.txt` contents into the visualizer's input field
   
## 🧪 Testing
