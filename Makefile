CC= g++
APPNAME= ImageSten
FLAGS= -Wall -Werror
OBJECTS= bin/encodeDecode.o bin/imageIo.o bin/main.o

.PHONY: clean 

$(APPNAME): $(OBJECTS)
	$(CC) $^ $(FLAGS) -o $(APPNAME)


$(OBJECTS): bin/%.o : src/%.cpp bin
	$(CC) $(FLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

$(TEST_OBJECTS): bin/%.o : test/%.cpp bin
	$(CC) $(FLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

bin: 
	mkdir bin

clean:
	rm -rf bin 
