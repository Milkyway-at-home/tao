include_directories(${Boost_INCLUDE_DIR})

add_library(synchronous_algorithms parameter_sweep.cxx synchronous_gradient_descent.cxx synchronous_newton_method.cxx gradient.cxx line_search.cxx)
target_link_libraries(synchronous_algorithms ${UNDVC_COMMON_LIBRARY} tao_util ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
