build:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -c main.c -o ./out/bin/main.obj

	x86_64-w64-mingw32-ld -entry=main --oformat=pei-x86-64 -o ./out/bin/a.exe ./out/bin/main.obj ./out/lib/scpdos.lib ./out/lib/bochs.lib

	rm ./out/bin/*.obj

libraries:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c scpdos.c -o ./out/lib/scpdos.lib

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c ./Source/io.c -o ./out/lib/io.lib

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c ./Source/bochs.c -o ./out/lib/bochs.lib

all:
	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -c main.c -o ./out/bin/main.obj

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c scpdos.c -o ./out/lib/scpdos.lib

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c ./Source/io.c -o ./out/lib/io.lib

	x86_64-w64-mingw32-gcc -m64 -masm=intel -mabi=ms -ffreestanding -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -Wall -Wextra -static -c ./Source/bochs.c -o ./out/lib/bochs.lib

	x86_64-w64-mingw32-ld -entry=main --oformat=pei-x86-64 -o ./out/bin/a.exe ./out/bin/main.obj ./out/lib/scpdos.lib ./out/lib/bochs.lib

	rm ./out/bin/*.obj