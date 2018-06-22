IPATH = -I"E:\Tsinghua\��һ��\���������\crawler\curl-7.60.0-win32-mingw\include"
LPATH = -L"E:\Tsinghua\��һ��\���������\crawler\curl-7.60.0-win32-mingw\lib"

all: main

main: main.o DoubanCrawler.o DoubanObject.o BaseObject.o BaseData.o Catcher.o
	g++ -o main main.o DoubanCrawler.o DoubanObject.o BaseObject.o BaseData.o Catcher.o -std=c++11 $(IPATH) $(LPATH) -lcurl -g

%.o: %.cpp DoubanCrawler.h DoubanObject.h BaseCrawler.h BaseObject.h BaseData.h Catcher.h
	g++ -c -o $@ $< -std=c++11 $(IPATH) $(LPATH) -lcurl -g

clean:
	rm *.o

clean = .PHONY