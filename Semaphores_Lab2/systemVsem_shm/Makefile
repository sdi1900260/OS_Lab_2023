all: systemV-semaphores \
	sem-server \
	sem-client

systemV-semaphores: systemV-semaphores.c
	gcc -g -Wall systemV-semaphores.c -o systemV-semaphores

sem-server: sem-server.c
	gcc -g -Wall sem-server.c -o sem-server

sem-client: sem-client.c
	gcc -g -Wall sem-client.c -o sem-client


clean:
	rm -f systemV-semaphores \
		sem-client sem-server
