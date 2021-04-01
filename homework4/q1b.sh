#!/bin/bash

#SBATCH --job-name=q1b_sw_mp2525
#SBATCH --output=/scratch/mp2525/sw_q1b.txt	
#SBATCH --error=/scratch/mp2525/sw_q1b.err
#SBATCH --time=360:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem1B ./sars_cov2.txt

make clean