BUILD_DIR = build
INC_DIR = inc
SRC_DIR = src

COMMON_SRC = $(SRC_DIR)/sm4.c $(SRC_DIR)/benchmark.c

all: sm4 sm4_cbc

sm4: $(COMMON_SRC) $(SRC_DIR)/test_sm4.c
	gcc -Wall -Wextra -O3 -funroll-loops -march=native \
		-I$(INC_DIR) $^ \
		-o $(BUILD_DIR)/$@

sm4_cbc: $(COMMON_SRC) $(SRC_DIR)/test_sm4_cbc.c
	gcc -Wall -Wextra -O3 -funroll-loops -march=native \
		-I$(INC_DIR) $^ \
		-o $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/*
