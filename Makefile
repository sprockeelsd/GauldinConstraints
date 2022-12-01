all:macOS

macOS:
	g++ -std=c++11 -F/Library/Frameworks -c Utilities.cpp Gauldin_csts.cpp Main.cpp

	g++ -std=c++11 -F/Library/Frameworks -framework gecode -o Main Utilities.cpp Gauldin_csts.cpp Main.cpp

	./Main

clean:
	rm -f *.o Main