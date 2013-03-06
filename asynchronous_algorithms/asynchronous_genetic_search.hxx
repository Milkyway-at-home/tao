#ifndef TAO_ASYNCHRONOUS_GENETIC_SEARCH_H
#define TAO_ASYNCHRONOUS_GENETIC_SEARCH_H

#include <vector>
#include <queue>

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace std;

using boost::variate_generator;
using boost::mt19937;
using boost::uniform_real;

typedef double (*objective_function_type)(const vector<int> &);
typedef vector<int> (*random_encoding_type)();
typedef vector<int> (*mutate_type)(const vector<int> &);
typedef vector<int> (*crossover_type)(const vector<int> &, const vector<int> &);

class GeneticAlgorithmIndividual {
    public:
        const double fitness;
        const vector<int> encoding;

        GeneticAlgorithmIndividual(double _fitness, const vector<int> &_encoding);
};

class GeneticAlgorithm {
    private:
        int individuals_inserted;
        int individuals_generated;
        vector<GeneticAlgorithmIndividual*> population;

        boost::variate_generator< boost::mt19937, boost::uniform_real<> > *random_number_generator;

        int find_insert_position(double fitness, int min_position, int current_position, int max_position);

        bool is_duplicate(const vector<int> &new_individual);

    protected:
        double mutation_rate;
        double crossover_rate;

        int population_size;
        int encoding_length;

        random_encoding_type random_encoding;
        mutate_type mutate;
        crossover_type crossover;

    public:

        GeneticAlgorithm(const vector<string> &arguments,
                         int _encoding_length,
                         random_encoding_type _random_encoding,
                         mutate_type _mutate,
                         crossover_type _crossover);


        vector<int> get_new_individual();
        void insert_individual(double fitness, const int* encoding);
        void insert_individual(double fitness, const vector<int> &encoding);
};


#endif
