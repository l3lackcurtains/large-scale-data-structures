#!/bin/bash

#SBATCH --job-name=q2c_blast_mp2525
#SBATCH --output=/scratch/mp2525/blast_q2c.txt	
#SBATCH --error=/scratch/mp2525/blast_q2c.err
#SBATCH --time=360:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem2C ./sars_cov2.txt

make clean