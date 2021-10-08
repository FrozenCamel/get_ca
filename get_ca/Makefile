TARGET=get_ca
CFLAGS:=-I./../openssl/include -L./../openssl/
HOST_PREFIX:=/toolchain/opt/peplink/20190104/armv7-peplink-linux-gnueabi/bin/
CROSS_COMPILE:=$(HOST_PREFIX)armv7-peplink-linux-gnueabi-
CC:= $(CROSS_COMPILE)gcc
LDLIBS:=-lssl -lcrypto
DESTDIR=./
#.PHONY: all clean

$(TARGET).o: $(TARGET).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS) 
        
clean:
	rm -f $(TARGET).o
install:
	install -d $(DESTDIR)$(PREFIX)lib/
	install -m 777 $(TARGET).o $(DESTDIR)$(PREFIX)lib/
