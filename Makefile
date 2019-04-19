CXX=/opt/compiler/gcc-4.8.2/bin/g++
INC_PATH=-I./libs/glog/include/ -I./libs/gflags/include/ -I./libs/boost/include -I../faiss/c_api
CXX_FLAGS=-O3 -std=c++11
GLOG_LIB = -L./libs/glog/lib/ -lglog -L./libs/gflags/lib -lgflags -L ../faiss -lfaiss -L ../faiss/c_api -lfaiss_c -lpthread
LD_FLAGS=-Wl,-rpath=../mkl_libs/mkl/lib -Wl,-rpath=../faiss/c_api
all:
	$(CXX) faiss_cal.cpp -o faiss_cal $(INC_PATH) $(CXX_FLAGS) $(GLOG_LIB) $(LD_FLAGS)
clean:
	@-rm faiss_cal
