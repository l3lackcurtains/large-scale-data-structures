output : homework.o fastaDAT.o
	g++ -o homework homework.o fastaDAT.o

homework.o : homework.cpp 
	g++ -c homework.cpp -O3

fastaDAT.o : fastaDAT.cpp fastaDAT.h 
	g++ -c fastaDAT.cpp -O3

clean:	
	rm -rf *.o homework