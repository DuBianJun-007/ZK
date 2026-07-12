# Dataset Files

This directory contains the datasets used in the experiments for the paper:

> **"A Dual-Heuristic String Matching Algorithm Based on Structural Constraint Propagation"**

## Download

Due to their large size, the dataset files are hosted externally.  
**Please download them from the following link and place them in this directory:**

> **🔗 Download Link: [Quark Cloud Drive](https://pan.quark.cn/s/beca437d4706?pwd=yJYF)**  
> **Extraction Code: `yJYF`**  
> **File: `datasets.zip`** (~900 MB)

## Directory Structure After Download

```
datasets/
├── README.md
├── gene_data/
│   ├── chr1.fna   (42 MB)  — Human chromosome 1 reference sequence
│   ├── chr2.fna   (32 MB)  — Human chromosome 2 reference sequence
│   ├── chr3.fna   (33 MB)  — Human chromosome 3 reference sequence
│   ├── chr4.fna   (22 MB)  — Human chromosome 4 reference sequence
│   ├── chr5.fna   (33 MB)  — Human chromosome 5 reference sequence
│   ├── chr6.fna   (39 MB)  — Human chromosome 6 reference sequence
│   ├── chr7.fna   (28 MB)  — Human chromosome 7 reference sequence
│   ├── chr8.fna   (28 MB)  — Human chromosome 8 reference sequence
│   ├── chr9.fna   (46 MB)  — Human chromosome 9 reference sequence
│   ├── chr10.fna  (20 MB)  — Human chromosome 10 reference sequence
│   ├── chr11.fna  (57 MB)  — Human chromosome 11 reference sequence
│   ├── chr12.fna  (65 MB)  — Human chromosome 12 reference sequence
│   ├── chr13.fna  (65 MB)  — Human chromosome 13 reference sequence
│   ├── chr14.fna  (63 MB)  — Human chromosome 14 reference sequence
│   ├── chr15.fna  (54 MB)  — Human chromosome 15 reference sequence
│   ├── chr16.fna  (57 MB)  — Human chromosome 16 reference sequence
│   ├── chr17.fna  (56 MB)  — Human chromosome 17 reference sequence
│   └── chr18.fna  (71 MB)  — Human chromosome 18 reference sequence
│   Total: ~800 MB (compressed)
└── text_data/
    ├── DNA.txt    (71 MB)   — DNA sequence text data
    └── words.txt  (4.8 MB)  — English word list
    Total: ~76 MB
```

## Data Sources

- **gene_data/**: Human reference genome (GRCh38/hg38) chromosome sequences in FASTA format
- **text_data/DNA.txt**: Concatenated DNA sequences for large-scale string matching benchmarks
- **text_data/words.txt**: English word list for natural language text matching experiments

## Usage

After downloading, place the `gene_data/` and `text_data/` folders inside this `datasets/` directory.  
The benchmark program will then be able to locate the data files automatically.
