BIN := server
BIN1 := client
LIB := function.h
SRC := Server_inet_udp.c
SRC1 := client_inet_udp.c

server:
$(BIN): $(SRC)
	gcc $(SRC) $(LIB) -o $(BIN) -lpthread

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(LIB) -o $(BIN1)  


