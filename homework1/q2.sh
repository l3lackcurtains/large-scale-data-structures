#!/bin/bash

#SBATCH --job-name=arrays_mp2525_q2
#SBATCH --output=/scratch/mp2525/arrays_q2.txt	
#SBATCH --error=/scratch/mp2525/arrays_q2.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework.exe 2 /common/contrib/classroom/inf503/hw_dataset.fa

make clean