#include "mc.h"
#include "progress.h"

using pele::Array;

namespace mcpele{

MC::MC(pele::BasePotential * potential, Array<double>& coords, double temperature, double stepsize)
    : _potential(potential),
    _coords(coords.copy()),
    _trial_coords(_coords.copy()), 
    _takestep(NULL),
    _nitercount(0), 
    _accept_count(0), 
    _E_reject_count(0),
    _conf_reject_count(0), 
    _success(true), 
    _print_progress(false), 
    _niter(0),
    _neval(0), 
    _stepsize(stepsize), 
    _temperature(temperature)
{
    _energy = compute_energy(_coords);
    _trial_energy = _energy;
    /*std::cout<<"mcrunner Energy is "<<_energy<< "\n";
    std::cout<<"mcrunner potential ptr is "<<_potential<< "\n";*/
}

/**
 * perform the configuration tests.  Stop as soon as one of them fails
 */
bool MC::do_conf_tests(Array<double> x)
{
    bool result;
    for (conf_t::iterator test1 = _conf_tests.begin(); test1 != _conf_tests.end(); ++test1){
        result = (*test1)->test(x, this);
        if (not result){
            ++_conf_reject_count;
            return false;
        }
    }
    return true;
}

/**
 * perform the acceptance tests.  Stop as soon as one of them fails
 */
bool MC::do_accept_tests(Array<double> xtrial, double etrial, Array<double> xold, double eold)
{
    bool result;
    for (accept_t::iterator test2 = _accept_tests.begin(); test2 != _accept_tests.end(); ++test2){
        result = (*test2)->test(xtrial, etrial, xold, eold, _temperature, this);
        if (not result){
            ++_E_reject_count;
            return false;
        }
    }
    return true;
}

void MC::one_iteration()
{
    _success = true;
    ++_niter;
    ++_nitercount;

    _trial_coords.assign(_coords);

    // take a step with the trial coords
    _takestep->takestep(_trial_coords, _stepsize, this);

    // perform the initial configuration tests
    _success = do_conf_tests(_trial_coords);

    // if the trial configuration is OK, compute the energy, and run the acceptance tests
    if (_success == true)
    {
        // compute the energy
        _trial_energy = compute_energy(_trial_coords);

        // perform the acceptance tests.  Stop as soon as one of them fails
        _success = do_accept_tests(_trial_coords, _trial_energy, _coords, _energy);
    }

    // Do some final checks to ensure the configuration is OK.
    // These come last because they might be computationally demanding.
    if (_success == true){
        for (conf_t::iterator test3 = _late_conf_tests.begin(); test3 != _late_conf_tests.end(); ++test3){
            _success = (*test3)->test(_trial_coords, this);
            if (_success == false){
                ++_conf_reject_count;
                break;
            }
        }
    }

    // if the step is accepted, copy the coordinates and energy
    if (_success == true){
        _coords.assign(_trial_coords);
        _energy = _trial_energy;
        ++_accept_count;
    }

    // perform the actions on the new configuration
    for (actions_t::iterator action1 = _actions.begin(); action1 != _actions.end(); ++action1){
        (*action1)->action(_coords, _energy, _success, this);
    }
}

void MC::check_input(){
    //std::cout << "_conf_tests.size(): " << _conf_tests.size() <<  "\n"; //debug
    //std::cout << "_late_conf_tests.size(): " << _late_conf_tests.size() <<  "\n"; //debug
    //std::cout << "_actions.size(): " << _actions.size() <<  "\n"; //debug
    //std::cout << "_accept_tests.size(): " << _accept_tests.size() <<  "\n"; //debug
    if (!take_step_specified()) throw std::runtime_error("MC::check_input: takestep not set");
    if (_conf_tests.size()==0) std::cout << "warning: no conf tests set" <<  "\n";
    if (_actions.size()==0) std::cout << "warning: no actions set" <<  "\n";
    if (_accept_tests.size()==0) std::cout << "warning: no accept tests set" <<  "\n";
}

void MC::run(size_t max_iter)
{
    check_input();
    progress stat(max_iter);
    while(_niter < max_iter){
        //std::cout << "done: " << double(_niter)/double(max_iter) <<  "\n";
        //std::cout << "_niter: " << _niter <<  "\n";
        //std::cout << "max_iter: " << max_iter <<  "\n";
        this->one_iteration();
        if (_print_progress) stat.next(_niter);
    }
    _niter = 0;
}

}//namespace mcpele
