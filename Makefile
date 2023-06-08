SRCDIR = src
OBJDIR = obj

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
EXCLUDES = $(shell find ./src/**/*_test.c ./src/**/*_test.h)

DEV_SRCS = $(filter-out $(EXCLUDES) $(SRCDIR)/main_test.c, $(SRCS))
DEV_OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(DEV_SRCS))

TEST_SRCS = $(filter-out $(SRCDIR)/main.c, $(SRCS))
TEST_OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(TEST_SRCS))

CC = gcc
CFLAGS = -I./$(SRCDIR)

.PHONY: all clean test dev

all: test dev

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o tests
	trap 'rm -rf ./tests' EXIT; ./tests

dev: $(DEV_OBJS)
	$(CC) $(CFLAGS) $^ -o program

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) tests program
