all : histogram 

histogram : main.cpp Histogram.cpp
	g++ main.cpp Histogram.cpp -o histogram
debug:
	g++ -g -DDEBUG main.cpp Histogram.cpp -o histogram
del :
	rm histogram

