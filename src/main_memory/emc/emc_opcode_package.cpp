#include "simulator.hpp"
#include <string>

// ========================================================================== //

emc_opcode_package_t::emc_opcode_package_t(){

	this->package_clean();
	this->reg_deps_ptr_array = NULL;
};

// -------------------------------------------------------------------------- //

emc_opcode_package_t::~emc_opcode_package_t(){

	utils_t::template_delete_array<emc_opcode_package_t*>(reg_deps_ptr_array);
};

// -------------------------------------------------------------------------- //

void emc_opcode_package_t::package_clean(){

	this->uop.package_clean();
	this->mob_ptr = NULL;
	this->wait_reg_deps_number=0;
	this->wake_up_elements_counter=0;
	this->rob_ptr = NULL;
	this->stage = PROCESSOR_STAGE_RENAME;
};

// -------------------------------------------------------------------------- //

std::string emc_opcode_package_t::content_to_string(){
	std::string content_string;
	content_string = "";

	content_string = this->uop.content_to_string();
	content_string = content_string + " | Stage:" + get_enum_processor_stage_char(this->stage);
	content_string = content_string + " | Reg.Wait:" + utils_t::uint32_to_string(this->wait_reg_deps_number);
	content_string = content_string + " | WakeUp:" + utils_t::uint32_to_string(this->wake_up_elements_counter);
	content_string = content_string + " | ReadyAt: " + utils_t::uint64_to_string(this->uop.readyAt);
	//content_string = content_string + " | Rob Pointer: " + utils_t::pointer_rob_to_string(this->rob_ptr);

	if(this->mob_ptr != NULL){
		content_string = content_string + this->mob_ptr->content_to_string();
	}

	return content_string;
};

// ========================================================================== //
