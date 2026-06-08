TARGET := m68k-elf
# override CC
CC := $(TARGET)-gcc
AS := $(TARGET)-as
LD := $(TARGET)-gcc
OBJCOPY := $(TARGET)-objcopy

SRCS += $(wildcard $(PLATDIR)/*.c)
ASSRCS += $(wildcard $(PLATDIR)/*.s)
PLATVPATH := $(PLATDIR)

OPTIMISE := 2

LDFLAGS := -march=68000 -ffreestanding -O$(OPTIMISE) -nostdlib -static-libgcc -lgcc -T $(SRCDIR)/platform/$(PLATFORM)/linker.ld
CFLAGS := -DPLATFORM_CC=\"$(CC)\" -I$(INCDIR) -I$(LIBCINCDIR) -I$(INCDIR)/platform/$(PLATFORM) -march=68010 -std=gnu99 -ffreestanding -O$(OPTIMISE) -Wall -Wextra

PLATFILES := *.bin* *.elf *.o *.s.o

PLATEXT := .elf

.PHONY: platform

coach.bin: coach.elf
	$(OBJCOPY) -O binary --set-start 0xe00000 --gap-fill 0x00 --pad-to 0xf00000 $< $@

coach.bin.lo: coach.bin
	$(OBJCOPY) -F binary -i 2 -b 1 $< $@

coach.bin.hi: coach.bin
	$(OBJCOPY) -F binary -i 2 -b 0 $< $@

coach.s68: coach.elf
	$(OBJCOPY) -O srec $< $@

platform: coach.bin.lo coach.bin.hi
