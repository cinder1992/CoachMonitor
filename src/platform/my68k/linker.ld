MEMORY
{
    VECTBL (rw) : ORIGIN = 0, LENGTH = 0x400
    RAM (rwx) : ORIGIN = 0x400, LENGTH = 1M - 0x400
    ROM (rx) : ORIGIN = 0xe00000, LENGTH = 1M
}

SECTIONS
{
	ENTRY(_start)
	/* ROM entries */
	.text : { *(.text) *(.text*) } >ROM
	.rodata : { *(.rodata) *(.rodata*) } >ROM

	/* Vector table */
	.vectors : {*(.vectors)} >VECTBL AT>ROM
	.tpa ORIGIN(RAM) (NOLOAD) : { . = ABSOLUTE(ORIGIN(RAM) + LENGTH(RAM) - (8K + 512)); _etpa = .; } >RAM
	.ustack (NOLOAD) : { . = 4K; } >RAM
	.sstack (NOLOAD) : { . = 4K; } >RAM
	.data : {
		*(.data)
		. = ALIGN(256);
	} >RAM AT>ROM
	.bss (NOLOAD) : { *(.bss) *(COMMON) . = ALIGN(256); } >RAM

	/* Symbols used for loading data by the loader */
	_vectors = ADDR(.vectors);
	_evectors = ADDR(.vectors) + SIZEOF(.vectors);
	_lvectors = LOADADDR(.vectors);
	_data = ADDR(.data);
	_edata = ADDR(.data) + SIZEOF(.data);
	_ldata = LOADADDR(.data);
	_bss = ADDR(.bss);
	_ebss = ADDR(.bss) + SIZEOF(.bss);
	_SSP = ADDR(.sstack) + SIZEOF(.sstack);
	_USP = ADDR(.ustack) + SIZEOF(.ustack);
}
