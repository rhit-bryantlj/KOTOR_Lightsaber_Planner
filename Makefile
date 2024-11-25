CXX = g++
CXXFLAGS = -Wall -g

TARGET = main

# Source files
SRCS = main.cpp Lightsaber.cpp Attributes.cpp Crystal.cpp

# Object files
OBJS = $(SRCS: .cpp=.o)

# Default rule to build and run the executable
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm main.exe