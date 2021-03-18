#!/bin/bash

#SBATCH --job-name=q2b_ht_mp2525
#SBATCH --output=/scratch/mp2525/ht_q2b.txt	
#SBATCH --error=/scratch/mp2525/ht_q2b.err
#SBATCH --time=10:00
#SBATCH --mem=10000

module load gcc/10.2

make

srun ./homework problem2B /common/contrib/classroom/inf503/hw3_dataset.fa /common/contrib/classroom/inf503/test_genome.fasta

make clean
