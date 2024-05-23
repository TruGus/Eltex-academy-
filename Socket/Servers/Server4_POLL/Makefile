BIN := server
BIN1 := client_udp
BIN2 := client_tcp
LIB := function.h
SRC := Server_inet_udp.c
SRC1 := client_inet_udp.c
SRC2 := client_inet_tcp.c

server:
$(BIN): $(SRC)
	gcc $(SRC) $(LIB) -o $(BIN) 

client_udp:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(LIB) -o $(BIN1)  

client_tcp:
$(BIN2): $(SRC2)
	gcc $(SRC2) $(LIB) -o $(BIN2)