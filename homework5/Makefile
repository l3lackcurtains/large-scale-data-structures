output : homework.o prefixTrie.o
	g++ -o homework homework.o prefixTrie.o -std=c++11

homework.o: homework.cpp prefixTrie.h
	g++ -c homework.cpp -O3 -std=c++11

prefixTrie.o: prefixTrie.cpp prefixTrie.h
	g++ -c prefixTrie.cpp -O3 -std=c++11

clean:	
	rm -rf *.o homework