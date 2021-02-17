output : homework.o fasta.o
	g++ -o homework.exe homework.o fasta.o

homework.o : homework.cpp 
	g++ -c homework.cpp

fasta.o : fasta.cpp fasta.h 
	g++ -c fasta.cpp

clean:	
	rm -rf *.o homework.exe