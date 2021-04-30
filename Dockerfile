FROM gcc:latest

WORKDIR /app

COPY ./main2.cpp .

# RUN apt update

RUN g++ -O3 -o prog main2.cpp

RUN mv prog /usr/bin