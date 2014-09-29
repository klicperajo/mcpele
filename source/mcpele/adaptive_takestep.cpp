#include "adaptive_takestep.h"

namespace mcpele {

AdaptiveTakeStep::AdaptiveTakeStep(std::shared_ptr<TakeStep> ts, const size_t interval)
    : m_ts(ts),
      m_interval(interval),
      m_total_steps(0),
      m_accepted_steps(0)
{}

void AdaptiveTakeStep::report(pele::Array<double>& old_coords,
        const double old_energy, pele::Array<double>& new_coords,
        const double new_energy, const bool success, MC* mc)
{
    ++m_total_steps;
    if (success) {
        ++m_accepted_steps;
    }
    if (mc->get_iterations_count() % m_interval == 0) {
        const double acceptance_fraction = static_cast<double>(m_accepted_steps) / static_cast<double>(m_total_steps);
        m_accepted_steps = 0;
        m_total_steps = 0;
        if (acceptance_fraction < get_min_acceptance_ratio()) {
            m_ts->increase_acceptance();
        }
        else if (acceptance_fraction > get_max_acceptance_ratio()) {
            m_ts->decrease_acceptance();
        }
    }
}

} // namespace mcpele
