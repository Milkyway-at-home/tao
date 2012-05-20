#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <string>
#include <stdint.h>

#include "particle_swarm.hxx"
#include "differential_evolution.hxx"

//from undvc_common
#include "arguments.hxx"
#include "benchmarks.hxx"

/**
 *  Define a type for our objective function so we
 *  can pick which one to use and then the rest of
 *  the code will be the same.
 *
 *  Note that all the objective functions return a
 *  double, and take a double* and uint32_t as arguments.
 */
typedef double (*objective_function)(const vector<double> &);

int main(int argc /* number of command line arguments */, char **argv /* command line argumens */ ) {
    vector<string> arguments(argv, argv + argc);

    //assign the objective function variable to the objective function we're going to use
    string objective_function_name;
    get_argument(arguments, "--objective_function", true, objective_function_name);

    objective_function f = NULL;
    //compare returns 0 if the two strings are the same
    if (objective_function_name.compare("sphere") == 0)             f = sphere;
    else if (objective_function_name.compare("ackley") == 0)        f = ackley;
    else if (objective_function_name.compare("griewank") == 0)      f = griewank;
    else if (objective_function_name.compare("rastrigin") == 0)     f = rastrigin;
    else if (objective_function_name.compare("rosenbrock") == 0)    f = rosenbrock;
    else {
        cerr << "Improperly specified objective function: '" << objective_function_name.c_str() << "'" << endl;
        cerr << "Possibilities are:" << endl;
        cerr << "    sphere" << endl;
        cerr << "    ackley" << endl;
        cerr << "    griewank" << endl;
        cerr << "    rastrigin" << endl;
        cerr << "    rosenbrock" << endl;
        exit(1);
    }

    /**
     *  Initialize the arrays for the minimum and maximum bounds of the search space.
     *  These are different for the different objective functions.
     */
    uint32_t number_of_parameters;
    get_argument(arguments, "--n_parameters", true, number_of_parameters);
    vector<double> min_bound(number_of_parameters, 0);
    vector<double> max_bound(number_of_parameters, 0);

    for (uint32_t i = 0; i < number_of_parameters; i++) {        //arrays go from 0 to size - 1 (not 1 to size)
        if (objective_function_name.compare("sphere") == 0) {
            min_bound[i] = -100;
            max_bound[i] = 100;
        } else if (objective_function_name.compare("ackley") == 0) {
            min_bound[i] = -32;
            max_bound[i] = 32;
        } else if (objective_function_name.compare("griewank") == 0) {
            min_bound[i] = -600;
            max_bound[i] = 600;
        } else if (objective_function_name.compare("rastrigin") == 0) {
            min_bound[i] = -5.12;
            max_bound[i] = 5.12;
        } else if (objective_function_name.compare("rosenbrock") == 0) {
            min_bound[i] = -5;
            min_bound[i] = 10;
        }
    }

    string search_type;
    get_argument(arguments, "--search_type", true, search_type);
    if (search_type.compare("ps") == 0) {
        ParticleSwarm ps(min_bound, max_bound, arguments);
        ps.iterate(f);

    } else if (search_type.compare("de") == 0) {
        DifferentialEvolution de(min_bound, max_bound, arguments);
        de.iterate(f);

    } else {
        cerr << "Improperly specified search type: '" << search_type.c_str() <<"'" << endl;
        cerr << "Possibilities are:" << endl;
        cerr << "    de     -       differential evolution" << endl;
        cerr << "    ps     -       particle swarm optimization" << endl;
        exit(1);
    }

    return 0;
}
