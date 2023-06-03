SRCDIR = src
OBJDIR = obj

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJS_TEST = $(filter-out $(OBJDIR)/main.o, $(OBJS))

CC = gcc
CFLAGS = -I./$(SRCDIR) -I./$(SRCDIR)/lexer -I./$(SRCDIR)/token -I./$(SRCDIR)/helpers

.PHONY: all clean

all: test main

test: $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ -o run_tests

main: $(OBJDIR)/main.o $(OBJDIR)/lexer/lexer.o $(OBJDIR)/token/actions.o $(OBJDIR)/token/mappers.o $(OBJDIR)/helpers/characters.o
	$(CC) $(CFLAGS) $^ -o program

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/lexer/%.o: $(SRCDIR)/lexer/%.c $(wildcard $(SRCDIR)/lexer/*.h)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/token/%.o: $(SRCDIR)/token/%.c $(wildcard $(SRCDIR)/token/*.h)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/helpers/%.o: $(SRCDIR)/helpers/%.c $(wildcard $(SRCDIR)/helpers/*.h)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) run_tests program
