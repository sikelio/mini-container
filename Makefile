build:
	gcc -o ./out/main main.c ./src/utility/file-handler.c

launch:
	make build && sudo ./out/main
