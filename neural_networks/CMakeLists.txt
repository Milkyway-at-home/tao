include_directories(${Boost_INCLUDE_DIR})

include_directories(${RAPIDJSON_INCLUDE_DIR})

IF (OPENCL_INCLUDE_DIRS)
    message(STATUS "ADDING __OPENCL__ DEFINE")
    add_definitions( -D__OPENCL__ )

    include_directories(${OPENCL_INCLUDE_DIRS})

    add_library(neural_networks neural_network.cxx time_series_neural_network.cxx edge.cxx convolutional_neural_network.cxx opencl_utils.cxx edge_new.cxx ${OpenCV_LIBRARIES} ${OPENCL_LIBRARIES})
ELSE (OPENCL_INCLUDE_DIRS)

    add_library(neural_networks neural_network.cxx time_series_neural_network.cxx edge.cxx convolutional_neural_network.cxx edge_new.cxx ${OpenCV_LIBRARIES})

ENDIF(OPENCL_INCLUDE_DIRS)

