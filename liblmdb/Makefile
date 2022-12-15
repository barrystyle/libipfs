CC=gcc

CFLAGS= -O2 -I./include -Wno-stringop-overflow
LDFLAGS= -lpthread -lm

SOURCES= \
	src/mdb.c \
	src/mdb_copy.c \
	src/mdb_drop.c \
	src/mdb_dump.c \
	src/mdb_load.c \
	src/mdb_stat.c \
	src/midl.c

OBJECTS=$(SOURCES:.c=.o)
OUTPUT=liblmdb.a

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	ar rc $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.a
	rm -f */*.o
	rm -f */*/*.o
