#make all nebo make vytvoří veškeré výstupy, generované ze zdrojového kódu.
#make compile vytvoří binární podobu semestrální práce, výsledek bude uložen do souboru <login>/<login>.
#make run spustí binární podobu semestrální práce.
#make clean smaže všechny vygenerované soubory a uvede adresář <login> do původního stavu.
#make doc vytvoří dokumentaci do adresáře <login>/doc. Dokumentaci musíte vytvořit pomocí programu doxygen, berte to jako výhodu a zkuste dokumentaci uplatnit v předmětu TED. Dokumentaci můžete vygenerovat P
GXX = g++


all: dir compile doc

dir:
	mkdir -p ./src/obj/

CGame.o: ./src/CGame.hpp ./src/CGame.cpp ./src/Player.hpp ./src/Connection.hpp ./src/STurn.hpp ./src/CGameBoard.cpp 
	$(GXX) -ggdb -c ./src/CGame.cpp -o ./src/obj/CGame.o 

CGameBoard.o: ./src/CGameBoard.hpp ./src/CGameBoard.cpp ./src/STurn.hpp 
	$(GXX) -ggdb -c ./src/CGameBoard.cpp -o ./src/obj/CGameBoard.o 

Player.o: ./src/Player.hpp ./src/Player.cpp ./src/Minimax.cpp ./src/CGameBoard.hpp ./src/STurn.hpp ./src/Minimax.cpp
	$(GXX) -ggdb -c ./src/Player.cpp -o ./src/obj/Player.o 

STurn.o: ./src/STurn.hpp  ./src/STurn.cpp
	$(GXX) -ggdb -c ./src/STurn.cpp -o ./src/obj/STurn.o 

Connection.o: ./src/Connection.hpp ./src/Connection.cpp
	$(GXX) -ggdb -c ./src/Connection.cpp -o ./src/obj/Connection.o 	

compile: dir CGame.o CGameBoard.o Player.o STurn.o Connection.o
	$(GXX) -ggdb src/obj/CGame.o src/obj/CGameBoard.o src/obj/Player.o src/obj/STurn.o src/obj/Connection.o -o simactom -Wall -pedantic -Wno-long-long -O0 -ggdb -lncurses

run: simactom
	./simactom

clean: 
	rm -f simactom
	rm -rf ./src/obj
	rm -rf ./doc

doc: ./src/Documentation ./src/Doxytitle.hpp ./src/CGame.hpp ./src/Connection.hpp ./src/Player.hpp ./src/CGameBoard.hpp ./src/STurn.hpp
	doxygen ./src/Documentation

count: 
		wc -l ./src/CGame.hpp ./src/CGame.cpp ./src/CGameBoard.hpp ./src/CGameBoard.cpp ./src/Player.cpp ./src/Player.hpp ./src/STurn.hpp ./src/STurn.cpp ./src/Connection.hpp ./src/Connection.cpp ./src/Minimax.cpp Makefile ./src/Documentation
