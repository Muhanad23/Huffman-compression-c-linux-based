hw1_p1: hw1_p1.o huffman.o
	g++ hw1_p1.o huffman.o -o hw1_p1

hw1_p1.o: hw1_p1.cpp
	g++ -c hw1_p1.cpp

huffman.o: huffman.cpp huffman.h
	g++ -c huffman.cpp

clean:
	rm *.o hw1_p1

