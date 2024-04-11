# build stage
FROM alpine:latest as builder

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake

WORKDIR /app

COPY CMakeLists.txt .
COPY include/ ./include/
COPY src/ ./src/
COPY test/ ./test/

RUN mkdir build && cd build && cmake .. && make

# run stage
FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    libstdc++

WORKDIR /app

COPY --from=builder /app/build/tests .

CMD ["./tests"]
