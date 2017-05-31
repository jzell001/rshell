CXX=g++
CXXFLAGS:= -g -Wall -Werror -ansi -pedantic
SOURCES= main.cpp Base.cpp
OBJS=$(patsubst %.cpp,bin/%.o,$(SOURCES))
VPATH=src
EXECUTABLE=bin/rshell


all: bin $(EXECUTABLE)

bin:
		mkdir -p bin

$(EXECUTABLE): $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $@

bin/%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
		rm -f $(EXECUTABLE) $(OBJS) *.gch
		rm -r bin