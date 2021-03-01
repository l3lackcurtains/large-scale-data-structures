#!/bin/bash

#SBATCH --job-name=q5_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q5.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q5.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework.exe 5 /common/contrib/classroom/inf503/test_genome.fasta

make clean