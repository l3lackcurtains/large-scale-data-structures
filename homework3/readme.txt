################################################################################
# Main Modules
################################################################################
1) fastaDAT.h: It is a header file for the fastaDAT.cpp file which includes the class declaration and methods definition of "FASTAreadset_DA" class.
2) fastaDAT.cpp: It includes the methods of "FASTAreadset_DA" class.
3) fastaHT.h: It is a header file for the fastaHT.cpp file which includes the class declaration and methods definition of "FASTAreadset_Chain" class.
4) fastaHT.cpp: It includes the methods of "FASTAreadset_Chain" class.
5) homework.cpp: The main file that runs the solutions for problems 1 and 2.

################################################################################
# Others modules used
################################################################################
ctime: It is used for the calculation of CPU time.

################################################################################
# Compile the project
################################################################################
Run the command:
> make

################################################################################
# Execute homework subproblems
################################################################################
Run the command:
> ./homework {question_number} {read_dataset} {genome_dataset}

where
question_number: { problem1A, problem1B, problem2A, problem2B }
read_dataset: "/common/contrib/classroom/inf503/hw3_dataset.fa"
genome_dataset: "/common/contrib/classroom/inf503/test_genome.fasta" (used in question 1b and 2b)

Example:
for question 1A
> ./homework problem1A /common/contrib/classroom/inf503/hw3_dataset.fa 
for question 2B
> ./homework problem1A /common/contrib/classroom/inf503/hw3_dataset.fa /common/contrib/classroom/inf503/test_genome.fasta

################################################################################
# Clean the project
################################################################################
Run the command:
> make Clean

################################################################################
# Execute in monsoon
################################################################################
Run the command:
> sbatch q{question_number}.sh
where
question_number: { q1A, q1B, q2A, q2B }
Example: for question 1a
> sbatch q1A.sh
