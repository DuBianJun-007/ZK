# ZK — A Dual-Heuristic String Matching Algorithm Based on Structural Constraint Propagation

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-%3E%3D3.14-green.svg)](https://cmake.org/)

This repository provides the official implementation of the ZK family of string matching algorithms, as described in the paper:

> **"A Dual-Heuristic String Matching Algorithm Based on Structural Constraint Propagation"**  
> *Submitted to Pattern Analysis and Applications (Springer)*

## Overview

ZK (ZK2 and ZK3) are novel exact string matching algorithms that leverage **multi-dimensional character feature tables** to achieve larger shift distances than classical approaches. The core innovation is the use of **structural constraint propagation** via 2-character (ZK2) and 3-character (ZK3) look-ahead heuristics.

### Algorithms Implemented

| Algorithm | Type | Description |
|-----------|------|-------------|
| Brute-Force | Baseline | Naive character-by-character comparison |
| KMP | Classical | Knuth-Morris-Pratt with prefix function |
| BM | Classical | Boyer-Moore (bad character + good suffix) |
| BMH | Classical | Boyer-Moore-Horspool (bad character only) |
| Sunday (QS) | Classical | Sunday Quick Search variant |
| Sunday (MS) | Classical | Sunday MS variant with optimal comparison order |
| **ZK2** | **Proposed** | Dual-heuristic with 2D feature table (128×128) |
| **ZK2 ASCII** | **Proposed** | ZK2 optimized for ASCII-only input |
| **ZK2 UTF** | **Proposed** | ZK2 with UTF-8 encoding support |
| **ZK3** | **Proposed** | Triple-heuristic with 3D feature table (128×128×128) |
| **ZK3 UTF** | **Proposed** | ZK3 with UTF-8 encoding support |

## Requirements

- **C++17** or later compiler
- **CMake** ≥ 3.14
- Any platform: Linux, macOS, or Windows

### Supported Compilers

| Compiler | Minimum Version |
|----------|----------------|
| GCC | 8.0+ |
| Clang | 7.0+ |
| MSVC | Visual Studio 2019 16.8+ |

## Quick Start

```bash
# Clone the repository
git clone https://github.com/DuBianJun-007/ZK.git
cd ZK

# Build with CMake
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run the demo (uses embedded test sequence — no dataset required)
./zk_demo
```

Expected output:
```
No input file specified. Using embedded DNA test sequence for verification.

Text length:     2193
Pattern length:  150

Running algorithms...
===============================================================================
Algorithm             Time (ms)          Matches
===============================================================================
BM                    <time> ms          1
BMH                   <time> ms          1
Brute-Force           <time> ms          1
KMP                   <time> ms          1
Sunday (QS)           <time> ms          1
Sunday (MS)           <time> ms          1
ZK2                   <time> ms          1
ZK2 (ASCII)           <time> ms          1
ZK3                   <time> ms          1
===============================================================================
```

## Reproducing Experiments

### Step 1: Download Datasets

The experimental datasets (~900 MB total) are hosted separately due to their size:

> **🔗 Download Link: [Quark Cloud Drive](https://pan.quark.cn/s/beca437d4706?pwd=yJYF)** | **Extraction Code: `yJYF`**

After downloading, extract the contents into the `datasets/` directory:

```bash
# Expected structure after extraction:
datasets/
├── gene_data/
│   ├── chr1.fna  ...  chr18.fna    # Human chromosome reference sequences (FASTA)
└── text_data/
    ├── DNA.txt                      # Concatenated DNA sequence data
    └── words.txt                    # English word list
```

### Step 2: Build from Source

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Step 3: Run Benchmarks

**Gene data benchmark (all 18 chromosomes):**
```bash
./zk_demo --gene-data ../datasets/gene_data --pattern "ACGTACGT"
```

**Single file benchmark (DNA.txt):**
```bash
./zk_demo --file ../datasets/text_data/DNA.txt
```

**Single file benchmark with custom pattern:**
```bash
./zk_demo --file ../datasets/text_data/DNA.txt --pattern "TATAAA"
```

**English text benchmark:**
```bash
./zk_demo --file ../datasets/text_data/words.txt --pattern "algorithm"
```

### Step 4: Understand the Results

The program outputs, for each algorithm:
- **Time (ms)**: Wall-clock execution time measured with `std::chrono::high_resolution_clock`
- **Matches**: Number of pattern occurrences found

All algorithms should report identical match counts (they are all exact matching algorithms).

## Experiment Datasets

| Dataset | File(s) | Size | Description |
|---------|---------|------|-------------|
| **Gene Data** | `chr1.fna` – `chr18.fna` | ~800 MB | Human reference genome (GRCh38/hg38), chromosomes 1–18 in FASTA format |
| **DNA Text** | `DNA.txt` | 71 MB | Concatenated DNA sequences for large-scale matching |
| **Words** | `words.txt` | 4.8 MB | English word list for natural language matching experiments |

### Data Source

The chromosome FASTA files are from the [GRCh38/hg38 human reference genome assembly](https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/), provided by the Genome Reference Consortium.

## Project Structure

```
ZK/
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This file
├── LICENSE                     # MIT License
├── .gitignore                  # Git ignore rules
├── src/                        # Algorithm source code
│   ├── force.h / force.cpp     # Brute-force matching
│   ├── kmp.h / kmp.cpp         # KMP algorithm
│   ├── bm.h / bm.cpp           # Boyer-Moore algorithm
│   ├── bmh.h / bmh.cpp         # Boyer-Moore-Horspool algorithm
│   ├── sunday.h / sunday.cpp   # Sunday algorithms (QS + MS)
│   ├── zk2.h / zk2.cpp         # ZK2 — dual-heuristic matching
│   ├── zk2_ascii.h / zk2_ascii.cpp
│   ├── zk2_utf.h / zk2_utf.cpp
│   ├── zk3.h / zk3.cpp         # ZK3 — triple-heuristic matching
│   ├── zk3_utf.h / zk3_utf.cpp
│   └── benchmark.h / benchmark.cpp  # High-precision timing framework
├── examples/
│   └── demo.cpp                # Command-line demo/benchmark program
├── results/                    # Experimental result spreadsheets
│   ├── 8.xlsx ~ 128.xlsx       # Results at various text sizes
│   ├── DNA.xlsx
│   └── englishTexts.xlsx
└── datasets/                   # Dataset storage (downloaded separately)
    ├── README.md               # Dataset download instructions
    ├── gene_data/              # Chromosome FASTA files
    └── text_data/              # DNA.txt, words.txt
```

## API Usage

Include the algorithm headers and link against `zk_algorithms`:

```cpp
#include "zk2.h"
#include "zk3.h"
#include "benchmark.h"

// Create algorithm instances
ZK2 zk2;
ZK3 zk3;

// Define text, pattern, and character set
const char* text = "atcgatcgatcg...";
const char* pattern = "atcg";
const char charset[] = {'a', 'c', 'g', 't'};

// Run matching
int matches = zk2.ZKSearch(text, pattern, strlen(text), strlen(pattern), charset);

// Measure execution time
retrieval_algorithms_time timer;
double time_ms = timer.ZK2_retrieval_time(text, pattern, strlen(text), strlen(pattern), charset);
```

## Build Options

| Option | Description | Default |
|--------|-------------|---------|
| `CMAKE_BUILD_TYPE` | `Release` for optimized builds, `Debug` for development | `Release` |
| `CMAKE_CXX_COMPILER` | Specify compiler (e.g., `g++-11`, `clang++-14`) | Auto-detected |

```bash
# Optimized release build (recommended for benchmarking)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Use specific compiler
cmake .. -DCMAKE_CXX_COMPILER=clang++-14
```

## Citation

If you use this code in your research, please cite:

```bibtex
@article{kong2024zk,
  title     = {A Dual-Heuristic String Matching Algorithm Based on Structural Constraint Propagation},
  author    = {Kong, Dechao},
  journal   = {Pattern Analysis and Applications},
  year      = {2024},
  publisher = {Springer}
}
```

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

## Contact

For questions or issues, please open a [GitHub Issue](https://github.com/DuBianJun-007/ZK/issues).
