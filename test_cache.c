#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_ITERATIONS 1000

int main(void)
{
    struct timeval tv_prev, tv_current;
    long time_diff;
    long min_time_diff = 1000000L;
    int i;

    gettimeofday(&tv_prev, NULL);

    for (i = 0; i < NUM_ITERATIONS; i++) {
        gettimeofday(&tv_current, NULL);

        time_diff = (tv_current.tv_sec - tv_prev.tv_sec) * 1000000L +
                    (tv_current.tv_usec - tv_prev.tv_usec);

        if (time_diff > 0 && time_diff < min_time_diff) {
            min_time_diff = time_diff;
        }

        tv_prev = tv_current;
    }

    if (min_time_diff >= 1000) {
        printf("Caching of gettimeofday detected. Minimum time difference: %ld us\n", min_time_diff);
        exit(0);
    } else {
        printf("No caching of gettimeofday detected. Minimum time difference: %ld us\n", min_time_diff);
        exit(1);
    }
}
