CC = gcc
CFLAGS = -fPIC -shared

LDLIBS_GLOBAL = -ldl -lpthread

LDLIBS_PER_THREAD = -ldl

TARGETS = libcache_gettimeofday_global.so libcache_gettimeofday_per_thread.so

all: $(TARGETS)

libcache_gettimeofday_global.so: cache_gettimeofday_global.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS_GLOBAL)

libcache_gettimeofday_per_thread.so: cache_gettimeofday_per_thread.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS_PER_THREAD)

clean:
	rm -f $(TARGETS)

.PHONY: all clean
