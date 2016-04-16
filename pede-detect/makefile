CXX=g++ -std=gnu++14

BIN_DIR=./build
OBJ_DIR=./objs

SOURCE=pede-detect.cpp
TARGET=$(BIN_DIR)/pede-detect
OBJ=$(OBJ_DIR)/xhogDetector.o $(OBJ_DIR)/cmdParse.o
OPENCV=`pkg-config --cflags --libs opencv`

$(TARGET):chkobjdir chkbindir $(SOURCE) $(OBJ)
	@echo ""
	$(CXX) -o $(TARGET) $(SOURCE) $(OBJ) $(OPENCV)
	@echo "executable file is ./build/pede-detect"

$(OBJ_DIR)/xhogDetector.o:xhogDetector.h xhogDetector.cpp
	$(CXX) -c -o $(OBJ_DIR)/xhogDetector.o xhogDetector.cpp
$(OBJ_DIR)/cmdParse.o:cmdParse.hpp cmdParse.cpp
	$(CXX) -c -o $(OBJ_DIR)/cmdParse.o cmdParse.cpp


chkobjdir:
	@if test ! -d $(OBJ_DIR);\
	then \
		mkdir $(OBJ_DIR);\
	fi
	
chkbindir:
	@if test ! -d $(BIN_DIR);\
	then \
		mkdir $(BIN_DIR);\
	fi	

.PHONY:clean
clean:
	-rm -rf $(BIN_DIR) 
	-rm -rf $(OBJ_DIR)
	
