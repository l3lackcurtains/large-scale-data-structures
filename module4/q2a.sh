#!/bin/bash

#SBATCH --job-name=q2a_blast_mp2525
#SBATCH --output=/scratch/mp2525/blast_q2a.txt	
#SBATCH --error=/scratch/mp2525/blast_q2a.err
#SBATCH --time=1200:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem2A ./sars_cov2.txt ./test.txt

make clean