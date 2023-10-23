FROM gcc:4.9
WORKDIR /server
EXPOSE 9666
COPY server/. .
RUN gcc -std=c99 -o server2 server.c
CMD ["./server2"]