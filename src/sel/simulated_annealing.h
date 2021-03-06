/* FEAT
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef SIMANNEAL_H
#define SIMANNEAL_H

#include "selection_operator.h"

namespace FT{

    namespace Sel{
        ////////////////////////////////////////////////////////////////////////////////// Declarations
        /*!
         * @class SimAnneal
         */
        struct SimAnneal : SelectionOperator
        {
            /** SimAnneal based selection and survival methods. */

            SimAnneal(bool surv);
            
            ~SimAnneal();
           
            vector<size_t> select(Population& pop, const MatrixXf& F, const Parameters& params);
            vector<size_t> survive(Population& pop, const MatrixXf& F, const Parameters& params);
        private:
            float t;           ///< annealing temperature
            float t0;          ///< initial temperature
        };
    }    
}
#endif
