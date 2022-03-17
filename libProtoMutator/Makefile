TARGET=libprotobuf_mutator.a
CXX=clang++
CXXFLAGS=-g -ggdb  -Wall -Wextra -fPIC -I/usr/local/include/libprotobuf-mutator -I../. -I.
LDFLAGS=-shared 
AR=ar

all: $(TARGET)

main.o: main.cc main.h
	$(CXX) $(CXXFLAGS) -c $<

serialize.o: core/serialize.cc core/core.h
	$(CXX) $(CXXFLAGS) -c $<

deserialize.o: core/deserialize.cc
	$(CXX) $(CXXFLAGS) -c $<

test.pb.o: core/test.pb.cc core/test.pb.h
	$(CXX) $(CXXFLAGS) -c $<

override_mutator.o: mutator/override_mutator.cc mutator/override_mutator.h
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): main.o serialize.o deserialize.o test.pb.o override_mutator.o 
	$(AR) rcs $@ $^ 

#$(TARGET): main.o serialize.o deserialize.o test.pb.o override_mutator.o \
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean compile
clean: 
	rm $(TARGET) *.o

compile: 
	protoc --cpp_out=. core/test.proto 
