/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#include "n_constant.h"
    		
namespace FT{

    namespace Pop{
        namespace Op{

            NodeConstant::NodeConstant()
            {
                HANDLE_ERROR_THROW("error in nodeconstant.h : invalid constructor called");
            }

            /// declares a boolean constant
            NodeConstant::NodeConstant(bool& v)
            {
	            name = "k_b";
	            otype = 'b';
	            complexity = 1;
	            b_value = v;
            }

            /// declares a double constant
            NodeConstant::NodeConstant(const double& v)
            {
	            name = "k_d";
	            otype = 'f';
	            complexity = 1;
	            d_value = v;
            }

            /// Evaluates the node and updates the state states. 
            void NodeConstant::evaluate(const Data& data, State& state)
            {
	            if (otype == 'b')
                    state.push<bool>(ArrayXb::Constant(data.X.cols(),int(b_value)));
                else 	
                    state.push<double>(limited(ArrayXd::Constant(data.X.cols(),d_value)));
            }

            /// Evaluates the node symbolically
            void NodeConstant::eval_eqn(State& state)
            {
	            if (otype == 'b')
                    state.push<bool>(std::to_string(b_value));
                else 	
                    state.push<double>(std::to_string(d_value));
            }
            
            NodeConstant* NodeConstant::clone_impl() const { return new NodeConstant(*this); }
              
            NodeConstant* NodeConstant::rnd_clone_impl() const { return new NodeConstant(); };
            
        }
    }
}