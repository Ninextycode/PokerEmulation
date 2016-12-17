CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGETDIR = bin
TARGET := $(TARGETDIR)/exec
 
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/% , $(SOURCES:.cpp=.o))
CFLAGS := -std=c++14
INC := -I include

$(TARGET): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET)



.PHONY: clean