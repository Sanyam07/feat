/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/

#include "n_mean.h"
    	
namespace FT{

    namespace Pop{
        namespace Op{
            NodeMean::NodeMean()
            {
                name = "mean";
	            otype = 'f';
	            arity['z'] = 1;
	            complexity = 1;
            }

            /// Evaluates the node and updates the state states. 
            void NodeMean::evaluate(const Data& data, State& state)
            {
                ArrayXd tmp(state.z.top().first.size());
                int x;
                
                for(x = 0; x < state.z.top().first.size(); x++)
                    tmp(x) = limited(state.z.top().first[x]).mean();
                  
                state.z.pop();
                
                state.push<double>(tmp);
                
            }

            /// Evaluates the node symbolically
            void NodeMean::eval_eqn(State& state)
            {
                state.push<double>("mean(" + state.zs.pop() + ")");
            }
            
            NodeMean* NodeMean::clone_impl() const { return new NodeMean(*this); }

            NodeMean* NodeMean::rnd_clone_impl() const { return new NodeMean(); } 
        }
    }
}