all:macOS

macOS:
	g++ -std=c++11 -F/Library/Frameworks -c Gauldin_csts.cpp

	g++ -std=c++11 -F/Library/Frameworks -framework gecode -o GauldinCsts Gauldin_csts.cpp

	./GauldinCsts

clean:
	rm -f *.o