#ifndef TAO_ANT_COLONY_OPTIMIZATION_H
#define TAO_ANT_COLONY_OPTIMIZATION_H

#include <cmath>

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "stdint.h"

#include "neural_networks/edge.hxx"


class ACO_Node {
    public:
        //the layer and node of this node in the nerual network
        int layer;
        int node;

        //connections to the other nodes this can connect to
        vector<double>   pheromones;
        vector<ACO_Node*> targets;

        ACO_Node(int l, int n);
        ~ACO_Node();

        void add_target(ACO_Node* aco_node);
};

class ACOIndividual {
    public:
        double fitness;
        vector<Edge> edges;
        vector<Edge> recurrent_edges;

        ACOIndividual(double f, vector<Edge> e, vector<Edge> re);
};

class CompareACOIndividual {
    public:
        bool operator()(ACOIndividual *i1, ACOIndividual *i2) {
            return i1->fitness > i2->fitness;
        }
};



class AntColony {
    protected:
        const static double PHEROMONE_DEGRADATION_RATE;
        const static double PHEROMONE_MINIMUM;
        const static double PHEROMONE_MAXIMUM;

        string output_directory;

        int number_of_ants;
        int n_layers;
        uint32_t input_layer_size;
        uint32_t hidden_layer_size;
        uint32_t n_hidden_layers;

        ACO_Node* pre_input;
        vector< vector< ACO_Node* > > neurons;

        int max_edge_population_size;
        vector<ACOIndividual*> edge_population;

    public:
        AntColony(int noa, int meps, int ils, int hls, int nhl);
        ~AntColony();

        double get_best_fitness();
        double get_worst_fitness();
        int get_edge_population_size();

        void get_ant_paths(vector<Edge> &edges, vector<Edge> &recurrent_edges);

        void add_ant_paths_v(const vector<Edge> &edges);
        void add_ant_paths(double fitness, const vector<Edge> &edges, const vector<Edge> &recurrent_edges);

        void decrease_pheromones();

        void set_output_directory(string output_directory);
        void write_population(int current_iteration);

        friend void ant_colony_optimization(int maximum_iterations, AntColony &ant_colony, double (*objective_function)(const vector<Edge> &edges, const vector<Edge> &recurrent_edges));
};


void ant_colony_optimization(int maximum_iterations, AntColony &ant_colony, double (*objective_function)(const vector<Edge> &edges, const vector<Edge> &recurrent_edges));

#endif
