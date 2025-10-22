This is a simple demo script using libopencv to render a webcam using the olc PixelGameEngine on linux.

Install webcam library:
```bash
sudo apt install libopencv-dev
```

Build binary:
```bash
g++ -o pgewebcam pge_linux_webcam.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

# Webcam link flags: 
# -lopencv_core -lopencv_videoio -lopencv_imgproc
```

Run binary:
./pgewebcam
