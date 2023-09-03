N_Queens: main.cpp
	g++ main.cpp -o N_Queens

clean:
	rm N_Queens

run: N_Queens
	./N_Queens
