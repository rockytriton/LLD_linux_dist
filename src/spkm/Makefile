
all: spkm

CFLAGS=-I../include

H_DEPS = $(wildcard ../include/lldos/*.h)

obj/shared/%.o: ../shared/%.c $(H_DEPS)
	mkdir -p $(@D)
	gcc -c -o $@ $< $(CFLAGS)

obj/%.o: ./%.c  $(H_DEPS)
	gcc -c -o $@ $< $(CFLAGS)

SPKM_FILES = $(wildcard ./*.c)
SHARED_FILES = $(wildcard ../shared/*.c)
OBJ_FILES = $(SHARED_FILES:../shared/%.c=obj/shared/%.o)
OBJ_FILES += $(SPKM_FILES:./%.c=obj/%.o)

spkm: $(OBJ_FILES)
	gcc -o ./spkm $(OBJ_FILES) -lyaml -lcurl 

clean:
	rm -f spkm
	rm -rf obj
