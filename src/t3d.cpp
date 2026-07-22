#include <cstdio> 
#include <climits>

int main(){
	constexpr int val = INT_MAX ; 
	constexpr int tpd /* Represents the ticks per day */ = 100 * 60 * 60 * 24 ;
	constexpr int days_till_overflow = val/tpd ; 
	std::printf("Days untill overflow : %d", days_till_overflow);
	return 0;
}
