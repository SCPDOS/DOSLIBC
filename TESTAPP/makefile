#Makefile for building images without a customised crosscompiler!
OUT_NAME := a
TGT_NAME := main
SRC_PATH := ./source
BIN_PATH := ./out/bin
LIB_PATH := ./out/lib
OUT_FILE := ${OUT_NAME}.exe

CRT0_PATH	:= ./../CRT0
CRT1_PATH 	:= ./../DOSCRT
IO_PATH  	:= ./../IO
DBG_PATH 	:= ./../BREAK
STD_PATH	:= ./../STDLIB

CRT1_LIB := ${CRT1_PATH}/${LIB_PATH}/scpdos.lib
DBG_LIB  := ${DBG_PATH}/${LIB_PATH}/bochs.lib

CC_PATH  := -I ${CRT1_PATH}/headers ${IO_PATH}/headers ${DBG_PATH}/headers ${STD_PATH}/headers
CC_FLAGS := ${CC_PATH} -m64 -masm=intel -mabi=ms -pie -nostdlib -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra 
LD_FLAGS := -T link.ld  --no-leading-underscore --enable-reloc-section -Map=./out/dbg/${OUT_NAME}.map


IO_LIB   := ${IO_PATH}/${LIB_PATH}/io.lib

BINUTIL  := x86_64-w64-mingw32
COMPILER := ${BINUTIL}-gcc
LINKER   := ${BINUTIL}-ld
LINK_SCRIPT:= /PATH/TO/LINK/SCRIPT


build:
	${COMPILER} ${CC_FLAGS} -c ${SRC_PATH}/${TGT_NAME}.c -o ${BIN_PATH}/${TGT_NAME}.obj

	${LINKER} ${LD_FLAGS} -o ${BIN_PATH}/${OUT_FILE} ${BIN_PATH}/${TGT_NAME}.obj ${CRT1_LIB}

clean:
#Using the @ symbol suppresses echoing to the console. @echo "" inserts a new line between the command and the returned prompt
	@rm ${BIN_PATH}/*.obj
	@echo ""