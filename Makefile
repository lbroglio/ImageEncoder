imageSten: imageIO.o main.o
	g++ -ggdb -Wall -Werror imageIO.o main.o -o imageSten

imageIO.o: imageIO.cpp imageData.h
	g++ -ggdb -Wall -Werror imageIO.cpp -c

main.o: main.cpp imageData.h
	g++ -ggdb -Wall -Werror main.cpp -c

clean:
	rm imageIO.o main.o imageSten