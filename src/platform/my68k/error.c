#include "platform/my68k/error.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

void (*userErrorHandlers[16])(void);
typedef struct __attribute__((packed)) regSave {
	union {
		int reg[16];
		struct {
			int d0;
			int d1;
			int d2;
			int d3;
			int d4;
			int d5;
			int d6;
			int d7;
			int a0;
			int a1;
			int a2;
			int a3;
			int a4;
			int a5;
			int a6;
			int a7;
		};
	};
	int usp;
	short fn;
	int aa;
	short ir;
	short sr;
	int pc;
} regSave_t;

extern void regdump(void);

typedef struct __attribute__((packed)) {
	short status;
	int pc;
	short vector;
} errorFrame;

static const char* errorStrings[] = {
	"",
	"",
	"Access Violation",
	"Address error",
	"Illegal instruction",
	"Divide by zero",
	"CHK out of bounds",
	"TRAPV with overflow",
	"Privilege violation",
	"Trace",
	"Line 1010",
	"Line 1111",
	"RESERVED","RESERVED",
	"Format error",
	"Uninitialized Interrupt Vector",
	"RESERVED","RESERVED","RESERVED","RESERVED",
	"RESERVED","RESERVED","RESERVED","RESERVED",
	"Spurious Interrupt",
	"","","","","","",
	"ABORT"
};

void __attribute__((interrupt)) err_bomb(void) {
	errorFrame* frame = __builtin_frame_address(0)+4;
	puts("\r\nBOMB exception, processor halted.\r\n");
	printf("Status: %x ", frame->status);
	printf("Error: %x\r\n ", frame->vector);
	puts(errorStrings[(frame->vector&0x00FF)>>2]);
	printf("PC: %x", frame->pc);
	while(1) asm volatile("stop #0x2000\n\t");
}
