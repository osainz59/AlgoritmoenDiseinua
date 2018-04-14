all: pd
	./test

pd:  test.cpp PD.cpp BT.cpp
	g++ -std=c++11 -o test test.cpp PD.cpp BT.cpp

clean:
	rm -f test
