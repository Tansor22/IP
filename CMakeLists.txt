cmake_minimum_required(VERSION 3.16)
project(IP)
# Gets CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# C++ standard.
set(CMAKE_CXX_STANDARD 14)
# Path to Qt MinGw dir
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.1\\mingw73_64\\")

include_directories(.)
# Qt .dll's that are used
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp common/headers/ProjectConstants.h common/src/DataRetriever.cpp common/headers/DataRetriever.h common/src/ImagesHandler.cpp common/headers/ImagesHandler.h common/src/ProjectHelper.cpp common/headers/ProjectHelper.h convolution/src/KernelsHandler.cpp convolution/headers/KernelsHandler.h convolution/src/ConvolutionTool.cpp convolution/headers/ConvolutionTool.h convolution/src/SequentialConvolutionTool.cpp convolution/headers/SequentialConvolutionTool.h common/src/ImageToProcess.cpp common/headers/ImageToProcess.h common/src/ItpPrinter.cpp common/headers/ItpPrinter.h common/headers/ItpPrinter.fwd.h common/headers/ImageToProcess.fwd.h convolution/src/Kernel.cpp convolution/headers/Kernel.h convolution/src/ConvolutionBuilder.cpp convolution/headers/ConvolutionBuilder.h convolution/src/Convolution.cpp convolution/headers/Convolution.h convolution/src/OutOfBoundPolicy.cpp convolution/headers/OutOfBoundPolicy.h convolution/src/MirrorPolicy.cpp convolution/headers/MirrorPolicy.h pois/src/POIsFinder.cpp pois/headers/POIsFinder.h pois/src/POI.cpp pois/headers/POI.h pois/src/Moravec.cpp pois/headers/Moravec.h pois/src/Harris.cpp pois/headers/Harris.h common/src/RgbImage.cpp common/headers/RgbImage.h common/src/GrayImage.cpp common/headers/GrayImage.h common/headers/GrayImage.fwd.h descriptors/src/DescritorBuilder.cpp descriptors/headers/DescritorBuilder.h convolution/src/BorderPolicy.cpp convolution/headers/BorderPolicy.h descriptors/src/Descriptor.cpp descriptors/headers/Descriptor.h demos/src/Lab5.cpp demos/headers/Lab5.h demos/src/Lab.cpp demos/headers/Lab.h)

# Link Qt libraries to the exe's
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)