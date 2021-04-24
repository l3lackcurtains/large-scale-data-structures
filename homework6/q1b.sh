#!/bin/bash

#SBATCH --job-name=q1b_suffix_trie_mp2525
#SBATCH --output=/scratch/mp2525/suffix_trie_q1b.txt	
#SBATCH --error=/scratch/mp2525/suffix_trie_q1b.err
#SBATCH --time=120:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem1B ./genome.txt

make clean