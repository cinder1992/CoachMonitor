# Coach
## the **C**leverly **O**ptimized **A**lgorithm for **C**ontrolling **H**ardware
A portable monitor program for retrocomputing projects, intended to be modular and easy-to-port to new platforms

## Why C?
Simple, Portability! If your platform has a C compiler, you're halfway to anywhere!

## Usage
The platform isn't complete yet, there's lots of dead code, bugs, and malfeatures that need ironing out.

## Differences from TUTOR
(some) of the commands are borrowed from the TUTOR monitor, but with some minor changes;

1. Numbers are now in C format with C prefixes, and are assumed to be decimal by default.
2. Some commands are platform-dependant, including, but not limited to, GO, BR, and register printing commands.

## Porting
see PORTING.md in src/platform
