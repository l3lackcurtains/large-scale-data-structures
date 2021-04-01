################################################################################
# Main Modules
################################################################################
1) smithWaterman.h: It is a header file for the smithWaterman.cpp file.
2) smithWaterman.cpp: It includes the main smith waterman algorithm function and its helper functions.
3) blast.h: It is a header file for the blast.cpp file.
4) blast.cpp: It includes the methods "BLAST" class and the methods to implement blast according to assignment.
5) homework.cpp: The main file that runs the solutions for problems 1 and 2.

################################################################################
# Others modules used
################################################################################
ctime: It is used for the calculation of CPU time.
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
> ./homework {question_number} {sars_cov2} {test_dataset}

where
question_number: { problem1A, problem1B, problem2A, problem2B, problem2C }
sars_cov2: "./sars_cov2.txt"
test_dataset: "./test.txt" (used in question 1a and 2a)

Example:
for question 1A
> ./homework problem1A ./sars_cov2.txt ./test.txt
for question 2B
> ./homework problem2B ./sars_cov2.txt

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
question_number: { q1a, q1b, q2a, q2b, q2c }
Example: for question 1a
> sbatch q1a.sh
