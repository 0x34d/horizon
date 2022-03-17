TARGET=myprog
CXX=clang++
CXXFLAGS=-g -Wall -Wextra  -I.

PROTOBUF_LIB=/usr/lib64/libprotobuf.so
FUZZ_MUTATOR=libProtoMutator/libprotobuf_mutator.a
LPM_LIB=/usr/local/lib/libprotobuf-mutator.a

all: $(TARGET)

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $@ $^  $(PROTOBUF_LIB) $(FUZZ_MUTATOR) $(LPM_LIB)

.PHONY: clean
clean: 
	rm $(TARGET) *.o

