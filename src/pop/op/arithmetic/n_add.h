/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef NODE_ADD
#define NODE_ADD

#include "../n_Dx.h"

namespace FT{

    namespace Pop{
        namespace Op{
        	class NodeAdd : public NodeDx
            {
            	public:
            	
            		NodeAdd(vector<double> W0 = vector<double>());
            		    		
                    /// Evaluates the node and updates the state states. 
                    void evaluate(const Data& data, State& state);
			
                    /// Evaluates the node symbolically
                    void eval_eqn(State& state);

                    ArrayXd getDerivative(Trace& state, int loc);

                protected:
                    NodeAdd* clone_impl() const override;
              
                    NodeAdd* rnd_clone_impl() const override;
            };
        }
    }
}	

#endif