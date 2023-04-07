CXXFLAGS =-std=c++17  -pthread -fsanitize=undefined -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef  -Wno-unused

CXX = g++
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

# Lista de arquivos de cabeçalho
HEADERS = $(wildcard $(SRCDIR)/Headers/*.hpp)

# Lista de arquivos de implementação
ENTITIES = $(wildcard $(SRCDIR)/Entities/*.cpp)

# Lista de objetos
OBJS = $(ENTITIES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Nome do executável
TARGET = $(BINDIR)/app

all: $(TARGET)

$(TARGET): $(OBJS) $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I./srd/Headers -o $@ $^ -g

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -I./src/Headers -c -o $@ $< -g

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
