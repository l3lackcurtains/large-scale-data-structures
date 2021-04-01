#!/bin/bash

#SBATCH --job-name=q2b_blast_mp2525
#SBATCH --output=/scratch/mp2525/blast_q2b.txt	
#SBATCH --error=/scratch/mp2525/blast_q2b.err
#SBATCH --time=360:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem2B ./sars_cov2.txt

make clean