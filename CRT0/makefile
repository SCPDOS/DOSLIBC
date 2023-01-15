#Makefile for building images without a customised crosscompiler!


ASM := nasm
SRC_PATH := ./source
LIB_PATH := ./out/lib
DBG_PATH := ./out/dbg

build:
	${ASM} ${SRC_PATH}/crt0.asm -o ${LIB_PATH}/crt0.lib -f win64 -l ${DBG_PATH}/lst/crt0.lst