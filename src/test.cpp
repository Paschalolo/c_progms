
#include <iostream>
#include <ostream>
class Jet{
	public :
		explicit Jet(int a , int b): m_a(a) , m_b(b){
			std::cout << "jet()";
		}
		explicit Jet(Jet&& jt):m_a(jt.m_a), m_b(jt.m_b){
			std::cout << "Jet&&";
		}
		friend std::ostream& operator<<(std::ostream& os , const Jet& jt){
			os << jt.m_b; 
			return os;
		}
	private :
		int m_a ; 
		int m_b;
};

int main(){
	Jet a{90,32};
	std::cout << std::move(a);
	std::cout << Jet{32,33};
	
	return 0 ;
}
