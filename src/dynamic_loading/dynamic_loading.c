#include <elf.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
struct Symbols{
	void* file ; 
	size_t sz ; 
};

static struct  Symbols ssy = {NULL, 0};
enum P_ERRORS : int{
	SUCCESS = 0,
	FAILED = -1,
	FILENOTOPEN = -2 
};
int load_libary(const char* __restrict__ name ){
	struct stat stbuf = {};
	int fd = open(name ,  O_RDONLY );
	if(fd == -1){
		return FILENOTOPEN;	
		
	}
	if(fstat(fd, &stbuf)== -1){
	close(fd); 
		return FAILED;
	}
	off_t  sz = stbuf.st_size ; 
	void* ptr = mmap(NULL ,(size_t) sz ,(PROT_EXEC  | PROT_READ),MAP_PRIVATE  ,fd , 0 );
	if( ptr == MAP_FAILED){
		close(fd);
		return FAILED;
	}
	ssy.file = ptr;
	ssy.sz = (size_t)sz; 
	 close(fd);
	return SUCCESS;
}
void* pdy_symbol(const char* __restrict__ sym) {
    if (!ssy.file) return NULL;

    Elf64_Ehdr* elf_file = (Elf64_Ehdr*)ssy.file;
    
    // Get the base address of the section header table
    Elf64_Shdr* shdr_table = (Elf64_Shdr*)((char*)elf_file + (elf_file->e_shoff));
    size_t shnum = (size_t)(elf_file->e_shnum); 
    
    Elf64_Shdr* dynsym_shdr = NULL;
    Elf64_Sym* dynsym_table = NULL;
    size_t dyn_count = 0; 
    
    // Look for the Dynamic Symbol Table
    for(size_t i = 0; i < shnum; i++) {
        if(shdr_table[i].sh_type == SHT_DYNSYM) {
            dynsym_shdr = &shdr_table[i];
            dynsym_table = (Elf64_Sym*)((char*)elf_file + dynsym_shdr->sh_offset);
            dyn_count = dynsym_shdr->sh_size / dynsym_shdr->sh_entsize;
            break;
        }
    }
    
    if(dynsym_table == NULL || dynsym_shdr == NULL) {
        return NULL;
    }
    
    // FIX: The string table for .dynsym is located via the .dynsym section's sh_link
    uint32_t strtab_idx = dynsym_shdr->sh_link;
    char* string_table = (char*)((char*)elf_file + shdr_table[strtab_idx].sh_offset); 
    
    void* addr = NULL;
    for(size_t i = 0; i < dyn_count; i++) {
        // ELF64_ST_TYPE parses the st_info field correctly
        if(ELF64_ST_TYPE(dynsym_table[i].st_info) == STT_FUNC || ELF64_ST_TYPE(dynsym_table[i].st_info) == STT_NOTYPE) {
            uint32_t index = dynsym_table[i].st_name;
            
            if(strcmp(sym, &string_table[index]) == 0) {
                // Note: For shared libraries (.so), st_value is a relative offset.
                // For executables compiled without PIE, it might be an absolute address.
                addr = (void*)((char*)elf_file + dynsym_table[i].st_value);
                break;
            }
        }
    }

    return addr;
}
int close_libary(){
	if(ssy.file == NULL){return SUCCESS;}
	int err = 0 ; 
	void* ptr = ssy.file; 
	err = munmap(ptr, ssy.sz);
	if(err == -1 ){return FAILED; }
	ssy.file = NULL ; 
	ssy.sz = 0;
	return SUCCESS;
}

