path=C:\Users\Scott\gbadev\devkitadv-r5-beta-3\bin
REM compiling with below line makes things run very slow
REM gcc  -o homebound.elf main.c gfx.c sfx.c -lm

gcc -c -O3 -mthumb -mthumb-interwork gfx.c
gcc -c -O3 -mthumb -mthumb-interwork main.c
gcc -c -O3 -mthumb -mthumb-interwork sfx.c

gcc -mthumb -mthumb-interwork -o homebound.elf main.o gfx.o sfx.o

objcopy -O binary homebound.elf homebound.gba

pause