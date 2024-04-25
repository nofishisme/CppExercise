OUT := main
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
COM_OP := -Wall -g
CC := gcc

$(OUT):$(OBJS)
	$(CC) $^ -o $@
%.o : %.c
	gcc -c $< $(COM_OP)
.PHONY: clean rebuild
clean:
	rm -f $(OUT) $(OBJS)
rebuild: clean main
