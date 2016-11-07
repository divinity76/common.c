#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#if defined(__GLIBC__)
#include <execinfo.h>
#endif
#include "misc.h"
#define macrobacktrace() { \
void *array[20]; \
int traces=backtrace(array,sizeof(array)/sizeof(array[0])); \
if(traces<=0) { \
	fprintf(stderr,"failed to get a backtrace!"); \
} else { \
backtrace_symbols_fd(array,traces,STDERR_FILENO); \
} \
fflush(stderr); \
}

void *emalloc(const size_t size) {
	void *ret = malloc(size);
	if (unlikely(size && !ret)) {
		fprintf(stderr,
				"malloc failed to allocate %zu bytes. errno: %i. strerror: %s. terminating...\n",
				size, errno, strerror(errno));
		fflush(stderr);
		fflush(stdout);
#if defined(__GLIBC__)

		macrobacktrace()
#endif
		exit(EXIT_FAILURE);
	}
	return ret;
}
void *erealloc(void *ptr, const size_t size) {
	void *ret = realloc(ptr, size);
	if (unlikely(size && !ret)) {
		fprintf(stderr,
				"realloc failed to allocate %zu bytes. errno: %i. strerror: %s. terminating...\n",
				size, errno, strerror(errno));
		fflush(stderr);
		fflush(stdout);
#if defined(__GLIBC__)
		macrobacktrace()
#endif
		exit(EXIT_FAILURE);
	}
	return ret;
}
void *ecalloc(const size_t num, const size_t size) {
	//im not implementing arbitrary precision integer logic for the error message, feel free to fix it
	void *ret = calloc(num, size);
	fflush(stderr);
	fflush(stdout);
	if (unlikely(num > 0 && size > 0 && !ret)) {
		fprintf(stderr,
				"calloc failed to allocate %zu*%zu bytes. errno: %i. strerror: %s. terminating...\n",
				num, size, errno, strerror(errno));
#if defined(__GLIBC__)
		macrobacktrace()
#endif
		exit(EXIT_FAILURE);

	}
	return ret;
}

