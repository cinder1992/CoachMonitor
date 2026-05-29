#include <stdio.h>
#include <main.h>

const char signon_str[] = "COACH Monitor program " COACH_VERSION "\n"; 
const char compile_str[] = "Compiled with " _PLATFORM_CC " v" _PLATFORM_CC_VERSION " on " __DATE__ " at " __TIME__ "\n";

void main() {
	printf(signon_str);
	printf(compile_str);
}
