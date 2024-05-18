#include <nofish_header.h>

typedef struct Person {
    char name[31];
    int age;
    char gender;
}Person;

//序列化和反序列化
void sequence_and_resequence(const char* filename) {
    Person person1 = {"nofish", 21, 'm'};
    printf("person1:\n\tname->%s\n\tage->%d\n\tgender->%c\n",
           person1.name, person1.age, person1.gender);
    int ret_write = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    ERROR_CHECK(ret_write, -1, "sequence_and_resequence open filename write error.\n");
    write(ret_write, &person1, sizeof(person1));
    close(ret_write);

    int ret_read = open(filename, O_RDONLY);
    ERROR_CHECK(ret_read, -1, "sequence_and_resequence open filename read error.\n");
    Person person2;
    read(ret_write, &person2, sizeof(person2));
    close(ret_read);
    printf("person2:\n\tname->%s\n\tage->%d\n\tgender->%c\n",
           person2.name, person2.age, person2.gender);
}

int main(int argc, char** argv)
{
    if(argc == 1){
        sequence_and_resequence("sequence_test.txt");
    } else {
        sequence_and_resequence(argv[1]);
    }
    return 0;
}


