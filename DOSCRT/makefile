#Makefile for building images without a customised crosscompiler!

CC_FLAGS := -m64 -masm=intel -mabi=ms -nostdlib -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static

SRC_PATH := ./source
LIB_PATH := ./out/lib

BINUTIL  := x86_64-w64-mingw32
COMPILER := ${BINUTIL}-gcc

libraries:
	${COMPILER} ${CC_FLAGS} -c ${SRC_PATH}/scpdos.c -o ${LIB_PATH}/scpdos.lib
	