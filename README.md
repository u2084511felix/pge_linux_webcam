Build:

```bash
g++ -o pgewebcam pge_linux_webcam.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

# Webcam link flags: 
# -lopencv_core -lopencv_videoio -lopencv_imgproc
```

run:

./pgewebcam
