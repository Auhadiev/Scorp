CXX = gcc
CXXFLAGS = -c -Ih_files

EXE = my_paint
SRCDIR = ./src
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -lpng -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ -lpng $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all
