BIN := server
BIN1 := client
LIB := function.h
SRC := Server_inet_udp.c
SRC1 := Client_raw_udp.c
SRC1.1 := create_udp.c
SRC1.2 := create_ip.c
SRC1.3 := create_ethernet.c

server:
$(BIN): $(SRC)
	gcc $(SRC) -o $(BIN) 

client:
$(BIN1): $(SRC1)
	gcc $(SRC1) $(SRC1.1) $(SRC1.2) $(SRC1.3) -o $(BIN1) $(LIB)


