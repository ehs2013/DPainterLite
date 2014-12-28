CXX = g++
CLANGXX = clang++
TARGET = DPainterLite.exe
SRCFILE = $(wildcard DPainterLite/*.cpp)
HEADERS = $(wildcard DPainterLite/*.h)

CXXFLAGS = --std=c++11 -g -Wno-write-strings -Wno-attributes -Wno-conversion-null -Wno-narrowing -Wno-format-security -Wno-invalid-source-encoding -Wno-format
LDFLAGS = -lgraphics -lcomdlg32 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -luuid -lgdiplus
INCLUDE = -I"external/rapidjson/include/" -I"external/ege/include/"
LIBRARY = -L"external/ege/lib/"

default: clean all

all: gcc_make

gcc: clean gcc_make

clang: clean clang_make

gcc_make: $(SRCFILE) $(HEADERS)
	$(CXX) $(SRCFILE) $(CXXFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o$(TARGET)

clang_make: $(SRCFILE) $(HEADERS)
	$(CLANGXX) $(SRCFILE) $(CXXFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o$(TARGET)

clean:
	$(RM) DPainterLite/*.h.gch DPainterLite.exe

.PHONY: clean all gcc clang gcc_make clang_make
