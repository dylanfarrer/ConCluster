# build stage
FROM ubuntu:latest as builder

#RUN apk update && \
#    apk add --no-cache \
#    build-base \
#    cmake

RUN apt update && apt install -y gcc clang clang-tools cmake

WORKDIR /app

COPY CMakeLists.txt .
COPY include/ ./include/
COPY src/ ./src/
COPY test/ ./test/

RUN mkdir build && cd build && cmake .. && make

# run stage
#FROM alpine:latest
FROM ubuntu:latest

#RUN apk update && \
#    apk add --no-cache \
#    libstdc++

RUN apt-get update

WORKDIR /app

COPY --from=builder /app/build/tests .

CMD ["./tests"]
