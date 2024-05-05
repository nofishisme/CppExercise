#include <nofish_header.h>

void file_copy(const char* dest_file, const char* src_file) {
    FILE* ifs = fopen(src_file, "rb");
    ERROR_CHECK(ifs, NULL, "src_file open error.\n");
    FILE* ofs = fopen(dest_file, "wb");
    if(!ofs){
        perror("dest_file open error.\n");
        fclose(ifs);
        exit(1);
    }
    char* buff[1024];
    int readCount;
    while((readCount = fread(buff, 1, 1024, ifs)) > 0){
        fwrite(buff, 1, readCount, ofs);
    }
    fclose(ifs);
    fclose(ofs);
}

int main(int argc, char** argv)
{
    if(argc != 3){
        perror("please input: program dest_file src_file.\n");
        exit(1);
    }
    file_copy(argv[1],argv[2]);
    return 0;
}


