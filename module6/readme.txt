################################################################################
# Main Modules
################################################################################
1) suffixTrie.h: It is a header file for the suffixTrie.cpp file.
2) suffixTrie.cpp: It includes the main suffix trie methods and its helper functions.
3) suffixTree.h: It is a header file for the suffixTree.cpp file.
4) suffixTree.cpp: It includes the main suffix trie methods and its helper functions.
5) homework.cpp: The main file that runs the solutions for problems 1a, 1b, 2a and 2b.

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
> ./homework {question_number} {genome_dataset} {search_dataset}

where
question_number: { problem1A, problem1B, problem2A, problem2B, problem2C }
genome_dataset: "./genome.txt"
search_dataset: "./search.txt"

Example:
for question 1A
> ./homework problem1A ./genome.txt ./search.txt
for question 2B
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
question_number: { q1a, q1b, q2a, q2b }
Example: for question 1a
> sbatch q1a.sh
