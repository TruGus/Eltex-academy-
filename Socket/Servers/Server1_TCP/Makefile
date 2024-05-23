BIN := server
BIN1 := client
SRC := Server_inet_tcp.c
SRC1 := client_inet_tcp.c
LIB := function.h

server:
$(BIN): $(SRC)
	gcc $(SRC) $(LIB) -o  $(BIN) -lpthread

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(LIB) -o $(BIN1)  


