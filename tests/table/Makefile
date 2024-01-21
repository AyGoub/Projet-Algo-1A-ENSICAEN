.PHONY: test_table

test_table: $(OBJ_DIR)/table.o $(OBJ_DIR)/test_table.o
	$(CC) $^ -o $(BIN_DIR)/test_table -L$(LIB_DIR) -limage -lm

$(OBJ_DIR)/table.o: $(TABLE_DIR)/table.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(OBJ_DIR)/test_table.o: $(TABLE_TEST_DIR)/test_table.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
