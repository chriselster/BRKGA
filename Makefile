CFLAGS =-std=c++17  -pthread -fsanitize=undefined -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef  -Wno-unused
CC = g++
CPPDIR = src\Entities
INCDIR = src\Headers

ODIR = obj
CPPFILES = $(wildcard $(CPPDIR)\*.cpp)
INCFILES = $(wildcard $(INCDIR)\*.hpp)
OBJFILES = $(notdir $(CPPFILES:.cpp=.o))
OBJFILES_WITH_PATH = $(patsubst %,$(ODIR)\%,$(OBJFILES))

$(ODIR)\%.o: $(CPPDIR)\%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) -I $(INCDIR)

# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory

SOURCEDIR = src
BUILDDIR = bin

# Name of the final executable
TARGET = main

# Decide whether the commands will be shwon or not+
VERBOSE = TRUE

# Create the list of directories
DIRS = $(wildcard $(SOURCEDIR)/*)
SOURCEDIRS = $(DIRS)
TARGETDIRS = $(foreach dir, $(DIRS), $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCEDIRS)))

# Generate the GCC includes parameters by adding -I before each source folder
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I , $(dir)))

# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)

# Create a list of *.cpp sources in DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)\*.cpp))

# Define objects for all sources
OBJS = $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)



# OS specific part
ifeq ($(OS),Windows_NT)
	RM = del /F /Q 
	RMDIR = -RMDIR /S /Q
	MKDIR = -mkdir
	ERRIGNORE = 2>NUL || true
	SEP=\\
else
	RM = rm -rf 
	RMDIR = rm -rf 
	MKDIR = mkdir -p
	ERRIGNORE = 2>/dev/null
	SEP=/
endif

# Remove space after separator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1)\%.o: %.cpp
	@echo Building $$@
	$(HIDE)$(CC) $(CFLAGS) -g -c  $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD $(CXXFLAGS)
endef

.PHONY: all clean directories 


all: CFLAGS += $(ADVANCEDFLAGS)
all: CFLAGS += -O3
all: directories
all: $(TARGET)
all: move

directories: 
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)



test: CFLAGS += -g -DDEBUG
test: aloca

$(TARGET): $(OBJS)
	$(HIDE)echo Linking $@ 
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -g -o $(TARGET)

move:
	mv main Example\\

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))


# aloca: $(OBJFILES_WITH_PATH)
# 	$(CC) src/main.cpp $(OBJFILES_WITH_PATH) $(CFLAGS) -I $(INCDIR) -o main
# 	

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo Cleaning done ! 

# clean:
# 	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
