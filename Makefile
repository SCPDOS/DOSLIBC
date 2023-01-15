build:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c main.c -o main.obj -Wall -Wextra -fpie

	x86_64-w64-mingw32-ld -entry=main --oformat=pei-x86-64 main.obj ./Lib/scpdos.lib ./Lib/bochs.lib

libraries:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/scpdos.c -o ./Lib/scpdos.lib -Wall -Wextra -fpie

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/io.c -o ./Lib/io.lib -Wall -Wextra -fpie

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/bochs.c -o ./Lib/bochs.lib -Wall -Wextra -fpie

all:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c main.c -o main.obj -Wall -Wextra -fpie

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/io.c -o ./Lib/io.lib -Wall -Wextra -fpie

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/scpdos.c -o ./Lib/scpdos.lib -Wall -Wextra -fpie

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -c ./Lib/Source/bochs.c -o ./Lib/bochs.lib -Wall -Wextra -fpie

	x86_64-w64-mingw32-ld -entry=main --oformat=pei-x86-64 main.obj ./Lib/scpdos.lib ./Lib/bochs.lib 