CXX=/opt/compiler/gcc-4.8.2/bin/g++
INC_PATH=-I./glog_lib/include -I./libs/gflags/include/ -I./libs/boost/include -I../faiss/c_api -I../faiss
CXX_FLAGS=-O3 -std=c++11
GLOG_LIB = -L ../faiss -lfaiss -L ../faiss/c_api -lfaiss_c  -L./glog_lib/lib/ -lglog -L./libs/gflags/lib -lgflags -lpthread
LD_FLAGS=-Wl,-rpath=../mkl_libs/mkl/lib -Wl,-rpath=../faiss/c_api -Wl,-rpath=./glog_lib/lib
all:
	$(CXX) faiss_cal.cpp -o faiss_cal $(INC_PATH) $(CXX_FLAGS) $(GLOG_LIB) $(LD_FLAGS)
clean:
	@-rm faiss_cal
