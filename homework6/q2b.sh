#!/bin/bash

#SBATCH --job-name=q2b_suffix_tree_mp2525
#SBATCH --output=/scratch/mp2525/suffix_tree_q2b.txt	
#SBATCH --error=/scratch/mp2525/suffix_tree_q2b.err
#SBATCH --time=120:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem2B ./genome.txt

make clean