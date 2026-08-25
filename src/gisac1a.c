
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // Required for sigaction and SIGINT
#include <unistd.h> // Required for sleep

static volatile int handled = 0; // Prevent compiler optimizations

static void handler(int signum) {
    (void)signum; // Silence unused parameter warning
    handled++;
}

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = &handler;

    // Correct integer comparison
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        return -1; 
    }

    for (;;) {
        // Added \n to flush the output buffer
        printf("handled : %d", handled); 
        sleep(3);
    }
    return 0;
}

