#!/bin/bash
#SBATCH --job-name=arrays_mp2525
#SBATCH --output=/scratch/mp2525/arrays_q4.txt	
#SBATCH --error=/scratch/mp2525/arrays_q4.err
#SBATCH --time=20:00
#SBATCH --mem=10000

module load gcc/10.2

g++ -O3 homework.cpp -o homework.exe

srun ./homework.exe 4 /common/contrib/classroom/inf503/hw_dataset.fa
