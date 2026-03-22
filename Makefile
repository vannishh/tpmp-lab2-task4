# Makefile для проекта tpmp-lab2-task4

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCSDIR = docs
DATADIR = data

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/customer_processor

.PHONY: all clean dirs test docs

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DATADIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(DATADIR)

test: $(TARGET)
	@chmod +x run_tests.sh
	@./run_tests.sh

docs:
	@echo "Documentation can be found in $(DOCSDIR)/report.md"

run: $(TARGET)
	@./$(TARGET)
