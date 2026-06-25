#include <string.h>

char* strpbrk(const char* dest, const char* breakset) {
	for(; *dest; dest++) {
		for(; *breakset; breakset++) {
			if(*dest == *breakset) return (char*)dest;
		}
	}
	return (char*)NULL;
}
