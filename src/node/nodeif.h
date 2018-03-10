/* FEWTWO
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef NODE_IF
#define NODE_IF

#include "node.h"

namespace FT{
	class NodeIf : public Node
    {
    	public:
    	   	
    		NodeIf()
    		{
    			name = "if";
    			otype = 'f';
    			arity['f'] = 1;
    			arity['b'] = 1;
    			complexity = 5;
    		}
    		
            /// Evaluates the node and updates the stack states. 
            void evaluate(const MatrixXd& X, const VectorXd& y, const vector<vector<ArrayXd> > &Z, 
			        Stacks& stack)
            {
                stack.f.push(stack.b.pop().select(stack.f.pop(),0));
            }

            /// Evaluates the node symbolically
            void eval_eqn(Stacks& stack)
            {
              string b = stack.bs.pop();
              string f = stack.fs.pop();
              stack.fs.push("if-then-else(" + stack.bs.pop() + "," + stack.fs.pop() + "," + "0)");
            }
    };
}	

#endif
