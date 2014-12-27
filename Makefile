CXX = g++
TARGET = DPainterLite.exe
SRCFILE = $(wildcard DPainterLite/*.cpp) $(wildcard DPainterLite/*.h)

CXXFLAGS = --std=c++11 -g
LDFLAGS = -lgraphics -lcomdlg32 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -luuid -lgdiplus
INCLUDE = -I"external/rapidjson/include/"


default: clean all

all: $(SRCFILE)
	$(CXX) $(SRCFILE) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o$(TARGET)


clean:
	$(RM) DPainterLite/*.h.gch DPainterLite.exe

.PHONY: clean all
