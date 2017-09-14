TARGET = mdiscovery
CC = gcc 

CFLAGS = -Wall -o2 -I . -I include/
LINK_FLAG = -L ./libs 

SRCS = $(wildcard *.c)
OBJS = $(patsubst %c, %o, $(SRCS))

.PHONY: ALL clean 

ALL:$(TARGET)
    
$(TARGET):$(OBJS) 
	@$(CC) $(OBJS) $(LINK_FLAG) -o $@ 

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
   
clean:
	@rm -rf *.o 
	@rm -rf $(TARGET)  
