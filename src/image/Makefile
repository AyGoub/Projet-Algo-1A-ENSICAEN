.PHONY: libimage

libimage : $(OBJ_DIR)/image.o
	ar -rv $(LIB_DIR)/libimage.a $^

$(OBJ_DIR)/image.o : $(IMAGE_DIR)/image.c
	$(CC) $(CPPFLAGS) -o $@ $^ -c

   






