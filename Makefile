CC       = gcc
CXX      = g++
CFLAGS   = -g
CXXFLAGS = $(CFLAGS)

LIBPATH = ./lib/
LIBS = -Wl,-rpath=./:./lib/HCNetSDKCom:./lib -lhcnetsdk
SRC = ./Hikvision_Video_Downloader.cpp
TARGET = ./Hikvision_Video_Downloader

all: 
	$(CXX) $(OPTI) $(CXXFLAGS) $(SRC) -o $(TARGET) -L$(LIBPATH) $(LIBS)

.PHONY: clean
clean:
	rm -f $(TARGET)
