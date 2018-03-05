/* FEWTWO
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef NODE_TANH
#define NODE_TANH

#include "node.h"

namespace FT{
	class NodeTanh : public Node
    {
    	public:
    	
    		NodeTanh()
            {
                name = "tanh";
    			otype = 'f';
    			arity['f'] = 1;
    			arity['b'] = 0;
    			complexity = 3;
    		}
    		
            /// Evaluates the node and updates the stack states. 
            void evaluate(const MatrixXd& X, const VectorXd& y, const vector<vector<ArrayXd> > &Z, 
			        vector<ArrayXd>& stack_f, vector<ArrayXb>& stack_b, vector<vector<ArrayXd> > &stack_z)
			{
        		ArrayXd x = stack_f.back(); stack_f.pop_back();
                stack_f.push_back(limited(tanh(x)));
            }

            /// Evaluates the node symbolically
            void eval_eqn(vector<string>& stack_f, vector<string>& stack_b, vector<string>& stack_z)
            {
        		string x = stack_f.back(); stack_f.pop_back();
                stack_f.push_back("tanh(" + x + ")");
            }
    };
}	

#endif
