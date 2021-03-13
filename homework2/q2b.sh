#!/bin/bash

#SBATCH --job-name=q2b_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q2b.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q2b.err
#SBATCH --time=1800:00
#SBATCH --mem=30000

module load gcc/10.2

make

srun ./homework problem2B /common/contrib/classroom/inf503/test_genome.fasta -1 -1

make clean