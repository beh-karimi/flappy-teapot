CC = g++
CFLAGS = -Wall -Wextra

SRCDIR = ./src
FILES = main drawable_objects
BUILDDIR = ./build
BINDIR = ./release
DEPS= -lGL -lGLU -lglut

OBJS = $(addsuffix .o, $(addprefix $(BUILDDIR)/, $(FILES)))

$(BINDIR)/flappy_teapot: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(DEPS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

run: $(BINDIR)/flappy_teapot
	$(BINDIR)/flappy_teapot
