# Makefile для проекта tpmp-lab2-task4

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCSDIR = docs

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/file_processor

.PHONY: all clean dirs test docs

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

test: $(TARGET)
	@echo "Running tests..."
	@./run_tests.sh

docs:
	@echo "Documentation can be found in $(DOCSDIR)/report.md"
