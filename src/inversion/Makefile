.PHONY: inversion

inversion: $(OBJ_DIR)/inversion.o  $(OBJ_DIR)/kd_tree.o $(OBJ_DIR)/table.o
	$(CC) $^ -o $(BIN_DIR)/inversion -L$(LIB_DIR) -limage -lm

$(OBJ_DIR)/inversion.o: $(INVERSION_DIR)/inversion.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@
	
$(OBJ_DIR)/kd_tree.o: $(KD_DIR)/kd_tree.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(OBJ_DIR)/table.o: $(TABLE_DIR)/table.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@


	

