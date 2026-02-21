# deskewk

A simple C++ application to correct skew of a document based on the journal: https://users.iit.demokritos.gr/~bgat/ICDAR2011_skew.pdf

# Datasets

https://drive.google.com/file/d/1a-a6aOqdsghjeHGLnCLsDs7NoJIus-Pw/view

# Dependencies

- Boost 1.90
- stb library

# Getting started

## Build application

- mkdir build 
- cd build
- cmake ..
- make

## Running the application

```
./build/deskewk <your image>.png
```

e.g.

```
./build/deskewk sample1_bc.png
```