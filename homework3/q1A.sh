#!/bin/bash

#SBATCH --job-name=q1a_dat_mp2525
#SBATCH --output=/scratch/mp2525/dat_q1a.txt	
#SBATCH --error=/scratch/mp2525/dat_q1a.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem1A /common/contrib/classroom/inf503/hw3_dataset.fa

make clean
