#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


static void sihdlr(int signum, siginfo_t *sig, void *uc)
{
	printf("Signal handler executed\n");
	signal(signum, SIG_IGN);
}

void* thread_func(void *arg) {
	int delay = *((int*)arg);
	sleep(delay);
}

int main()
{
	timer_t tid;
	struct sigevent sev;
	struct itimerspec its;
	sigset_t mask;
	struct sigaction sa;

	/* Add signal handler that is executed when timer fires off */
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sihdlr;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
		perror("sigaction");
		return -1;
	}

	/* Initialize timer */
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = &tid;
	if (timer_create(CLOCK_MONOTONIC, &sev, &tid) == -1) {
		perror("timer_create");
		return -1;
	}

	/* Start timer */
	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;
	if (timer_settime(tid, 0, &its, NULL) == -1) {
		perror("timer_settime");
		return -1;
	}

	/* Execute sleep in a thread to not block main process  */
	pthread_t thread;
	int delay = its.it_value.tv_sec + 1;
	pthread_create(&thread, NULL, thread_func, &delay);
	pthread_join(thread, NULL);

	puts("Done");

	return 0;
}