BIN := test
OBJ := main.o add_ab.o delete_ab.o search_ab.o search_all.o
SRC := main.c add_ab.c delete_ab.c search_ab.c search_all.c

$(BIN): $(OBJ)
	gcc $(OBJ) -o $(BIN)
	
$(OBJ): $(SRC)
	gcc $(SRC) -c
