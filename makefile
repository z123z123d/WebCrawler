IPATH = -I"E:\Tsinghua\大一下\面向对象编程\crawler\curl-7.60.0-win32-mingw\include"
LPATH = -L"E:\Tsinghua\大一下\面向对象编程\crawler\curl-7.60.0-win32-mingw\lib"

all: test

test: test.o BaseCrawler.o Catcher.o BaseObject.o test.cpp BaseCrawler.cpp Catcher.cpp
	g++ -o test test.o BaseCrawler.o Catcher.o BaseObject.o -std=c++11 $(IPATH) $(LPATH) -lcurl

%.o: %.cpp
	g++ -c -o $@ $^ -std=c++11 $(IPATH) $(LPATH) -lcurl

clean:
	rm *.o

clean = .PHONY