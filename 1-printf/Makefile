SRC_ASM_EXT = .nasm
SRC_C_EXT   = .c

SRC_ASM = ./src_asm
SRC_C   = ./src_c
OBJ_ASM = ./obj_asm
OBJ_C   = ./obj_c
BIN     = ./bin
LST     = ./lst
OUT     = $(BIN)/prog

SOURCES_ASM 	= $(wildcard $(SRC_ASM)/*$(SRC_ASM_EXT))
OBJFILES_ASM    = $(patsubst $(SRC_ASM)/%,$(OBJ_ASM)/%,$(SOURCES_ASM:$(SRC_ASM_EXT)=.o))

SOURCES_C 		= $(wildcard $(SRC_C)/*$(SRC_C_EXT))
OBJFILES_C    	= $(patsubst $(SRC_C)/%,$(OBJ_C)/%,$(SOURCES_C:$(SRC_C_EXT)=.o))

$(OUT) : $(OBJFILES_ASM) $(OBJFILES_C)
	gcc -o $@ -no-pie $^

$(OBJ_ASM)/%.o : $(SRC_ASM)/%$(SRC_ASM_EXT)
	nasm -f elf64 -o $@ -l $(LST)/$@.lst $<

$(OBJ_C)/%.o : $(SRC_C)/%$(SRC_C_EXT)
	gcc -Wall -o $@ -c $<

.PHONY: clean_all
clean_all:
	rm -f $(OBJFILES_ASM) $(OBJFILES_C) $(OUT) $(LST)/$(OBJ_C)/* $(LST)/$(OBJ_ASM)/*

