#!/bin/bash

#SBATCH --job-name=q2a_ht_mp2525
#SBATCH --output=/scratch/mp2525/ht_q2a.txt	
#SBATCH --error=/scratch/mp2525/ht_q2a.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem2A /common/contrib/classroom/inf503/hw3_dataset.fa

make clean
