#Makefile for building images without a customised crosscompiler!

CC_FLAGS := -m64 -masm=intel -mabi=ms -nostdlib -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra
LD_FLAGS := --no-leading-underscore --enable-reloc-section -entry=start --oformat=pei-x86-64

TGT_NAME := main

TGT_CCFLAGS := ${CC_FLAGS} -pie

SRC_PATH := ./source
BIN_PATH := ./out/bin
OUT_FILE := a.exe

LIB_PATH := ./out/lib

CRT0_PATH	:= ./../CRT0
CRT1_PATH 	:= ./../DOSCRT
IO_PATH  	:= ./../IO
DBG_PATH 	:= ./../BREAK

BINUTIL  := x86_64-w64-mingw32
COMPILER := ${BINUTIL}-gcc
LINKER   := ${BINUTIL}-ld

LINK_SCRIPT:= /PATH/TO/LINK/SCRIPT

CRT0_LIB := ${CRT0_PATH}/${LIB_PATH}/crt0.lib
CRT1_LIB := ${CRT1_PATH}/${LIB_PATH}/scpdos.lib
DBG_LIB  := ${DBG_PATH}/${LIB_PATH}/bochs.lib
IO_LIB   := ${IO_PATH}/${LIB_PATH}/io.lib

build:
	${COMPILER} ${TGT_CCFLAGS} -c ${SRC_PATH}/${TGT_NAME}.c -o ${BIN_PATH}/${TGT_NAME}.obj

	${LINKER} ${LD_FLAGS} -o ${BIN_PATH}/${OUT_FILE} ${CRT0_LIB} ${CRT1_LIB} ${DBG_LIB}

clean:
#Using the @ symbol suppresses echoing to the console. @echo "" inserts a new line between the command and the returned prompt
	@rm ${BIN_PATH}/*.obj
	@echo ""