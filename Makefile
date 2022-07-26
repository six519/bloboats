# Released under GNU GPL version 2 except for a few datafiles.

### Installation options:
# These are the directories for `make install'
# NOTICE: Use absolute paths! ~ means $HOME, but ONLY for PRIVATEDIR.

### Installation directory (Installation prefix)
# If you don't have root privileges, set this to /home/tentacleman/bloboats/
# for example, otherwise /. Don't use ~ or other environment variables!
PREFIX = /

### Or if you don't want to run make install at all, uncomments the next line
# and comment the line below. Compile and run with './bin/bloboats'
#DATADIR = data

DATADIR = $(PREFIX)usr/games/bloboats/data

### If you do make install, you may perhaps want to set these
BINARYDIR = $(PREFIX)usr/bin
CONFIGDIR = $(PREFIX)etc

PRIVATEDIR = ~/.bloboats



### To compile, this program requires:
# SDL, SDL_image, SDL_mixer to compile. Libvorbis for music support.
# OpenGL support.

SOUND = 1
MUSIC = 1
DEBUG = 0

# Select target system
# Possible targets: DEFAULT (Linux and most of others too)
#                   FREEBSD
#                   NETBSD (use gmake)
#                   MACOSX (not sure if replay and ghost work)
#                   CROSS (for cross-compiling to win32)


#This should probably be DEFAULT
TARGET = DEFAULT


### Only some random settings below


# For compiling with an icon, set these

ICON = src/icon.o
ICON_CMD = i586-mingw32msvc-windres -i src/icon.rc -o $(ICON)


### C++ compiler to be used
CXX_DEFAULT = g++
CXX_FREEBSD = g++
CXX_NETBSD = g++
CXX_MACOSX = g++
CXX_CROSS = i586-mingw32msvc-g++

CXX = $(CXX_$(TARGET))


### SDL-Config in your system
SDLCONFIG_DEFAULT = sdl-config
SDLCONFIG_FREEBSD = sdl-config
SDLCONFIG_NETBSD = sdl-config
SDLCONFIG_MACOSX = sdl-config
SDLCONFIG_CROSS = i586-mingw32msvc-sdl-config

SDLCONFIG = $(SDLCONFIG_$(TARGET))

### Libs
LIBS_DEFAULT = `$(SDLCONFIG) --libs` -lSDL_image -lSDL_mixer -lGL -lGLU
LIBS_FREEBSD = `$(SDLCONFIG) --libs` -lSDL_image -lSDL_mixer -lGL -lGLU
LIBS_NETBSD = `$(SDLCONFIG) --libs` -lSDL_image -lSDL_mixer -lGL -lGLU -L/usr/pkg/lib
LIBS_MACOSX = `$(SDLCONFIG) --libs` -lSDL_image -lSDL_mixer -framework OpenGL
LIBS_CROSS = `$(SDLCONFIG) --libs` -lSDL_image -lSDL_mixer -lopengl32 -lglu32

LIBS = $(LIBS_$(TARGET))

### Binary path
BINARY_DEFAULT = bloboats
BINARY_FREEBSD = bloboats
BINARY_NETBSD = bloboats
BINARY_MACOSX = bloboats
BINARY_CROSS = bloboats.exe

BINARY = $(BINARY_$(TARGET))

### CXX-Flags
CXXFLAGS_DEFAULT = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY) -O2
CXXFLAGS_FREEBSD = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY) -O2
CXXFLAGS_NETBSD = -g `$(SDLCONFIG) --cflags` -O2 -I/usr/pkg/include
CXXFLAGS_MACOSX = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY) -O2
CXXFLAGS_CROSS = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY) -O2

CXXFLAGS = $(CXXFLAGS_$(TARGET))

### Stripping command
STRIP_DEFAULT = strip
STRIP_FREEBSD = strip
STRIP_NETBSD = strip
STRIP_MACOSX = strip
STRIP_CROSS = i586-mingw32msvc-strip

STRIP = $(STRIP_$(TARGET))


##########
# -fomit-frame-pointer -ffast-math


OBJ=src/main.o src/vec.o src/particle.o src/keyboard.o src/window.o src/mouse.o src/graphics.o src/wall.o src/spring.o \
src/model.o src/font.o src/compat.o src/level.o src/model_tex.o src/game.o src/menu.o \
src/menutext.o src/config.o src/player.o src/models/paatti.o src/models/canvas.o \
src/sound.o src/media.o src/path.o src/text.o src/models/hirvio.o src/models/invader.o \
src/water.o src/models/broken.o src/models/boulder.o src/element.o src/models/tux.o \
src/connection.o src/condition.o src/handler.o src/texfile.o

BINARY_DEFAULT_ = blobinv
BINARY_FREEBSD_ = blobinv
BINARY_NETBSD_ = blobinv
BINARY_MACOSX_ = blobinv
BINARY_CROSS_ = blobinv.exe
BINARY_ = $(BINARY_$(TARGET)_)
CXXFLAGS_DEFAULT_ = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY_) -O2
CXXFLAGS_FREEBSD_ = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY_) -O2
CXXFLAGS_NETBSD = -g `$(SDLCONFIG) --cflags` -O2 -I/usr/pkg/include
CXXFLAGS_MACOSX_ = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY_) -O2
CXXFLAGS_CROSS_ = -g `$(SDLCONFIG) --cflags` -o bin/$(BINARY_) -O2
CXXFLAGS_ = $(CXXFLAGS_$(TARGET)_)

all: config main

main: $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) $(LIBS) $(CXXFLAGS)
	$(STRIP) bin/$(BINARY)

icon:
	$(ICON_CMD)
	$(CXX) -o bin/$(BINARY) $(OBJ) $(ICON) $(LIBS)
	$(STRIP) bin/$(BINARY)

config:
	echo "datadir $(DATADIR)" >bloboats.dirs
	echo "privatedir $(PRIVATEDIR)" >>bloboats.dirs
	chmod 644 bloboats.dirs
	echo "#define DEFAULT_CONFIGFILE \"$(CONFIGDIR)/bloboats.dirs\"" >src/compiling_settings.h
	echo "#define SOUND $(SOUND)" >> src/compiling_settings.h
	echo "#define MUSIC $(MUSIC)" >> src/compiling_settings.h
	echo "#define DEBUG $(DEBUG)" >> src/compiling_settings.h

install:
	mkdir -p $(BINARYDIR)/
	mkdir -p $(CONFIGDIR)/
	cp bloboats.dirs $(CONFIGDIR)/
	mkdir -p $(DATADIR)/
	cp -R data/* $(DATADIR)/
	cp bin/$(BINARY) $(BINARYDIR)/
	chmod -R 744 $(DATADIR)
	chmod 755 `find $(DATADIR) -type d`

uninstall:
	rm -rf $(CONFIGDIR)/bloboats.dirs
	rm -rf $(DATADIR)/
	rm -rf $(BINARYDIR)/bloboats

gho: src/viewport.o
	$(CXX) src/viewport.o $(LIBS) $(CXXFLAGS_)
	$(STRIP) bin/$(BINARY_)

clean:
	rm -rf bloboats.dirs
	rm -rf src/*.o
	rm -rf src/models/*.o
	rm -rf bin/$(BINARY)
