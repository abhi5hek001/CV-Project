# Topic: Feature detection, descriptor and matching

<b>Assignment (Code-FDDM):</b>
The assignment has three parts: key point detection, feature description, and feature matching.\
<b>1. Keypoint detection:</b> Identify points of interest in the image using the Harris corner
detection method. [8 Marks]\
<b>2. Feature description:</b> Find scale invariant feature transform (SIFT) descriptor at each key
point. [6 Marks]\
<b>3. Feature matching:</b> Find the matching features with sum of squared differences (SSD) and
ratio distance. For ratio distance. find the closest and second closest features by SSD
distance. The ratio distance is their ratio (i.e., SSD distance of the closest feature match
divided by SSD distance of the second closest feature match). [6 Marks]
Along with the code, you should submit two outputs, keypoint detection and feature matching as
given below.

[Demonstration of output](https://github.com/user-attachments/assets/2f731f08-e987-40da-911d-9c12db11e83b)

## Step 1: Install OpenCV & OpenCV Contrib from Source
### Install necessary updates in your ubuntu machine

      sudo apt update
      
      sudo apt install build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb-dev libdc1394-dev

### Clone the OpenCV and OpenCV contrib repository

      cd ~
      git clone https://github.com/opencv/opencv.git
      git clone https://github.com/opencv/opencv_contrib.git

### Create a build directory and configure CMake to include contrib modules
      cd ~/opencv
      mkdir build
      cd build
      cmake -D CMAKE_BUILD_TYPE=Release \
            -D CMAKE_INSTALL_PREFIX=/usr/local \
            -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
            -D BUILD_EXAMPLES=ON ..

### Compile OpenCV
      make -j$(nproc)   

### Install OpenCV
      sudo make install
      sudo ldconfig

## Step 2: Compile your program
      g++ -o cvProject S20220010003_FDDM.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_xfeatures2d -lGL -lGLU -lglut

After compiling, run the program using

     ./cvProject
