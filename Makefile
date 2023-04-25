imageSten: imageIO.o main.o encodeDecode.o
	g++ -ggdb -Wall -Werror imageIO.o main.o encodeDecode.o -o imageSten

main.o: main.cpp imageData.h encodeDecode.h
	g++ -ggdb -Wall -Werror main.cpp -c

encodeDecode.o: encodeDecode.cpp imageData.h encodeDecode.h
	g++ -ggdb -Wall -Werror encodeDecode.cpp -c

imageIO.o: imageIO.cpp imageData.h
	g++ -ggdb -Wall -Werror imageIO.cpp -c

clean:
	rm imageIO.o main.o encodeDecode.o imageSten