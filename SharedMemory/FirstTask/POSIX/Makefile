BIN := server
BIN1 := client
SRC := server.c
SRC1 := client.c

server:
$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN) -lrt -pthread

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) -o $(BIN1)  -lrt -pthread

	
