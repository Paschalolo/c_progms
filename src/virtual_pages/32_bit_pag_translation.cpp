
/*
 *	This shows how page translation works at the hardware level 
 *	Copyright Mr Paschal Ahanmisi 2024- 2026
 * */
#include <cstdint> 

/*
 *	For the 32 bit i will be using a flat page table 
 *	p1_entry 
 * 	*/

/*
 *	address -> 32 bits 
 *	Page Frame Number -> 20 bit 
 *	Page offset -> 12 bit 
 * */

using Page_table_entry = std::uint32_t*;


/* Function to get the physical address */ 
std::uint32_t get_physical_address(Page_table_entry pg_table , std::uint32_t v_addr){
	std::uint32_t offset = v_addr & 0xFFF; /* mask only 12 bits out of the address for the pffset */  
	std::uint32_t virtual_page_index  = (v_addr >> 12 ) ; /* mask only 12 bits out of the address for the pffset */  
	auto physical_page_frame = pg_table[virtual_page_index]; 

	std::uint32_t addr = (physical_page_frame << 12 )  | offset ;
	return addr;

}
