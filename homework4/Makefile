output : homework.o smithWaterman.o blast.o
	g++ -o homework homework.o smithWaterman.o blast.o -std=c++11

homework.o: homework.cpp smithWaterman.h blast.h
	g++ -c homework.cpp -O3 -std=c++11

smithWaterman.o: smithWaterman.cpp smithWaterman.h
	g++ -c smithWaterman.cpp -O3 -std=c++11

blast.o: blast.cpp blast.h smithWaterman.h
	g++ -c blast.cpp -O3 -std=c++11

clean:	
	rm -rf *.o homework