XX = g++
CXXFLAGS = `pkg-config --cflags opencv`
LDFLAGS = -L/usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio 
INC=-I/usr/include/opencv
TARGET = TP
SOURCE = $(TARGET).cpp

TARGET:
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS) $(LDFLAGS)

.PHONY: all clean
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(PROG) $(TARGET)