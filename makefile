CC = g++ 
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
EXEC = exec
LIB = pokerlib.so
PYTHONDIR = gui

HEADERSDIR = include

SOURCES = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/% , $(SOURCES:.cpp=.o))
HEADERS =  $(shell find $(HEADERSDIR) -type f -name *.h)
CFLAGS = -std=c++14 -g -fpic 
LIB_LINK_FLAGS = -shared -lboost_python3
EXEC_LINK_FLAGS = 

INC = -I $(HEADERSDIR)

all: $(EXEC) $(LIB)

$(EXEC): $(filter-out $(BUILDDIR)/BoostWrap.o,$(OBJECTS))
	$(CC) $^ $(EXEC_LINK_FLAGS) -o $(TARGETDIR)/$(EXEC)
	
$(LIB): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ $(LIB_LINK_FLAGS) -o $(TARGETDIR)/$(LIB)
	cp $(TARGETDIR)/$(LIB) $(PYTHONDIR)/$(LIB)

$(BUILDDIR)/BoostWrap.o:  $(SRCDIR)/BoostWrap.cpp $(HEADERS)
	echo $(CPP_INCLUDE_PATH)
	mkdir -p $(BUILDDIR) 
	$(CC) $(CFLAGS) -I/usr/include/python3.5 $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: clean