CXXFLAGS =-std=c++17  -pthread -fsanitize=undefined -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef  -Wno-unused
OPTIMIZATION = 
CXXFLAGS += $(OPTIMIZATION)
CXX = g++
SRCDIR = src
OBJDIR = obj
BINDIR = bin

HEADERS = $(wildcard $(SRCDIR)/Headers/*.hpp)
ENTITIES = $(wildcard $(SRCDIR)/Entities/*.cpp)
OBJS = $(ENTITIES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


TARGET = $(BINDIR)/app

all: $(TARGET)

$(TARGET): $(OBJS) $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(OTIMIZATION_FLAGS)  -o $@ $^ -g

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OTIMIZATION_FLAGS) -I ./src/Headers -c -o $@ $< -g

solution: $(OBJS) $(SRCDIR)/solutionValidator.cpp
	$(CXX) $(CXXFLAGS) $(OTIMIZATION_FLAGS) -I ./src/Headers -o $@ $^ -g

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean


build_test: $(OBJS)
	$(CXX) $(CXXFLAGS) /src/tests/Carrier_test.cpp /src/tests/obj/catch_amalgamated.o  /obj/Entities/Point.o /obj/Entities/Carrier.o /obj/Entities/Client.o /obj/Entities/Vehicle.o /obj/Entities/Item.o  -g -o /carrier_test
	$(CXX) $(CXXFLAGS) /src/tests/TSPInstance_test.cpp /src/tests/obj/catch_amalgamated.o /obj/Entities/Point.o /obj/Entities/Carrier.o /obj/Entities/Client.o /obj/Entities/TSPInstance.o /obj/Entities/Vehicle.o /obj/Entities/Item.o  -g -o /instance_test
	$(CXX) $(CXXFLAGS) /src/tests/Vehicle_test.cpp /src/tests/obj/catch_amalgamated.o /obj/Entities/Point.o /obj/Entities/Carrier.o /obj/Entities/Client.o /obj/Entities/TSPInstance.o /obj/Entities/Vehicle.o /obj/Entities/Item.o  -g -o /vehicle_test


test: build_test
	mv /instance_test /src/tests/in/
	/carrier_test
	/vehicle_test
	/src/tests/in/instance_test

