CC = gcc
RM = rm -f 

objects = server client

all: $(objects)

$(objects): %: %.c
	$(CC) -o $@ $<

clean: 
	$(RM) $(objects)
