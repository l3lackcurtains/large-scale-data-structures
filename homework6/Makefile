output : homework.o suffixTrie.o suffixTree.o
	g++ -o homework homework.o suffixTrie.o suffixTree.o -std=c++11

homework.o: homework.cpp suffixTrie.h suffixTree.h
	g++ -c homework.cpp -O3 -std=c++11

suffixTrie.o: suffixTrie.cpp suffixTrie.h
	g++ -c suffixTrie.cpp -O3 -std=c++11

suffixTree.o: suffixTree.cpp suffixTree.h
	g++ -c suffixTree.cpp -O3 -std=c++11

clean:	
	rm -rf *.o homework