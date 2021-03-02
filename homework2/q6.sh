#!/bin/bash

#SBATCH --job-name=q6_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q6.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q6.err
#SBATCH --time=720:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem2B /common/contrib/classroom/inf503/test_genome.fasta

make clean