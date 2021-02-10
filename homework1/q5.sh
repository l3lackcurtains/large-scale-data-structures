#!/bin/bash
#SBATCH --job-name=arrays
#SBATCH --output=/scratch/mp2525/arrays.out
#SBATCH --time=20:00
#SBATCH --workdir=/home/mp2525
#SBATCH --mem=10000

srun ./homework 5 sample_hw_dataset