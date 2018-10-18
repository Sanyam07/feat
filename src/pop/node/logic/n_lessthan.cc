/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#include "n_lessthan.h"

namespace FT{

    namespace Pop{
        namespace NodeSpace{
        
            NodeLessThan::NodeLessThan()
            {
	            name = "<";
	            otype = 'b';
	            arity['f'] = 2;
	            complexity = 2;
            }

            /// Evaluates the node and updates the stack states. 
            void NodeLessThan::evaluate(const Data& data, Stacks& stack)
            {
                ArrayXd x1 = stack.pop<double>();
                ArrayXd x2 = stack.pop<double>();
                stack.push<bool>(x1 < x2);
            }

            /// Evaluates the node symbolically
            void NodeLessThan::eval_eqn(Stacks& stack)
            {
                stack.push<bool>("(" + stack.popStr<double>() + "<" + stack.popStr<double>() + ")");
            }
            
            NodeLessThan* NodeLessThan::clone_impl() const { return new NodeLessThan(*this); }

            NodeLessThan* NodeLessThan::rnd_clone_impl() const { return new NodeLessThan(); }  
            
        }
    }
}
