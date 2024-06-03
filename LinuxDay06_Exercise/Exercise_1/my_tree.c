#include <nofish_header.h>

static const char* graph1= "│   ";
static const char* graph2= "    ";
static int level = 0;
static int count_dir = 0;
static int count_file = 0;
static bool flag_bool[1024];

//根据每层的状态打印不同的前置树形
void printPreGraph(void) {
    for(int i = 0; i < level; ++i){
        if(flag_bool[i]){
            printf("%s", graph2);
        }else{
            printf("%s", graph1);
        }
    }
}

char* get_file_path(const char* dirname, const char* filename){
    char* path = (char*)malloc(strlen(dirname) + strlen(filename) + 2);
    ERROR_CHECK(path, NULL, "get_file_path");
    return strcat(strcat(strcpy(path,dirname),"/"), filename);
}

struct dirent* get_next_entry(DIR* dirp){
    long loc = telldir(dirp);
    struct dirent* pdirent;
    //这里要略过"."和".."目录，如果略过这两个隐藏目录后返回null表明当前时最后一个目录项
    while((pdirent = readdir(dirp)) != NULL 
        && (pdirent->d_type == DT_DIR) 
        && pdirent->d_name[0] == '.');
    seekdir(dirp, loc);
    return pdirent;
}

void printBranch(struct dirent* pdirent, DIR* dirp) {
    printPreGraph();
    //检查下一个不是"."和".."的目录项目是否为空
    if(get_next_entry(dirp) == NULL){
        flag_bool[level] = true;
        printf("└── ");
    } else {
        flag_bool[level] = false;
        printf("├── ");
    }
    printf("%s\n", pdirent->d_name);

}

//递归调用展示文件夹的树
//flag标志标识上一个文件夹是否是最后一个文件夹
//不同的flag会打印不同的前置树形图
void my_tree_recrusion(const char* dirname) {
    DIR* dirp = opendir(dirname);
    ERROR_CHECK(dirp, NULL, "opendir");
    struct dirent* pdirent;
    while ((pdirent = readdir(dirp)) != NULL) {
        //略过"."和".."目录
        if(pdirent->d_type == DT_DIR && pdirent->d_name[0] == '.') {
            continue;
        } else if (pdirent->d_name[0] == '.') {
            continue;
        }
        //如果是目录，递归调用
        if (pdirent->d_type == DT_DIR) {
            //打印分支和文件项
            printBranch(pdirent, dirp);
            count_dir++;
            char* dirpath = get_file_path(dirname, pdirent->d_name);
            level++;
            my_tree_recrusion(dirpath);//递归调用
            level--;
            free(dirpath);
        } else {
            //打印分支和文件项
            printBranch(pdirent, dirp);
            count_file++;
        }
    }
    closedir(dirp);
}

void my_tree(const char* dirname){
    printf("%s\n", dirname);
    my_tree_recrusion(dirname);
    printf("\n总文件数目：%d\t总目录数目：%d\n", count_file, count_dir);
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

    my_tree(dirname);

    free(dirname);
    return 0;
}


