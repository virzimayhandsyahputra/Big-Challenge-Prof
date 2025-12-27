BigChallenge:
	gcc -Wall ./src/main.c ./src/fileHandling.c ./src/parsing.c ./src/structure.c ./src/view.c -o program
	rm ./bin/out.bin
	echo "[+] Compile Selesai"