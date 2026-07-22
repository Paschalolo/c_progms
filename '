/* Short doc on diffrent bits implemetation */ 

#define GET_MASK(n) ((1ULL << static_cast<size_t>(n) ) - 1 )
#define ALIGNED_ADDR(addr , align) ((addr + addr -1 )   &  ~(align -1))
#define TWO_REG_FAST_SWAP(x, y) ( x = x ^ y ; y = x^ y ; x = x ^ y;)
