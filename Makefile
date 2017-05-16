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

test_cache: test_cache.c
	$(CC) -o $@ $<

test: test_cache libcache_gettimeofday_per_thread.so libcache_gettimeofday_global.so
	@echo "Running test without caching (expected to fail)..."
	-./test_cache
	@echo "Running test with per-thread caching library..."
	LD_PRELOAD=./libcache_gettimeofday_per_thread.so ./test_cache
	@echo "Running test with global caching library..."
	LD_PRELOAD=./libcache_gettimeofday_global.so ./test_cache

clean:
	rm -f $(TARGETS) test_cache

.PHONY: all clean test
