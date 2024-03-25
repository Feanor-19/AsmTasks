SRC_ASM_EXT = .nasm

SRC_ASM = ./src_asm
SRC_C   = ./src_c
OBJ     = ./obj
BIN     = ./bin
LST     = ./lst
OUT     = $(BIN)/prog

SOURCES_ASM 	= $(wildcard $(SRC_ASM)/*$(SRC_ASM_EXT))
OBJFILES_ASM    = $(patsubst $(SRC_ASM)/%,$(OBJ)/%,$(SOURCES_ASM:$(SRC_ASM_EXT)=.o))

$(OUT) : $(OBJFILES_ASM)
	ld -s -o $@ $^

$(OBJ)/%.o : $(SRC_ASM)/%$(SRC_ASM_EXT)
	nasm -f elf64 -o $@ -l $(LST)/$@.lst $<

.PHONY: clean_all
clean_all:
	rm -f $(OBJFILES_ASM) $(OUT) $(LST)/$(OBJ)/*

