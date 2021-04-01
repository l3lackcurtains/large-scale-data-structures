#!/bin/bash

#SBATCH --job-name=q1a_sw_mp2525
#SBATCH --output=/scratch/mp2525/sw_q1a.txt	
#SBATCH --error=/scratch/mp2525/sw_q1a.err
#SBATCH --time=360:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem1A ./sars_cov2.txt ./test.txt

make clean
