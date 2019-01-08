XX = g++ 
CXXFLAGS = `pkg-config --cflags opencv4` 
LDFLAGS = -L/usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
TARGET = TP 
SOURCE = TP.cpp Color.cpp


TARGET:
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS) $(LDFLAGS)

.PHONY: all clean
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

clean:
	-rm $(TARGET)