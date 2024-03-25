CC=g++

CFLAGS = 	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef 				\
			-Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 			\
			-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ 				\
			-Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion 		\
			-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2	 			\
			-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 			\
			-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo 		\
			-Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits 	\
			-Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -O3

OBJ = obj
SRC = src
BIN = bin
OUT = $(BIN)/mandelbrot

SOURCES 		= $(wildcard $(SRC)/*.cpp)
OBJFILES 		= $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.cpp=.o))

$(OUT) : $(OBJFILES)
	$(CC) -o $@ $(CFLAGS) $^ -lsfml-graphics -lsfml-window -lsfml-system

$(OBJ)/%.o : $(SRC)/%.cpp
	@$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)

.PHONY: run
run:
	$(OUT)