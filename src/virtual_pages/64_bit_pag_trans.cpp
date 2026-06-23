
#include <cstdint>
/*
 *	Logic for 64 bit page translation 
 *	NOte 64 bit has  4 page traanslation levels 
 *
 * */

/*
 *	64 bits -> address 
 *	bits 63 - 48 -> sign extension bits 
 *	p4 entry -> 9 bits 
 *	p3 entry -> 9 bits
 *	p2 -> 9 bits 
 *	p1 entry -> 9 bits 
 *	page_offser -> 12 bits 
 * */

// CR3 register contains the p4 entry array 
std::uint64_t get_physical_address(std::uint64_t** cr3 , std::uint64_t v_addr ){
	if (!cr3) return 0U ;
	auto p4_entry = (v_addr  >> 39U )    & 0x1FF ;
	auto p3_entry = (v_addr >> 30U ) & 0x1FF  ; 
	auto p2_entry = (v_addr >> 21U) & 0x1FF ;  
	auto p1_entry = (v_addr >> 12U) & 0x1FF; 
	auto offset = (v_addr ) & 0xFFF ;
	
	auto pg_addr4 = cr3[p4_entry] ; /* page 4 table walk */ 
	auto pg_addr3 = reinterpret_cast<std::uint64_t*>(pg_addr4)[p3_entry] ;  /* page 4 table walk */ 
	auto pg_addr2 = reinterpret_cast<std::uint64_t*>(pg_addr3)[p2_entry] ;  /* page 4 table walk */ 
	auto physical_page_frame = reinterpret_cast<std::uint64_t*>(pg_addr2)[p1_entry]; /* page 4 table walk */ 
	
	return 	((physical_page_frame << 12 ) | offset ) ;
}
