#!/bin/bash
#SBATCH --job-name=OMP_BinarySearch
#SBATCH --output=output_BinarySearch.txt
#SBATCH --error=binary_search_error.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
gcc -o OMP_BinarySearch OMP_BinarySearch.c -fopenmp
./OMP_BinarySearch
