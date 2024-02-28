CPP_SOURCE = $(wildcard *.cpp)

H_SOURCE = $(wildcard *.h)

OBJ=$(CPP_SOURCE:.cpp=.o)

CXX=g++

CXX_FLAGS=-Wall -g -pg

TARGET=main.exe

all: $(TARGET)

$(TARGET): $(OBJ) $(H_SOURCE)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

clean:
	rm -rf *.o

 gprof: $(TARGET) 
	./$(TARGET)
	gprof $(TARGET) gmon.out > analysis.txt