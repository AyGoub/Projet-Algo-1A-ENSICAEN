.PHONY: test_kdtree

test_kdtree: $(OBJ_DIR)/kd_tree.o $(OBJ_DIR)/test_kd_tree.o $(OBJ_DIR)/table.o
	$(CC) $^ -o $(BIN_DIR)/test_kd_tree -L$(LIB_DIR) -limage -lm

$(OBJ_DIR)/kd_tree.o: $(KD_DIR)/kd_tree.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(OBJ_DIR)/test_kd_tree.o: $(KD_TEST_DIR)/test_kd_tree.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
	
$(OBJ_DIR)/table.o: $(TABLE_DIR)/table.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
	

