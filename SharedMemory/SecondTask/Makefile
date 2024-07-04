BIN := server
BIN1 := client
SRC := server.c
SRC1 := client.c graphic.c
LIB := function.h -lncurses

server:
$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN) -lpthread

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(LIB) -o $(BIN1) -lpthread

	
