EXENAME = mp1
OBJS = main.o layer.o network.o 2d.o features.o pooling.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp layer.h network.h 2d.h
	$(CXX) $(CXXFLAGS) main.cpp

layer.o : layer.cpp layer.h 
	$(CXX) $(CXXFLAGS) layer.cpp

network.o : network.cpp network.h layer.h
	$(CXX) $(CXXFLAGS) network.cpp

2d.o : 2d.cpp 2d.h
	$(CXX) $(CXXFLAGS) 2d.cpp

features.o : features.cpp features.h 2d.h
	$(CXX) $(CXXFLAGS) features.cpp

pooling.o : pooling.cpp pooling.h
	$(CXX) $(CXXFLAGS) pooling.cpp

clean :
	-rm -f *.o $(EXENAME)
