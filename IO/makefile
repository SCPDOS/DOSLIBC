#Makefile for building images without a customised crosscompiler!

CC_FLAGS := -m64 -masm=intel -mabi=ms -nostdlib -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static

SRC_PATH := ./source
LIB_PATH := ./out/lib

BINUTIL  := x86_64-w64-mingw32
COMPILER := ${BINUTIL}-gcc

libraries:
	${COMPILER} ${CC_FLAGS} -c ${SRC_PATH}/io.c -o ${LIB_PATH}/io.o
	ar rcs ${LIB_PATH}/io.lib ${LIB_PATH}/io.o ../DOSCRT/out/lib/scpdos.lib
	rm ${LIB_PATH}/io.o
	
#Must use ar to archive io.o and scpdos.lib together, to allow us to wrap scpdos.lib in io.o