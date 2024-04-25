# build stage

# using ubuntu (rather than alpine) as it more closely 
# reflects github CI/CD environment.

FROM ubuntu:latest as builder

RUN apt update && apt install -y gcc clang clang-tools cmake

WORKDIR /app

COPY CMakeLists.txt .
COPY include/ ./include/
COPY src/ ./src/
COPY test/ ./test/

RUN mkdir build && cd build && cmake .. && make && make install

RUN cd test && rm -rf build && mkdir build && cd build && cmake .. && make

# run stage
FROM ubuntu:latest

RUN apt-get update

WORKDIR /app

COPY --from=builder /app/test/build/tests .
COPY --from=builder /usr/local/lib/libconcluster* /usr/local/lib/

CMD ["./tests"]
