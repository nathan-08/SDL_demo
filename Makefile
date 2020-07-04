INCLUDE := -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers

FOLDER := -F/Library/Frameworks

FW := -framework SDL2 -framework SDL2_image -framework SDL2_ttf

main: main.o LTexture.o
	g++ -o main main.o LTexture.o $(INCLUDE) $(FW) $(FOLDER)

main.o: main.cpp LTexture.h
	g++ -c main.cpp $(INCLUDE)

LTexture.o: LTexture.cpp LTexture.h
	g++ -c LTexture.cpp $(INCLUDE)
