CC = g++
CFLAGS = -Wall -Wextra

SRCDIR = ./src
FILES = main drawable_objects
BUILDDIR = ./build
BINDIR = ./release
DEPS= -lGL -lGLU -lglut

OBJS = $(addsuffix .o, $(addprefix $(BUILDDIR)/, $(FILES)))

$(BINDIR)/flappy_teapot: $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(DEPS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

run: $(BINDIR)/flappy_teapot
	$(BINDIR)/flappy_teapot
