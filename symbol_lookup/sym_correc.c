#include <elf.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define SCRATCH_BUF_SIZE (1024 * 20)

void print_symbols_table(const char* __restrict__ str_buf, size_t str_sz, const Elf64_Sym* sym_tb, size_t sz_sym) {
    size_t count = sz_sym / sizeof(Elf64_Sym);
    for (size_t i = 0; i < count; i++) {
        uint32_t name_offset = sym_tb[i].st_name;
        
        // Prevent Out-of-Bounds Read
        if (name_offset < str_sz) {
            // Only print if the symbol actually has a name string assigned
            if (name_offset != 0 && *(str_buf + name_offset) != '\0') {
                printf("[%lu] Symbol Name: %s\n", i, (str_buf + name_offset));
            }
        } else {
            fprintf(stderr, "[Warning] Symbol %lu has an out-of-bounds name offset!\n", i);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <elf_executable>\n", argv[0]);
        return -1; 
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -2;
    }

    char* buffer = (char*)aligned_alloc(8, SCRATCH_BUF_SIZE);
    if (!buffer) {
        perror("Allocation failed");
        close(fd);
        return -2;
    }

    // 1. Read ELF Header
    ssize_t ret = read(fd, buffer, sizeof(Elf64_Ehdr));
    if (ret != sizeof(Elf64_Ehdr)) {
        fprintf(stderr, "Failed to read ELF Header\n");
        free(buffer);
        close(fd);
        return -2;
    }

    Elf64_Ehdr* elf_ed = (Elf64_Ehdr*)buffer;
    Elf64_Off section_offset = elf_ed->e_shoff; 
    uint16_t nsec_Entries = elf_ed->e_shnum; 
    size_t sec_sz = (size_t)elf_ed->e_shentsize; 

    // Prevent Buffer Overflow
    size_t total_sec_hdr_sz = (size_t)nsec_Entries * sec_sz;
    if (total_sec_hdr_sz > SCRATCH_BUF_SIZE) {
        fprintf(stderr, "Section headers section too large for scratch buffer\n");
        free(buffer);
        close(fd);
        return -3;
    }

    // 2. Read Section Headers
    if (lseek(fd, (off_t)section_offset, SEEK_SET) == -1) {
        perror("lseek to section headers failed");
        free(buffer);
        close(fd);
        return -3;
    }

    ret = read(fd, buffer, total_sec_hdr_sz);
    if (ret != (ssize_t)total_sec_hdr_sz) {
        fprintf(stderr, "Failed to read complete section headers\n");
        free(buffer);
        close(fd);
        return -3;
    }

    Elf64_Shdr* section_buf = (Elf64_Shdr*)buffer;
    uint64_t symboltb_size = 0;
    uint64_t symboltb_offset = 0;
    size_t string_offset = 0;
    size_t string_table_sz = 0;

    // 3. Locate the Symbol Table and dynamically find its linked String Table (.strtab)
    for (size_t i = 0; i < nsec_Entries; i++) {
        if (section_buf[i].sh_type == SHT_SYMTAB) {
            symboltb_size = section_buf[i].sh_size;
            symboltb_offset = section_buf[i].sh_offset;
            
            // sh_link holds the section index of the correct string table
            uint32_t strtab_idx = section_buf[i].sh_link; 
            if (strtab_idx < nsec_Entries) {
                string_offset = (size_t)section_buf[strtab_idx].sh_offset;
                string_table_sz = (size_t)section_buf[strtab_idx].sh_size;
            }
            break;
        }
    }

    if (symboltb_size == 0 || symboltb_offset == 0 || string_table_sz == 0) {
        fprintf(stderr, "Required symbol or string tables not found\n");
        free(buffer);
        close(fd);
        return -3; 
    }

    // 4. Align sizes to 64 bytes to satisfy aligned_alloc constraints safely
    size_t aligned_str_sz = (string_table_sz + 63) & ~63UL;
    size_t aligned_sym_sz = (symboltb_size + 63) & ~63UL;

    // 5. Read String Table safely
    char* str_table = (char*)aligned_alloc(64, aligned_str_sz);
    if (!str_table) {
        perror("Failed to allocate string table");
        free(buffer);
        close(fd);
        return -2;
    }

    if (lseek(fd, (off_t)string_offset, SEEK_SET) == -1) {
        perror("lseek to string table failed");
        free(str_table);
        free(buffer);
        close(fd);
        return -2;
    }

    ret = read(fd, str_table, string_table_sz);
    if (ret != (ssize_t)string_table_sz) {
        fprintf(stderr, "Failed read of string table\n");
        free(str_table);
        free(buffer);
        close(fd);
        return -2;
    }

    // 6. Read Symbol Table safely
    Elf64_Sym* sym_table = (Elf64_Sym*)aligned_alloc(64, aligned_sym_sz);
    if (!sym_table) {
        perror("Failed to allocate symbol table");
        free(str_table);
        free(buffer);
        close(fd);
        return -2;
    }

    if (lseek(fd, (off_t)symboltb_offset, SEEK_SET) == -1) {
        perror("lseek to symbol table failed");
        free(sym_table);
        free(str_table);
        free(buffer);
        close(fd);
        return -2;
    }

    ret = read(fd, (void*)sym_table, symboltb_size);
    if (ret != (ssize_t)symboltb_size) {
        fprintf(stderr, "Failed read of symbol table\n");
        free(sym_table);
        free(str_table);
        free(buffer);
        close(fd);
        return -2;
    }

    // 7. Output correct symbol names
    print_symbols_table(str_table, string_table_sz, sym_table, symboltb_size); 

    // Clean up
    free(str_table);
    free(sym_table);
    free(buffer);
    close(fd);
    
    return 0;
}
