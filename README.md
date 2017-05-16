# Time Cache Libraries for `gettimeofday`

This project provides two implementations of a shared library that caches the `gettimeofday` system call on Linux systems. The cached value is updated at most every 100 milliseconds. Preloading this library will improve performance in blackbox applications that frequently call `gettimeofday`.

## Libraries

1. **Global Version (`libcache_gettimeofday_global.so`):**
   - Uses a global cache shared across all threads.
   - Synchronization is handled using a mutex (`pthread_mutex_t`).
   - Ensures consistent time values across threads.
   - Source file: `cache_gettimeofday_global.c`

2. **Per-Thread Version (`libcache_gettimeofday_per_thread.so`):**
   - Uses thread-local storage to maintain a separate cache for each thread.
   - No synchronization primitives are needed.
   - Offers better performance in multi-threaded applications.
   - Source file: `cache_gettimeofday_per_thread.c`

## Building the Libraries

Ensure you have `gcc` and `make` installed on your system.

To build both shared libraries, run:

```bash
make
```

## Usage

Running an application with the global cache:

```bash
LD_PRELOAD=./libcache_gettimeofday_global.so ./my_app
```

Running an application with the per-thread cache:
```bash
LD_PRELOAD=./libcache_gettimeofday_per_thread.so ./my_app
```

## License

Copyright 2017 [Lukas Lösche](mailto:lukas@opensourcery.de)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

&nbsp;&nbsp;&nbsp;&nbsp;[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
