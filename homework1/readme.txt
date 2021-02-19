################################################################################
# Main Modules
################################################################################
1) fasta.h: It is a header file for the fasta.cpp file which includes the class declaration and methods definition of "FASTA_readset" class.
2) fasta.cpp: It includes the methods of "FASTA_readset" class.
3) homework.cpp: The main file that runs the solutions for 5 questions.

################################################################################
# Others modules used
################################################################################
ctime: It is used for the calculation of CPU time.
string.h: Two functions are employed from this library: strcmp and strcpy in question 5.

################################################################################
# Compile the project
################################################################################
Run the command:
> make

################################################################################
# Execute homework subproblems
################################################################################
Run the command:
> ./homework.exe {question_number} /common/contrib/classroom/inf503/hw_dataset.fa
where question_number is { 1, 2, 3, 4, 5 }
Example: for question 3
> ./homework.exe 3 /common/contrib/classroom/inf503/hw_dataset.fa

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
where question_number is { 1, 2, 3, 4, 5 }
Example: for question 3
> sbatch q3.sh

################################################################################
***** Note ********
################################################################################
I have used exactly 36 million data from the dataset for questions 2, 4, and 5 instead of 36220411 (36 million approximate).