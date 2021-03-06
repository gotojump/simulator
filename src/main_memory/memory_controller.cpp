#include "simulator.hpp"
#include <string>

// ========================================================================== //

memory_controller_t::memory_controller_t(){

	this->emc = NULL;
	this->requests_made = 0;
	this->operations_executed = 0;
	this->requests_emc = 0;
	this->requests_llc = 0;
};

// -------------------------------------------------------------------------- //

memory_controller_t::~memory_controller_t() = default;

// -------------------------------------------------------------------------- //

void memory_controller_t::allocate(){

	#if EMC_ACTIVE
	this->emc = new emc_t;
	this->emc->allocate();
	#endif
};

// -------------------------------------------------------------------------- //

void memory_controller_t::statistics(){
	FILE *output = stdout;

	if(orcs_engine.output_file_name != NULL)
		output = fopen(orcs_engine.output_file_name,"a+");

	if(output != NULL){
		utils_t::largestSeparator(output);
		fprintf(output,"Memory Controller\n");
		utils_t::largestSeparator(output);
		fprintf(output,"Requests_Made %lu\n",this->get_requests_made());
		fprintf(output,"Requests_from_LLC %lu\n",this->get_requests_llc());
		fprintf(output,"Requests_from_EMC %lu\n",this->get_requests_emc());
		utils_t::largestSeparator(output);

		#if EMC_ACTIVE
		this->emc->statistics();
		#endif
	}

	if( output != NULL && output != stdout )
		fclose(output);
};

// -------------------------------------------------------------------------- //

void memory_controller_t::clock(){

	#if EMC_ACTIVE
	this->emc->clock();
	#endif
};

// -------------------------------------------------------------------------- //

uint64_t memory_controller_t::requestDRAM(){

	this->add_requests_made();
	return RAM_LATENCY;
};

// ========================================================================== //
