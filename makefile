
CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Woverride-init -Wunused-variable
INC = -Ic:\sdl2\i686-w64-mingw32\include\sdl2
LIBDIR = -Lc:\sdl2\i686-w64-mingw32\lib
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lopengl32

TARGET   = stark
SRCDIR   = src
OBJDIR   = obj
BUILDDIR = $(TARGET)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

SOURCES = $(wildcard ./src/*.c)
OBJ = $(wildcard ./obj/*.o)

$(TARGET): prepare $(OBJECTS)
	@$(CC) -o $(BUILDDIR)\$@ $(OBJ) $(LDFLAGS) $(LIBDIR)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

prepare:
	@cmd /c if not exist $(OBJDIR) md $(OBJDIR)
	@cmd /c if not exist $(BUILDDIR) md $(BUILDDIR)

.PHONY: clean
clean:
	@cmd /c del /f $(BUILDDIR)\$(TARGET).exe $(OBJDIR)\\*.o
	@cmd /c rd $(OBJDIR)
	@echo "Cleanup complete!"


