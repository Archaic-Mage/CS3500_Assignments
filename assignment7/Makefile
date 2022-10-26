GC = g++
RM = rm -rf

all: algorithm.cpp
	$(GC) -o algorithm algorithm.cpp

clean: 
	$(RM) algorithm ./csv/*.csv ./output/*.out

run1:
	./algorithm

plot:
	python3 plot.py

run:
	bash run.sh