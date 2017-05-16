#define _GNU_SOURCE
#include <sys/time.h>
#include <time.h>
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

typedef int (*real_gettimeofday_t)(struct timeval *, struct timezone *);

int gettimeofday(struct timeval *tv, void *tz)
{
    static real_gettimeofday_t real_gettimeofday = NULL;
    static struct timeval cached_tv;
    static struct timespec last_update = {0, 0};
    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    if (real_gettimeofday == NULL) {
        real_gettimeofday = (real_gettimeofday_t)dlsym(RTLD_NEXT, "gettimeofday");
        if (real_gettimeofday == NULL) {
            fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
            return -1;
        }
    }

    int ret;
    pthread_mutex_lock(&lock);

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    if (last_update.tv_sec == 0 && last_update.tv_nsec == 0) {
        ret = real_gettimeofday(&cached_tv, tz);
        if (ret == -1) {
            pthread_mutex_unlock(&lock);
            return -1;
        }
        last_update = now;
    }

    long ms_elapsed = (now.tv_sec - last_update.tv_sec) * 1000 +
                      (now.tv_nsec - last_update.tv_nsec) / 1000000;

    if (ms_elapsed >= 100) {
        ret = real_gettimeofday(&cached_tv, tz);
        if (ret == -1) {
            pthread_mutex_unlock(&lock);
            return -1;
        }
        last_update = now;
    }

    *tv = cached_tv;

    pthread_mutex_unlock(&lock);
    return 0;
}
