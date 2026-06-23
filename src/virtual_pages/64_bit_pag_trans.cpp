
#include <cstdint>
#include <filesystem>
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

__attribute__((always_inline)) std::uint64_t* physical_to_virtual(std::uint64_t addr){
		return reinterpret_cast<std::uint64_t*>(addr);
}

constexpr std::uint64_t PHYSICAL_PAGE_MASK = 0x000FFFFFFFFF000ULL;
constexpr std::uint64_t PRESENT_BIT = 0x01ULL;
constexpr std::uint64_t PAGE_BIT = 0x01ULL << 7 ; 
std::uint64_t get_physical_address(std::uint64_t cr3_phys , std::uint64_t v_addr ){
	auto p4_entry = (v_addr  >> 39U )    & 0x1FF ;
	auto p3_entry = (v_addr >> 30U ) & 0x1FF  ; 
	auto p2_entry = (v_addr >> 21U) & 0x1FF ;  
	auto p1_entry = (v_addr >> 12U) & 0x1FF; 
	
	/* Page 4 tab;e walk */ 
	auto p4_physical_addr = physical_to_virtual((cr3_phys & PHYSICAL_PAGE_MASK)); 
	auto p4e = p4_physical_addr[p4_entry];
	if(!(p4e & PRESENT_BIT)) return 0ULL ;

	/* p3 table walk */
	auto p3_physical_addr = physical_to_virtual((p4e & PHYSICAL_PAGE_MASK)); 
	auto p3e = p3_physical_addr[p3_entry];
	if(!(p3e & PRESENT_BIT)) return 0ULL ;

	/* check if 1 gb page table */ 
	if(p3e & PAGE_BIT){
		auto page1gb_offset = v_addr & 0x7FFFFFFF; 
		auto page1gb_physical_addr = p3e & 0xFFFFFC0000000ULL;
		return (page1gb_physical_addr | page1gb_offset); 
	}
	/*Branchless */
	/* 
	auto page1gb_offset = v_addr & 0x7FFFFFFF;                                                                   
   	auto page1gb_physical_addr = p3e & 0xFFFFFC0000000ULL;
	auto mask_1gb = static_cast<std::uint64_t>(static_cast<std::int64_t>(~(p3e & PAGE_BIT))  >> 1 )  ; 
*/
	/* p2 table walk */ 

	auto p2_physical_addr = physical_to_virtual((p3e & PHYSICAL_PAGE_MASK)); 
	auto p2e = p2_physical_addr[p2_entry];
	if(!(p2e & PRESENT_BIT)) return 0ULL ;
	/* check if 2mb page */ 
	if(PAGE_BIT & p2e){
		auto pg2mb_offset = p2e & 0x1FFFFFULL ; 
		auto pg2mb_address = p2e & 0xFFFFFFFFE0000ULL;
		return (pg2mb_address | pg2mb_offset);
	}
	

	auto p1_physical_addr = physical_to_virtual((p2e & PHYSICAL_PAGE_MASK)); 
	auto p1e = p1_physical_addr[p1_entry];
	if(!(p1e & PRESENT_BIT)) return 0ULL ;

	auto offset = v_addr & 0xFFF ; 
	auto phy_addr = v_addr & PHYSICAL_PAGE_MASK ; 
	return 	(phy_addr | offset ) ;
}
