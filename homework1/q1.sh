#!/bin/bash

#SBATCH --job-name=q1_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q1.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q1.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework 1 /common/contrib/classroom/inf503/hw_dataset.fa

make clean
