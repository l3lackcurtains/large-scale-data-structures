#!/bin/bash

#SBATCH --job-name=q2_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q2.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q2.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework 2 /common/contrib/classroom/inf503/hw_dataset.fa

make clean