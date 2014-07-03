#include "mc.h"
#include "progress.h"

namespace mcpele{

MC::MC(pele::BasePotential * potential, Array<double>& coords, double temperature, double stepsize):
            _potential(potential), _coords(coords.copy()),_trial_coords(_coords.copy()), _takestep(NULL),
			_nitercount(0), _accept_count(0), _E_reject_count(0), _conf_reject_count(0),
			_success(true), _print_progress(false), _niter(0), _neval(0), _stepsize(stepsize),
			_temperature(temperature)

		{
			_energy = _potential->get_energy(_coords);
			_trial_energy = _energy;
			++_neval;
			/*std::cout<<"mcrunner Energy is "<<_energy<<std::endl;
			std::cout<<"mcrunner potential ptr is "<<_potential<<std::endl;*/
		}

void MC::one_iteration()
{
    _success = true;
    ++_niter;
    ++_nitercount;

    _trial_coords.assign(_coords);

    // take a step with the trial coords
    _takestep->takestep(_trial_coords, _stepsize, this);

    // perform the initial configuration test
    //for (auto& test : _conf_tests ){
    for (conf_t::iterator test1 = _conf_tests.begin(); test1 != _conf_tests.end(); ++test1){
    //for (size_t test1 = 0; test1 != _conf_tests.size(); ++test1){
	//_success = test->test(_trial_coords, this);
	_success = (*test1)->test(_trial_coords, this);
	//_success = _conf_tests.at(test1)->test(_trial_coords, this);
	    if (_success == false){
		    ++_conf_reject_count;
		    break;
	    }
    }

    // if the trial configuration is OK, compute the energy, and run the acceptance tests
    if (_success == true)
    {
        // compute the energy
	    _trial_energy = _potential->get_energy(_trial_coords);
	    ++_neval;  // shouldn't this be in get_energy() ?

	    // perform the acceptance tests.  Stop as soon as one of them fails
	    for (accept_t::iterator test2 = _accept_tests.begin(); test2 != _accept_tests.end(); ++test2){
	    //for (size_t test2 = 0; test2 < _accept_tests.size(); ++test2){
		    _success = (*test2)->test(_trial_coords, _trial_energy, _coords, _energy, _temperature, this);
		    //_success = _accept_tests.at(test2)->test(_trial_coords, _trial_energy, _coords, _energy, _temperature, this);
		    if (_success == false){
			    ++_E_reject_count;
			    break;
		    }
	    }
    }

    // Do some final checks to ensure the configuration is OK.
    // These come last because they might be computationally demanding.
    if (_success == true){
        for (conf_t::iterator test3 = _late_conf_tests.begin(); test3 != _late_conf_tests.end(); ++test3){
        //for (size_t test3 = 0; test3 < _late_conf_tests.size(); ++test3){
            _success = (*test3)->test(_trial_coords, this);
            //_success = _late_conf_tests.at(test3)->test(_trial_coords, this);
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
    //for (size_t action1 = 0; action1 < _actions.size(); ++action1){
	(*action1)->action(_coords, _energy, _success, this);
	//_actions.at(action1)->action(_coords, _energy, _success, this);
    }
}

void MC::check_input(){
    //std::cout << "_conf_tests.size(): " << _conf_tests.size() << std::endl; //debug
    //std::cout << "_late_conf_tests.size(): " << _late_conf_tests.size() << std::endl; //debug
    //std::cout << "_actions.size(): " << _actions.size() << std::endl; //debug
    //std::cout << "_accept_tests.size(): " << _accept_tests.size() << std::endl; //debug
    if (!take_step_specified()) throw std::runtime_error("MC::check_input: takestep not set");
    if (_conf_tests.size()==0) std::cout << "warning: no conf tests set" << std::endl;
    if (_actions.size()==0) std::cout << "warning: no actions set" << std::endl;
    if (_accept_tests.size()==0) std::cout << "warning: no accept tests set" << std::endl;
}

void MC::run(size_t max_iter)
{
    check_input();
    progress stat(max_iter);
    while(_niter < max_iter){
	//std::cout << "done: " << double(_niter)/double(max_iter) << std::endl;
	//std::cout << "_niter: " << _niter << std::endl;
	//std::cout << "max_iter: " << max_iter << std::endl;
	this->one_iteration();
	if (_print_progress) stat.next(_niter);
    }
    _niter = 0;
}

}//namespace mcpele