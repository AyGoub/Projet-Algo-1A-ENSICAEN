# Tools
CC              =gcc
DOXYGEN	        =doxygen
RM              =rm -f
# Macros for directories
SRC_DIR         =./src
TEST_DIR        =./tests
OBJ_DIR	        =./obj
TABLE_TEST_DIR =$(TEST_DIR)/table
KD_TEST_DIR     =$(TEST_DIR)/kd_tree
TABLE_DIR      =$(SRC_DIR)/table
TRIVIALE_DIR     =$(SRC_DIR)/triviale
KD_DIR 	        =$(SRC_DIR)/kd_tree
IMAGE_DIR       =$(SRC_DIR)/image
INVERSION_DIR   =$(SRC_DIR)/inversion
BIN_DIR	        =./bin
INC_DIR	        =./include
LIB_DIR	        =./lib
DOC_DIR	        =./doc
DOXYFILEPATH  = $(DOC_DIR)/Doxyfile_Projet
# Compilation flags
CPPFLAGS        =-I$(INC_DIR)
CFLAGS	        =-Wall -Wextra -O2 -g

.PHONY: all tests clean doc distclean docclean

all: libimage triviale inversion

tests: test_table test_kdtree 

include $(IMAGE_DIR)/Makefile
include $(TABLE_TEST_DIR)/Makefile
include $(KD_TEST_DIR)/Makefile
include $(TRIVIALE_DIR)/Makefile
include $(INVERSION_DIR)/Makefile

clean: 
	$(RM) $(OBJ_DIR)/*.o
	
distclean: clean docclean
	$(RM) $(BIN_DIR)/*
	$(RM) $(LIB_DIR)/*

doc:
	$(DOXYGEN) $(DOXYFILEPATH)
	
docclean:
	$(RM) -r $(DOC_DIR)/inversion




