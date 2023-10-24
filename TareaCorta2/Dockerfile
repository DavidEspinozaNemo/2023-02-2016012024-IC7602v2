FROM gcc:4.9
WORKDIR /
EXPOSE 9666
COPY /. .
RUN gcc -std=c99 -o server server.c
CMD ["./server"]