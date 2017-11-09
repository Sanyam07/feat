/* FEWTWO
copyright 2017 William La Cava
license: GNU/GPL v3
*/
#ifndef PARAMS_H
#define PARAMS_H
// internal includes
#include "nodewrapper.h"

namespace FT{

    ////////////////////////////////////////////////////////////////////////////////// Declarations
    /*!
     * @class Parameters
     * @brief holds the hyperparameters for Fewtwo. 
     */
    struct Parameters
    {
        int pop_size;                   			///< population size
        int gens;                       			///< max generations
        string ml;                      			///< machine learner with which Fewtwo is paired
        bool classification;            			///< flag to conduct classification rather than 
        int max_stall;                  			///< maximum stall in learning, in generations
        vector<char> otypes;                     	///< program output types ('f', 'b')
        int verbosity;                  			///< amount of printing. 0: none, 1: minimal, 
                                                    // 2: all
        vector<double> term_weights;    			///< probability weighting of terminals
        vector<std::shared_ptr<Node>> functions;    ///< function nodes available in programs
        vector<std::shared_ptr<Node>> terminals;    ///< terminal nodes available in programs
        unsigned int max_depth;         			///< max depth of programs
        unsigned int max_size;          			///< max size of programs (length)
        unsigned int max_dim;           			///< maximum dimensionality of programs
        bool erc;								    ///<whether to include constants for terminals 
        unsigned num_features;                      ///< number of features
        vector<string> objectives;                  ///< Pareto objectives 
        bool shuffle;                               ///< option to shuffle the data
        double split;                               ///< fraction of data to use for training

        Parameters(int pop_size, int gens, string& ml, bool classification, int max_stall, 
                   char otype, int verbosity, string fs, unsigned int max_depth, 
                   unsigned int max_dim, bool constant, string obj, bool sh, double sp):    
            pop_size(pop_size),
            gens(gens),
            ml(ml),
            classification(classification),
            max_stall(max_stall), 
            verbosity(verbosity),
            max_depth(max_depth),
            max_dim(max_dim),
            erc(constant),
            shuffle(sh),
            split(sp)
        {
            set_functions(fs);
            set_objectives(obj);
            updateSize();        
            switch (otype)
            { 
                case 'b': otypes.push_back('b'); break;
                case 'f': otypes.push_back('f'); break;
                default: 
                {
                    for (const auto& f: functions)
                        if (!in(otypes,f->otype)) 
                            otypes.push_back(f->otype);
                    for (const auto& t: terminals)
                        if (!in(otypes,t->otype)) 
                            otypes.push_back(t->otype);

                    break;
                }
            }

        }
        
        ~Parameters(){}

        /// print message with verbosity control. 
        void msg(string m, int v, string sep="\n") const
        {
            /* prints messages based on verbosity level. */

            if (verbosity >= v)
                std::cout << m << sep;
        }
        
        /// sets weights for terminals. 
        void set_term_weights(const vector<double>& w)
        {
            std::cout << "w size: " << w.size() << "\n";
            std::cout << "terminals size: " << terminals.size() << "\n";
            assert(w.size()==terminals.size());
            term_weights = w; 
        }
        
        /// return shared pointer to a node based on the string passed
        std::shared_ptr<Node> createNode(std::string str, double d_val = 0, bool b_val = false, 
                                         size_t loc = 0);
        
        /// sets available functions based on comma-separated list.
        void set_functions(string fs);
        
        /// max_size is max_dim binary trees of max_depth
        void updateSize()
        {
        	max_size = (pow(2,max_depth+1)-1)*max_dim;
        }
        
        /// set max depth of programs
        void set_max_depth(unsigned int max_depth)
        {
        	this->max_depth = max_depth;
        	updateSize();
        }
        
        /// set maximum dimensionality of programs
        void set_max_dim(unsigned int max_dim)
        {
        	this->max_dim = max_dim;
        	updateSize();
        }
        
        /// set the terminals
        void set_terminals(int nf);

        /// set the objectives
        void set_objectives(string obj);   

    };

    /////////////////////////////////////////////////////////////////////////////////// Definitions
    
    std::shared_ptr<Node> Parameters::createNode(string str, double d_val, bool b_val, size_t loc)
    {
        // algebraic operators
    	if (str.compare("+") == 0) 
    		return std::shared_ptr<Node>(new NodeAdd());
        
        else if (str.compare("-") == 0)
    		return std::shared_ptr<Node>(new NodeSubtract());

        else if (str.compare("*") == 0)
    		return std::shared_ptr<Node>(new NodeMultiply());

     	else if (str.compare("/") == 0)
    		return std::shared_ptr<Node>(new NodeDivide());

        else if (str.compare("sqrt") == 0)
    		return std::shared_ptr<Node>(new NodeSqrt());
    	
    	else if (str.compare("sin") == 0)
    		return std::shared_ptr<Node>(new NodeSin());
    		
    	else if (str.compare("cos") == 0)
    		return std::shared_ptr<Node>(new NodeCos());
    	   
        else if (str.compare("^2") == 0)
    		return std::shared_ptr<Node>(new NodeSquare());
 	
        else if (str.compare("^3") == 0)
    		return std::shared_ptr<Node>(new NodeCube());
    	
        else if (str.compare("^") == 0)
    		return std::shared_ptr<Node>(new NodeExponent());

        else if (str.compare("exp") == 0)
    		return std::shared_ptr<Node>(new NodeExponential());

        else if (str.compare("log") == 0)
    		return std::shared_ptr<Node>(new NodeLog());   

        // logical operators
        else if (str.compare("and") == 0)
    		return std::shared_ptr<Node>(new NodeAnd());
       
    	else if (str.compare("or") == 0)
    		return std::shared_ptr<Node>(new NodeOr());
   		
     	else if (str.compare("not") == 0)
    		return std::shared_ptr<Node>(new NodeNot());
   		
    	else if (str.compare("=") == 0)
    		return std::shared_ptr<Node>(new NodeEqual());
    		
        else if (str.compare(">") == 0)
    		return std::shared_ptr<Node>(new NodeGreaterThan());

    	else if (str.compare(">=") == 0)
    		return std::shared_ptr<Node>(new NodeGEQ());        

    	else if (str.compare("<") == 0)
    		return std::shared_ptr<Node>(new NodeLessThan());
    	
    	else if (str.compare("<=") == 0)
    		return std::shared_ptr<Node>(new NodeLEQ());
    	
     	else if (str.compare("if") == 0)
    		return std::shared_ptr<Node>(new NodeIf());   	    		
        	
    	else if (str.compare("ite") == 0)
    		return std::shared_ptr<Node>(new NodeIfThenElse());

        // variables and constants
        else if (str.compare("x") == 0)
            return std::shared_ptr<Node>(new NodeVariable(loc));
            
        else if (str.compare("kb")==0)
            return std::shared_ptr<Node>(new NodeConstant(b_val));
            
        else if (str.compare("kd")==0)
            return std::shared_ptr<Node>(new NodeConstant(d_val));
            
        else
        {
            std::cerr << "Error: no node named " << str << " exists.\n"; 
            throw;
        }
        //TODO: add squashing functions, time delay functions, and stats functions
    	
    }

    void Parameters::set_functions(string fs)
    {
        /*! 
         * Input: 
         *
         *		fs: string of comma-separated Node names
         *
         * Output:
         *
         *		modifies functions 
         *
         */
        fs += ',';          // add delimiter to end 
        string delim = ",";
        size_t pos = 0;
        string token;
        functions.clear();
        while ((pos = fs.find(delim)) != string::npos) 
        {
            token = fs.substr(0, pos);
            functions.push_back(createNode(token));
            fs.erase(0, pos + delim.length());
        } 
        if (verbosity > 1){
            std::cout << "functions set to [";
            for (auto f: functions) std::cout << f->name << ", "; 
            std::cout << "]\n";
        }
    }

    void Parameters::set_terminals(int nf)
    {
        /*!
         * based on number of features.
         */
        num_features = nf; 
        for (size_t i = 0; i < nf; ++i)
            terminals.push_back(createNode(string("x"), 0, 0, i));
    	
        if(erc)
    		for (int i = 0; i < nf; ++i)
    		{
    			if(r() < 0.5)
    	       		terminals.push_back(createNode(string("kb"), 0, r(), 0));
    	       	else
    	       		terminals.push_back(createNode(string("kd"), r(), 0, 0));
    	    }                
    }

    void Parameters::set_objectives(string obj)
    {
        /*! Input: obj, a comma-separated list of objectives
         */

        obj += ',';          // add delimiter to end 
        string delim = ",";
        size_t pos = 0;
        string token;
        while ((pos = obj.find(delim)) != string::npos) 
        {
            token = obj.substr(0, pos);
            objectives.push_back(token);
            obj.erase(0, pos + delim.length());
        }
    }
}
#endif
