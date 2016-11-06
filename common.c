#include <stdlib.h>
#include <stdio.h>
#if defined(__GLIBC__)
#include <execinfo.h>
#endif
#include "common.h"


void* emalloc(size_t size) {
	void* ret = malloc(size);
	if (unlikely(size && !ret)) {
		fprintf(stderr, "malloc failed to allocate %zu bytes. terminating...",
				size);
#if defined(__GLIBC__)
		//add glibc backtrace() stuff here?
#endif
		exit(EXIT_FAILURE);
	}
	return ret;
}
void* erealloc(void* ptr, size_t size) {
	void* ret = realloc(ptr, size);
	if (unlikely(size && !ret)) {
		fprintf(stderr, "realloc failed to allocate %zu bytes. terminating...",
				size);
#if defined(__GLIBC__)
		//add glibc backtrace() stuff here?
#endif
		exit(EXIT_FAILURE);
	}
	return ret;
}
void* ecalloc(size_t num, size_t size) {
	//im not implementing arbitrary precision integer logic for the error message, feel free to fix it
	void* ret = calloc(num, size);
	if (unlikely(num > 0 && size > 0 && !ret)) {
		fprintf(stderr, "calloc failed to allocate %zu bytes. terminating...",
				num * size);
#if defined(__GLIBC__)
		//add glibc backtrace() stuff here?
#endif
		exit(EXIT_FAILURE);

	}
	return ret;
}
