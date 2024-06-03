#include <nofish_header.h>
void my_la(const char* filepath){
    DIR* pdir = opendir(filepath);

    struct dirent* pdirent;

    while((pdirent = readdir(pdir)) != NULL) {
        if(strcmp(pdirent->d_name, ".") == 0 || 
           strcmp(pdirent->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n",pdirent->d_name);
    }
    
    closedir(pdir);
}

int main(int argc, char** argv)
{
    if(argc == 1) {
        my_la(".");
    }else {
        my_la(argv[1]);
    }
    return 0;
}


