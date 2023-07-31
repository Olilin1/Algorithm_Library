/*
AUTHOR: Oliver Lindgren
*/

#ifndef EQUATION_SOLVER_HPP
#define EQUATION_SOLVER_HPP
#include<vector>
#include<cmath>
#include<iostream>
#include<assert.h>

/*
Tar en n X n matris a och en vector b av längd n. Löser sedan ekvationssystemet ax = b med hjälp av gauss-elimininering
och returnerar vectorn v av längd n där v[i] = värdet för x_i
Om ett x_i inte kan bestämmas utan har flera möjliga värden då är v[i] = NaN.
Om det linjära ekvationssystemet är inkonsistent då returneras en tom vektor.
*/
std::vector<double> equation_solver(const std::vector<std::vector<double>>& a, const std::vector<double>& b);

bool is_double_zero(double x);

#endif