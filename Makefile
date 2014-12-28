CXX = g++
TARGET = DPainterLite.exe
SRCFILE = $(wildcard DPainterLite/*.cpp) $(wildcard DPainterLite/*.h)

CXXFLAGS = --std=c++11 -g -Wno-write-strings -Wno-attributes -Wno-conversion-null -Wno-narrowing
LDFLAGS = -lgraphics -lcomdlg32 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -luuid -lgdiplus
INCLUDE = -I"external/rapidjson/include/" -I"external/ege/include/"
LIBRARY = -L"external/ege/lib/"

default: clean all

all: $(SRCFILE)
	$(CXX) $(SRCFILE) $(CXXFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o$(TARGET)


clean:
	$(RM) DPainterLite/*.h.gch DPainterLite.exe

.PHONY: clean all
