#include <nofish_header.h>

void list_dir(char* dirname){
    DIR* dirstream = opendir(dirname);
    ERROR_CHECK(dirstream, NULL,"opendir");
    struct dirent* pdirent;
    long loc;
    while((pdirent = readdir(dirstream)) != NULL) {
        printf("inode num = %lu, len of item = %hu, type = %u, name = %s\n",
               pdirent->d_ino,
               pdirent->d_reclen,
               pdirent->d_type,
               pdirent->d_name);
        if(strcmp(pdirent->d_name, ".") == 0){
            loc = telldir(dirstream);
        }
    }
    printf("------------------------------------------\n");
    seekdir(dirstream, loc);
    pdirent = readdir(dirstream);
    printf("inode num = %lu, len of item = %hu, type = %u, name = %s\n",
           pdirent->d_ino,
           pdirent->d_reclen,
           pdirent->d_type,
           pdirent->d_name);
    closedir(dirstream);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 2);
    list_dir(argv[1]);
    return 0;
}


