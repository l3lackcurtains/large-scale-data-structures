################################################################################
# Main Modules
################################################################################
1) prefixTrie.h: It is a header file for the prefixTrie.cpp file.
2) prefixTrie.cpp: It includes the main prefix trie methods and its helper functions.
3) homework.cpp: The main file that runs the solutions for problems 1a and 1b.

################################################################################
# Others modules used
################################################################################
string.h: It is used to get string length and the string reversal to the array of characters data structure.

################################################################################
# Compile the project
################################################################################
Run the command:
> make

################################################################################
# Execute homework subproblems
################################################################################
Run the command:
> ./homework {question_number} {genome_dataset}

where
question_number: { problem1A, problem1B, problem2A, problem2B, problem2C }
genome_dataset: "./genome.txt"

Example:
for question 1A
> ./homework problem1A ./genome.txt
for question 1B
> ./homework problem1B ./genome.txt

################################################################################
# Clean the project
################################################################################
Run the command:
> make clean

################################################################################
# Execute in monsoon
################################################################################
Run the command:
> sbatch q{question_number}.sh
where
question_number: { q1a, q1b }
Example: for question 1a
> sbatch q1a.sh
