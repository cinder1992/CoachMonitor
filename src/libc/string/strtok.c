#include <string.h>


char* strtok(char* str, const char* delim) {
	static char* strtok_state;

	if(str == NULL) {
		//First, check if str is NULL while we have no state
		if(strtok_state == NULL) return NULL;
		//then, set str to the state if the state is clean
		str = strtok_state;
	}

	//skip leading delimeter
	str += strspn(str,delim);

	//If we're at the end of the string, return NULL and reset state
	if(*str == '\0') return strtok_state = NULL;

	//skip past non-delimeter characters
	strtok_state = str + strcspn(str,delim);
	//If we're not at the last char in the string, set the next char to NULL
	if(*strtok_state != '\0') *strtok_state++ = '\0';
	//if we ARE at the last char in the string, clear the state so we don't clobber memory
	else strtok_state = NULL;

	return str;
}
