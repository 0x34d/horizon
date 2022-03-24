# horizon
libprotobuf-mutator for Test.
Working....

## Run
libprotobuf-mutator is a library to randomly mutate
[libprotobuf-mutator](https://github.com/google/libprotobuf-mutator). <BR>

## Quick start on Fedora

Install:

```
git clone https://github.com/google/libprotobuf-mutator

cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLIB_PROTO_MUTATOR_TESTING=OFF -DCMAKE_BUILD_TYPE=Debug ../
```
## Run
```
  make 
  make compile
```
