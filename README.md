# 46 Optimization Code

This project implements an optimization algorithm for determining the best scoring region based on input data representing crystals and voids. The program processes input data from a file, calculates a score, and outputs the optimized region and its edges, utilising 2-dimensional coordinate compression and 2-dimensional Kadane's algorithm.

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Replication of Results](#replication-of-results)
---

## Requirements

To run this project, ensure you have:

- A C++ compiler supporting C++11 or later (e.g., `g++`)
- A Unix-based system (Linux/macOS) or Windows with MinGW
- Standard input/output file redirection support

---

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/ShashwatShukla15/46_optimization_code.git
   cd 46_optimization_code

2.Compile the code using g++:
  g++ 46_optimization_code.cpp -o optimization
  
## Replication of Results:

    Ensure Correct Input File
    Verify that input.txt contains the correct format described above.

    Run the Code
    Execute the command:
      ./optimization

Check the Output
   Compare output.txt with expected values.

Modify and Experiment
   Try different input datasets by creating new files (e.g., input_test.txt) and rerun.
