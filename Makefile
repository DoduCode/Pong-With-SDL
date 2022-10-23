all:
	g++ -c src/*.cpp -std=c++20 -g -Wall  -I include -I C:/Users/Ramesh/Pandu/SDL/SDL-2.24.0/SDL2-2.24.0/x86_64-w64-mingw32/include && g++ *.o -o bin/debug/main -L C:/Users/Ramesh/Pandu/SDL/SDL-2.24.0/SDL2-2.24.0/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && start bin/debug/main

# Build Release
# all:
# 	g++ -c src/*.cpp -std=c++20 -O3 -Wall -m64 -I include -I C:/Users/Ramesh/Pandu/SDL/SDL-2.24.0/SDL2-2.24.0/x86_64-w64-mingw32/include && g++ *.o -o bin/release/main -s -L C:/Users/Ramesh/Pandu/SDL/SDL-2.24.0/SDL2-2.24.0/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && start bin/release/main
