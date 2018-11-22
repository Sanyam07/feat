/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#include "n_equal.h"
    	  
namespace FT{

    namespace Pop{
        namespace Op{ 	
            NodeEqual::NodeEqual()
            {
	            name = "=";
	            otype = 'b';
	            arity['f'] = 2;
	            complexity = 1;
            }

            /// Evaluates the node and updates the state states. 
            void NodeEqual::evaluate(const Data& data, State& state)
            {
                state.push<bool>(state.pop<double>() == state.pop<double>());
            }

            /// Evaluates the node symbolically
            void NodeEqual::eval_eqn(State& state)
            {
                state.push<bool>("(" + state.popStr<double>() + "==" + state.popStr<double>() + ")");
            }
            
            NodeEqual* NodeEqual::clone_impl() const { return new NodeEqual(*this); }

            NodeEqual* NodeEqual::rnd_clone_impl() const { return new NodeEqual(); }  
        }
    }
}