#!/bin/bash

#SBATCH --job-name=arrays_mp2525_q3
#SBATCH --output=/scratch/mp2525/arrays_q3.txt	
#SBATCH --error=/scratch/mp2525/arrays_q3.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework.exe 3 /common/contrib/classroom/inf503/hw_dataset.fa

make clean