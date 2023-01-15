#Makefile for building images without a customised crosscompiler!

CC_FLAGS := -m64 -masm=intel -mabi=ms -nostdlib -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra
LD_FLAGS := --no-leading-underscore --enable-reloc-section -entry=start --oformat=pei-x86-64

TGT_NAME := main

TGT_CCFLAGS := ${CC_FLAGS} -pie
LIB_CCFLAGS := ${CC_FLAGS} -static

SRC_PATH := ./Source
BIN_PATH := ./out/bin
LIB_PATH := ./out/lib
OUT_FILE := a.exe

BINUTIL  := x86_64-w64-mingw32
COMPILER := ${BINUTIL}-gcc
LINKER   := ${BINUTIL}-ld

LINK_SCRIPT:= /PATH/TO/LINK/SCRIPT

build:
	${COMPILER} ${TGT_CCFLAGS} -c ${TGT_NAME}.c -o ${BIN_PATH}/${TGT_NAME}.obj

	${LINKER} ${LD_FLAGS} -o ${BIN_PATH}/${OUT_FILE} ${BIN_PATH}/${TGT_NAME}.obj ${LIB_PATH}/scpdos.lib ${LIB_PATH}/bochs.lib

libraries:
	${COMPILER} ${LIB_CCFLAGS} -c scpdos.c -o ${LIB_PATH}/scpdos.lib

	${COMPILER} ${LIB_CCFLAGS} -c ${SRC_PATH}/io.c -o ${LIB_PATH}/io.lib

	${COMPILER} ${LIB_CCFLAGS} -c ${SRC_PATH}/bochs.c -o ${LIB_PATH}/bochs.lib

all:
	${COMPILER} ${TGT_CCFLAGS} -c ${TGT_NAME}.c -o ${BIN_PATH}/${TGT_NAME}.obj

	${COMPILER} ${LIB_CCFLAGS} -c scpdos.c -o ${LIB_PATH}/scpdos.lib

	${COMPILER} ${LIB_CCFLAGS} -c ${SRC_PATH}/io.c -o ${LIB_PATH}/io.lib

	${COMPILER} ${LIB_CCFLAGS} -c ${SRC_PATH}/bochs.c -o ${LIB_PATH}/bochs.lib

	${LINKER} ${LD_FLAGS} -o ${BIN_PATH}/${OUT_FILE} ${BIN_PATH}/${TGT_NAME}.obj ${LIB_PATH}/scpdos.lib ${LIB_PATH}/bochs.lib

clean:
#Using the @ symbol suppresses echoing to the console. @echo "" inserts a new line between the command and the returned prompt
	@rm ${BIN_PATH}/*.obj
	@echo ""