output : homework.o fastaDAT.o fastaHT.o
	g++ -o homework homework.o fastaDAT.o fastaHT.o

homework.o : homework.cpp 
	g++ -c homework.cpp -O3

fastaDAT.o : fastaDAT.cpp fastaDAT.h 
	g++ -c fastaDAT.cpp -O3

fastaHT.o : fastaHT.cpp fastaHT.h 
	g++ -c fastaHT.cpp -O3

clean:	
	rm -rf *.o homework