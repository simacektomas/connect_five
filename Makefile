#make all nebo make vytvoří veškeré výstupy, generované ze zdrojového kódu.
#make compile vytvoří binární podobu semestrální práce, výsledek bude uložen do souboru <login>/<login>.
#make run spustí binární podobu semestrální práce.
#make clean smaže všechny vygenerované soubory a uvede adresář <login> do původního stavu.
#make doc vytvoří dokumentaci do adresáře <login>/doc. Dokumentaci musíte vytvořit pomocí programu doxygen, berte to jako výhodu a zkuste dokumentaci uplatnit v předmětu TED. Dokumentaci můžete vygenerovat P
GXX = g++

OBJ = src/obj/CGame.o \
      src/obj/CGameBoard.o \
      src/obj/Player.o \
      src/obj/STurn.o \
      src/obj/Connection.o \

all: compile doc

src/obj:
	mkdir -p ./src/obj/

src/obj/%.o: src/%.cpp src/%.hpp src/obj
	$(GXX) -ggdb -c $< -o $@

simactom: $(OBJ)
	$(GXX) -ggdb $(OBJ) -o $@ -Wall -pedantic -Wno-long-long -O0 -ggdb -lncurses

compile:  simactom
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
