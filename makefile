CC = g++ 
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
TARGET = $(TARGETDIR)/exec
HEADERSDIR = include

SOURCES = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/% , $(SOURCES:.cpp=.o))
HEADERS =  $(shell find $(HEADERSDIR) -type f -name *.h)
CFLAGS = -std=c++14 -g
INC = -I $(HEADERSDIR)

$(TARGET): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET)



.PHONY: clean