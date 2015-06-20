SOURCES = $(wildcard *.cpp util/*.cpp)
HEADERS = $(wildcard *.h util/*.h)
OBJECTS = $(SOURCES:%.cpp=%.o)
CFLAGS  = -std=c++11 -O2 -march=native
LFLAGS  = -O2 -march=native
TARGET  = ms

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o *~ util/*.o util/*~ $(TARGET)