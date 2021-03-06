#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>

#include "mpi.h"

#include "asynchronous_algorithms/particle_swarm.hxx"

#include "mpi/master_worker.hxx"
#include "mpi/mpi_particle_swarm.hxx"

//from undvc_common
#include "arguments.hxx"

#ifdef CUDA
#include "mpi/assign_device.hxx"
#endif

using namespace std;

ParticleSwarmMPI::ParticleSwarmMPI(const std::vector<double> &min_bound,            /* min bound is copied into the search */
                                   const std::vector<double> &max_bound,            /* max bound is copied into the search */
                                   const vector<string> &arguments
                                  ) : ParticleSwarm(min_bound, max_bound, arguments) {

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!get_argument(arguments, "--max_queue_size", false, max_queue_size)) {
        if (rank == 0) {
            cout << "Argument '--max_queue_size <I>' not found, using default of 3." << endl;
        }
        max_queue_size = 3;
    }
}


void ParticleSwarmMPI::go(double (*objective_function)(const std::vector<double> &)) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        master<ParticleSwarmMPI, double>(this);
    } else {
        worker(objective_function, this->number_parameters, max_queue_size);
    }
    
    MPI_Finalize();
}

#ifdef CUDA
void ParticleSwarmMPI::go(double (*cpu_objective_function)(const std::vector<double> &),
                          double (*gpu_objective_function)(const std::vector<double> &),
                          int *device_assignments) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        master<ParticleSwarmMPI, double>(this);
    } else {
        assign_device(rank, device_assignments[rank]);
        if (device_assignments[rank] < 0) { //-1 is for CPU, 0 .. n are for GPUs
            worker(cpu_objective_function, this->number_parameters, max_queue_size);
        } else {
            worker(gpu_objective_function, this->number_parameters, max_queue_size);
        }
    }
    
    MPI_Finalize();
}
#endif
