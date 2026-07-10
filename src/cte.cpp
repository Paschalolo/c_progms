#include <type_traits>
#include <new> 
#include <iostream>
class HUgeClass{
	public : 
		HUgeClass(double f , int p , int j , bool b=false )noexcept: m_data(f), joy(p), pain(j) , mm(b){
			std::cout << "default constructor";
		}
		HUgeClass& operator=(HUgeClass&& hg ){
			m_data= hg.m_data; joy = hg.joy; pain =hg.pain;
			std::cout << "&& hugeclass";
			return *this;
		}
		friend std::ostream& operator<<(std::ostream& os , const HUgeClass & hg){
			os<< hg.pain << hg.m_data ; 
			return os;
		}
		int verify_hardware() noexcept {
			if(m_data < std::abs(0.0f))return -1;
			mm = true ; 
			return 0; 
		}
	private :
		double m_data ; 
		int joy; 
		int pain ;
		bool mm;

};

template <typename T > 
class FastAccess{
	private : 
		alignas(T) char m_data[sizeof(T)]{0}; 
	public : 
		FastAccess( ) = default;

		template <typename ... Args> 
		requires std::is_constructible_v<T,Args...>
		void write(Args&&... args) noexcept {
			new (reinterpret_cast<void*>(m_data)) T{std::forward<Args>(args)...};
		}
		const T* get() const{
			return reinterpret_cast<const T*>(m_data);
		}
		T* get() {
			return reinterpret_cast< T*>(m_data);
		}
		T* operator->(){
			return get();
		}
		void destroy()noexcept {
			if constexpr(!std::is_trivially_destructible_v<T>){
			reinterpret_cast<T*>(m_data)->~T();
			}
		}
};

__attribute__((used)) void func(auto & hg)noexcept{
		// bus down 
		hg.write(100.0f, 11, 22);
		
	};
int main(){
	FastAccess<HUgeClass> hug{};
	func(hug); 
	auto rc = hug->verify_hardware();
	if(rc){
			goto err_return ;
			
	}
	std::cout << static_cast<HUgeClass&>(*hug.get());
 
	hug.destroy();
err_return :
	return 0;
}
