include_directories(${Boost_INCLUDE_DIR})

add_library(asynchronous_algorithms evolutionary_algorithm.cxx particle_swarm.cxx differential_evolution.cxx individual.cxx asynchronous_newton_method.cxx asynchronous_genetic_search.cxx ant_colony_optimization.cxx neat.cxx ant_colony_optimization_new.cxx)
#add_library(asynchronous_algorithms evolutionary_algorithm particle_swarm differential_evolution individual asynchronous_newton_method asynchronous_genetic_search)
target_link_libraries(asynchronous_algorithms ${UNDVC_COMMON_LIBRARY} tao_util)

if (MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})
    include_directories(${MYSQL_INCLUDE_DIR}/mysql)

    add_library(db_asynchronous_algorithms particle_swarm_db.cxx differential_evolution_db.cxx asynchronous_newton_method_db.cxx)
    target_link_libraries(db_asynchronous_algorithms ${UNDVC_COMMON_LIBRARY} tao_util ${MYSQL_LIBRARIES})
else (MYSQL_FOUND)
    message(STATUS "MYSQL not found, not compiling database enabled evolutionary algorithms")
endif (MYSQL_FOUND)
