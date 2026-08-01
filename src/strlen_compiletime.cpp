
using size_t = unsigned long;
namespace pstd{

	consteval size_t strlen(const char* __restrict__ str){
		if(str == nullptr) {
			static_assert(false, "String is null or is dynamically allocated" );
		}
		size_t count {0}; 
		while(str[count] == '\0'){
			count++; 
		}
		return count ;
	} 
}; 
