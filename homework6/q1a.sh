#!/bin/bash

#SBATCH --job-name=q1a_suffix_trie_mp2525
#SBATCH --output=/scratch/mp2525/suffix_trie_q1a.txt	
#SBATCH --error=/scratch/mp2525/suffix_trie_q1a.err
#SBATCH --time=120:00
#SBATCH --mem=20000

module load gcc/10.2

make

srun ./homework problem1A ./genome.txt ./search.txt

make clean
