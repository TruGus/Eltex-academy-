BIN := server
BIN1 := client
LIB := function.h
SRC := Server_raw_udp.c
SRC1 := client_inet_udp.c

server:
$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN)

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(LIB) -o $(BIN1)  


