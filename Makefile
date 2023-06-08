SRCDIR = src
OBJDIR = obj

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
EXCLUDES = $(shell find ./src/**/*_test.c)

TEST_SRCS = $(filter-out $(SRCDIR)/main.c, $(SRCS))
TEST_OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(TEST_SRCS))

PROD_SRCS = $(filter-out $(EXCLUDES), $(SRCS))
PROD_OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(PROD_SRCS))

CC = gcc
CFLAGS = -I./$(SRCDIR)

.PHONY: all clean test dev

all: test dev

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o run_tests
	trap 'rm -rf ./run_tests' EXIT; ./run_tests

dev: $(PROD_OBJS)
	$(CC) $(CFLAGS) $^ -o program

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) run_tests program
