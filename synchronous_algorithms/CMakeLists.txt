include_directories(${Boost_INCLUDE_DIR})

add_library(synchronous_algorithms parameter_sweep synchronous_gradient_descent synchronous_newton_method gradient line_search)
target_link_libraries(synchronous_algorithms ${UNDVC_COMMON_LIBRARY} tao_util ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
