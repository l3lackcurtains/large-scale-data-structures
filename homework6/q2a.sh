#!/bin/bash

#SBATCH --job-name=q2a_suffix_tree_mp2525
#SBATCH --output=/scratch/mp2525/suffix_tree_q2a.txt	
#SBATCH --error=/scratch/mp2525/suffix_tree_q2a.err
#SBATCH --time=120:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem2A ./genome.txt ./search.txt

make clean