#include <nofish_header.h>

int main()
{
    int res;
    MYSQL *mysql = mysql_init(NULL);
    const char* user = "root";
    const char* password = "nofish8520";
    const char* localhost = "localhost";
    MYSQL_RES *query_result;

    if(mysql_real_connect(mysql, localhost, user, password, "test", 0, NULL, 0) == NULL) {
        fprintf(stderr, "数据库连接失败！\n");
        return -1;
    }

    res = mysql_query(mysql, 
                "create table if not exists t_user (id int, name varchar(25), password varchar(255), email varchar(255))");
    if(res != 0){
        printf("创建数据表失败！\n");
        return -1;
    }else{
        printf("创建数据表成功！\n");
    }

    res = mysql_query(mysql, "insert into t_user values (1, 'zs', '11408', 'myzs@example.com')");
    if(res != 0){
        printf("数据插入失败！\n");
        return -1;
    }
    const char *stmt_str = "select id, name, email from t_user where id > 0";
    res = mysql_query(mysql, stmt_str);
    if(res != 0){
        printf("查询数据表失败！\n");
        return -1;
    }

    query_result = mysql_store_result(mysql);
    if(query_result == NULL) {
        printf("未找到数据或者出错\n");
        return -1;
    }
    for(int i = 0; i < (int)mysql_num_rows(query_result); i++){
        MYSQL_ROW tmp_row = mysql_fetch_row(query_result);
        printf("id: %s\nname: %s\nemail: %s\n", tmp_row[0], tmp_row[1], tmp_row[2]);
    }
    mysql_close(mysql);

    return 0;
}

