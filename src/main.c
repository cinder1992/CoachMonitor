#include <stdio.h>
#include <main.h>
#include <string.h>

const char signon_str[] = "COACH Monitor program " COACH_VERSION "\n"; 
const char compile_str[] = "Compiled with " _PLATFORM_CC " v" _PLATFORM_CC_VERSION " on " __DATE__ " at " __TIME__ "\n";

const char* teststr1 = "1000";
const char* teststr2 = "-32768";
const char* teststr3 = "0xBADF00D";

void main() {
	char* end;
	printf(signon_str);
	printf(compile_str);
	printf("%d,%d,%x\n", (int)strtol(teststr1,&end,0), (int)strtol(teststr2,&end,0), (int)strtol(teststr3,&end,0));
}
