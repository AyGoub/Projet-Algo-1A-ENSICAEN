.PHONY: triviale

triviale: $(OBJ_DIR)/triviale.o  $(OBJ_DIR)/table.o
	$(CC) $^ -o $(BIN_DIR)/triviale -L$(LIB_DIR) -limage -lm

$(OBJ_DIR)/triviale.o: $(TRIVIALE_DIR)/triviale.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
	
$(OBJ_DIR)/table.o: $(TABLE_DIR)/table.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
	

