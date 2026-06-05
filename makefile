CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

BUILD = build

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=$(BUILD)/%.o)

RUN = run
ASM = assemble

all: $(RUN) $(ASM)

$(RUN): $(BUILD)/run.o $(BUILD)/VM.o $(BUILD)/memory.o
	$(CC) $^ -o $@


$(ASM): $(BUILD)/assemble.o
	$(CC) $^ -o $@


$(BUILD)/%.o: src/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(RUN) $(ASM)