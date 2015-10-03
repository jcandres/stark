
CC = gcc

CFLAGS = -std=c99 -O3
CFLAGS = -std=c99 -pedantic -g -Wall -Wextra
INC = -Ic:\sdl2\include\sdl2
LIBDIR = -Lc:\sdl2\lib
#-mwindows in LDFLAGS gets rid of console (and console messages, even if run from debugger...)
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_ttf
#-lSDL2 goes AFTER all the -lSDL_xxx libraries
#LDFLAGS = -static -Lc:\sdl2\lib -lmingw32 -lSDL2main -lSDL2_mixer -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

TARGET  = stark
SRCDIR  = src
OBJDIR  = obj
BUILDDIR = $(TARGET)
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm    = rm -f

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


