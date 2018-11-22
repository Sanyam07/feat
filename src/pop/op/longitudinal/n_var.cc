/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/

#include "n_var.h"
#include "../../../util/utils.h"
    	
namespace FT{

    namespace Pop{
        namespace Op{
            NodeVar::NodeVar()
            {
                name = "variance";
	            otype = 'f';
	            arity['z'] = 1;
	            complexity = 1;
            }

            /// Evaluates the node and updates the state states. 
            void NodeVar::evaluate(const Data& data, State& state)
            {
                ArrayXd tmp(state.z.top().first.size());
                
                int x;
                ArrayXd tmp1;
                
                for(x = 0; x < state.z.top().first.size(); x++)
                    tmp(x) = variance(limited(state.z.top().first[x]));
                    
                state.z.pop();

                state.push<double>(tmp);
                
            }

            /// Evaluates the node symbolically
            void NodeVar::eval_eqn(State& state)
            {
                state.push<double>("variance(" + state.zs.pop() + ")");
            }

            NodeVar* NodeVar::clone_impl() const { return new NodeVar(*this); }

            NodeVar* NodeVar::rnd_clone_impl() const { return new NodeVar(); } 
        }
    }

}