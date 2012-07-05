#ifndef TAO_GRADIENT_DESCENT_H
#define TAO_GRADIENT_DESCENT_H

#include <vector>

using namespace std;

void synchronous_gradient_descent(vector<string> arguments, double (*objective_function)(const std::vector<double> &));
void synchronous_gradient_descent(vector<string> arguments, double (*objective_function)(const std::vector<double> &), const vector<double> &starting_point, const vector<double> &step_size);

void synchronous_conjugate_gradient_descent(vector<string> arguments, double (*objective_function)(const std::vector<double> &));
void synchronous_conjugate_gradient_descent(vector<string> arguments, double (*objective_function)(const std::vector<double> &), const vector<double> &starting_point, const vector<double> &step_size);

#endif
