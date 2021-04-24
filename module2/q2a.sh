#!/bin/bash

#SBATCH --job-name=q2a_linkedlist_mp2525
#SBATCH --output=/scratch/mp2525/linkedlist_q2a.txt	
#SBATCH --error=/scratch/mp2525/linkedlist_q2a.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem2A /common/contrib/classroom/inf503/test_genome.fasta -1 -1

make clean