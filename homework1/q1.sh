#!/bin/bash
#SBATCH --job-name=arrays_mp2525
#SBATCH --output=/scratch/mp2525/arrays_q1.txt	
#SBATCH --error=/scratch/mp2525/arrays_q1.err
#SBATCH --time=20:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework.exe 1 /common/contrib/classroom/inf503/hw_dataset.fa

make clean
