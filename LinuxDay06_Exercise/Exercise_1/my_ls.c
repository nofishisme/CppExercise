#include <nofish_header.h>

void set_type_mode(mode_t mode, char* str){
    //设置第一个权限字符
    switch (mode & S_IFMT) {
        case S_IFBLK:  str[0] = 'b'; break;//块设备文件
        case S_IFCHR:  str[0] = 'c'; break;//字符设备文件
        case S_IFDIR:  str[0] = 'd'; break;//目录文件
        case S_IFIFO:  str[0] = 'p'; break;//管道文件
        case S_IFLNK:  str[0] = 'l'; break;//符号连接文件
        case S_IFREG:  str[0] = '-'; break;//常规文件
        case S_IFSOCK: str[0] = 's'; break;//套接字文件
        default:       str[0] = '?'; break;//未知文件
    }
    str[1] = (mode & 0400) ? 'r' : '-';
    str[2] = (mode & 0200) ? 'w' : '-';
    str[3] = (mode & 0100) ? 'x' : '-';
    str[4] = (mode & 0040) ? 'r' : '-';
    str[5] = (mode & 0020) ? 'w' : '-';
    str[6] = (mode & 0010) ? 'x' : '-';
    str[7] = (mode & 0004) ? 'r' : '-';
    str[8] = (mode & 0002) ? 'w' : '-';
    str[9] = (mode & 0001) ? 'x' : '-';
    str[10] = 0;
}

char* get_file_path(const char* dirname, const char* filename){
    char* path = (char*)malloc(strlen(dirname) + strlen(filename) + 2);
    ERROR_CHECK(path, NULL, "get_file_path");
    return strcat(strcat(strcpy(path,dirname),"/"), filename);
}

void my_ls(const char* dirname) {
    DIR* dirp = opendir(dirname);
    ERROR_CHECK(dirp, NULL, "opendir");

    struct dirent* pdirent;
    while((pdirent = readdir(dirp)) != NULL) {
        char type_power[11];
        //获取当前目录项的绝对路径
        char* filepath = get_file_path(dirname, pdirent->d_name);
        struct stat statbuf;
        //获取当前文件条目的属性
        stat(filepath, &statbuf);
        set_type_mode(statbuf.st_mode, type_power);
        //根据时间戳获取时间
        struct tm* tmbuff = localtime(&(statbuf.st_mtime));
        struct passwd* passwdbuf = getpwuid(statbuf.st_uid);
        struct group* groupbuf = getgrgid(statbuf.st_gid);
        
        printf("%lu %s %2lu %s %s %6lu %d月  %d %02d:%02d %s\n",
               pdirent->d_ino,
               type_power,
               statbuf.st_nlink,
               passwdbuf->pw_name,
               groupbuf->gr_name,
               statbuf.st_size,
               tmbuff->tm_mon + 1,
               tmbuff->tm_mday,
               tmbuff->tm_hour,
               tmbuff->tm_min,
               pdirent->d_name);

        free(filepath);
    }
    closedir(dirp);
}

int main(int argc, char** argv)
{
    char* dirname;
    if (argc < 2) {
        dirname = (char*)malloc(strlen(".") + 1);
        ERROR_CHECK(dirname, NULL, "argc < 2, malloc error.\n");
        strcpy(dirname, ".");
    } else {
        dirname = (char*)malloc(strlen(argv[1]) + 1);
        ERROR_CHECK(dirname, NULL, "argc < 2, malloc error.\n");
        strcpy(dirname, argv[1]);
    }

    my_ls(dirname);

    free(dirname);
    return 0;
}


