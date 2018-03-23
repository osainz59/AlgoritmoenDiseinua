all: grafoa
	./test

grafoa:  test_Grafoa.cpp Grafoa.cpp Partiketa.cpp LehentasunIlara.cpp
	g++ -std=c++11 -o test test_Grafoa.cpp Grafoa.cpp Partiketa.cpp LehentasunIlara.cpp

clean:
	rm -f test
	rm -f kruskal_emaitza.txt
