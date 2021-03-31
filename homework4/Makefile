output : homework.o smithWaterman.o blast.o
	g++ -o homework homework.o smithWaterman.o blast.o

homework.o: homework.cpp smithWaterman.h blast.h
	g++ -c homework.cpp -O3

smithWaterman.o: smithWaterman.cpp smithWaterman.h
	g++ -c smithWaterman.cpp -O3

blast.o: blast.cpp blast.h smithWaterman.h
	g++ -c blast.cpp -O3

clean:	
	rm -rf *.o homework