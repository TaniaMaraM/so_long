FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    libxext-dev \
    libbsd-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN make re

CMD ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "./so_long", "maps/valid.ber"]