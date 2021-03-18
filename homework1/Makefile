output : homework.o fasta.o
	g++ -o homework homework.o fasta.o

homework.o : homework.cpp 
	g++ -c homework.cpp -O3

fasta.o : fasta.cpp fasta.h 
	g++ -c fasta.cpp -O3

clean:	
	rm -rf *.o homework