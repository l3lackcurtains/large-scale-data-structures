#!/bin/bash

#SBATCH --job-name=q1a_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q1a.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q1a.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem1A /common/contrib/classroom/inf503/hw_dataset.fa -1

make clean
