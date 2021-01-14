all:
	g++ main.cpp -o SpaceFight2 -I/usr/include/SDL -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_net
	
clean:
	rm main.o SpaceFight2
