#include <stdio.h>
#include <platform.h>

char* _platform_ram[1024*1024];
void* _platform_mem = (void*)_platform_ram;

FILE _platform_stdin_file = {
	._buf_size = 0,
	._buf_unget = '\0',
	._fd = 0,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 1,
	._fl_w = 0,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek
};

FILE _platform_stdout_file = {
	._buf_size = 0,
	._fd = 1,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 0,
	._fl_w = 1,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek,
};

FILE _platform_stderr_file = {
	._buf_size = 0,
	._fd = 2,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 0,
	._fl_w = 1,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek,
};

#define SYSCALL_READ 0
#define SYSCALL_WRITE 1
#define SYSCALL_CLOSE 3
#define SYSCALL_FSYNC 74
#define SYSCALL_LSEEK 8

int _platform_read(int fdes, unsigned char* buf, size_t count) {
	register int retval asm("%rax") = SYSCALL_READ;
	register int rdi asm("%rdi") = fdes;
	register unsigned char* rsi asm("%rsi") = buf;
	register size_t rdx asm("%rdx") = count;
	asm volatile(
		"syscall"
		: "+r"(retval)
		: "r"(retval), "r"(rdi), "r"(rsi), "r"(rdx)
		: "memory"
	);
	return retval;
}

int _platform_write(int fdes, const unsigned char* buf, size_t count) {
	register int retval asm("%rax") = SYSCALL_WRITE;
	register int rdi asm("%rdi") = fdes;
	register const unsigned char* rsi asm("%rsi") = buf;
	register size_t rdx asm("%rdx") = count;
	asm volatile(
		"syscall"
		: "+r"(retval)
		: "r"(retval), "r"(rdi), "r"(rsi), "r"(rdx)
		: "memory"
	);
	return retval;
}


int _platform_close(int fdes) {
	register int retval asm("%rax") = SYSCALL_CLOSE;
	register int rdi asm("%rdi") = fdes;
	asm volatile(
		"syscall"
		: "+r"(retval)
		: "r"(retval), "r"(rdi)
		: "memory"
	);
	return retval;
}

int _platform_flush(int fdes) {
	register int retval asm("%rax") = SYSCALL_FSYNC;
	register int rdi asm("%rdi") = fdes;
	asm volatile(
		"syscall"
		: "+r"(retval)
		: "r"(retval), "r"(rdi)
		: "memory"
	);
	return retval;
}

off_t _platform_seek(int fdes, off_t offs, unsigned int whence) {
	register int retval asm("%rax") = SYSCALL_LSEEK;
	register int rdi asm("%rdi") = fdes;
	register off_t rsi asm("%rsi") = offs;
	register unsigned int rdx asm("%rdx") = whence;
	asm volatile(
		"syscall"
		: "+r"(retval)
		: "r"(retval), "r"(rdi), "r"(rsi), "r"(rdx)
		: "memory"
	);
	return retval;
}
