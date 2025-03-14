CC = clang++
CCFLAGS = -Wall -Wextra -g -std=c++17

SRCDIR = .
OBJDIR = obj

HEADERS = arithmetic.h \
		  elliptic_curve.h \
		  ECDH.h \
		  breakingDLP/bruteforce.h \
		  breakingDLP/baby_giant_step.h \
		  breakingDLP/pollard_rho.h

SRCS = arithmetic.cc \
	   elliptic_curve.cc \
	   ECDH.cc \
	   breakingDLP/bruteforce.cc \
	   breakingDLP/baby_giant_step.cc \
	   breakingDLP/pollard_rho.cc \
	   main.cc

OBJS = $(patsubst %.cc,$(OBJDIR)/%.o,$(SRCS))

DLPOBJDIR = $(OBJDIR)/breakingDLP

TARGET = ecc

all: directories $(TARGET)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DLPOBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cc $(HEADERS)
	$(CC) $(CCFLAGS) -c $< -o $@

$(OBJDIR)/breakingDLP/%.o: breakingDLP/%.cc
	$(CC) $(CCFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)

help:
	@echo "Elliptic Curve Cryptography"
	@echo "make              - complie program"
	@echo "make run          - execute program"
	@echo "make clean        - clean .o and program"
	@echo "make help         - help"

.PHONY: all directories clean run help