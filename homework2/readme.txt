################################################################################
# Main Modules
################################################################################
1) fasta.h: It is a header file for the fasta.cpp file which includes the class declaration and methods definition of "FASTAreadset_LL" class.
2) fasta.cpp: It includes the methods of "FASTAreadset_LL" class.
3) homework.cpp: The main file that runs the solutions for problems 1 and 2.

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
> ./homework {question_number} /common/contrib/classroom/inf503/hw_dataset.fa {limit_36mil_dataset} {limit_genome_dataset}

where
question_number: { problem1A, problem1B, problem1C, problem1D, problem2A, problem2B, problem2B2 }
limit_36mil_dataset: Limit the "/common/contrib/classroom/inf503/hw_dataset.fa" dataset. blank or "-1" for using full dataset.
limit_genome_dataset: Limit the "/common/contrib/classroom/inf503/test_genome.fasta" dataset. blank or "-1" for using full dataset.

Example: for question 3
> ./homework problem1C /common/contrib/classroom/inf503/hw_dataset.fa -1 -1
> ./homework problem1C /common/contrib/classroom/inf503/hw_dataset.fa -1
> ./homework problem1C /common/contrib/classroom/inf503/hw_dataset.fa
> ./homework problem1C /common/contrib/classroom/inf503/hw_dataset.fa 10000

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
question_number: { q1a, q1b, q1c, q1d, q2a, q2b, q2b2 }
Example: for question 3
> sbatch q1c.sh

################################################################################
***** Note ********
################################################################################
Here, problem2B2 and q2b2 refers to the alternative solution to the question 2B.
