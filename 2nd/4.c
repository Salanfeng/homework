#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int num;
    char *nums;
} Person;

int compare(const void *p1, const void *p2)
{
    const Person *person1 = (const Person *)p1;
    const Person *person2 = (const Person *)p2;
    return strcmp(person1->name, person2->name);
}

int main()
{
    int n;
    scanf("%d\n", &n);
    Person *people = (Person *)malloc(n * sizeof(Person));
    int i;
    for (i = 0; i < n; i++)
    {
        char name[101], num[101];
        scanf("%s %s", name, num);
        int j;
        for (j = 0; j < i; j++)
        {
            if (strcmp(people[j].name, name) == 0)
            {
                if (strcmp(people[j].nums, num) == 0)
                {
                    break;
                }
                else
                {
                    char number = '0' + people[j].num;
                    char save[3];
                    save[0] = '_', save[1] = number, save[2] = '\0';
                    strcat(name, save);
                    people[j].num++;
                    j = i;
                }
            }
        }
        if (j < i)
        {
            i--;
            n--;
            continue;
        }

        Person person;
        person.name = strdup(name);
        person.num = 1;
        person.nums = (char *)malloc(sizeof(char *));
        person.nums = strdup(num);
        people[i] = person;
    }

    qsort(people, n, sizeof(Person), compare);
    for (i = 0; i < n; i++)
    {
        printf("%s %s", people[i].name, people[i].nums);
        printf("\n");
    }
    free(people);

    return 0;
}
/*15
liping 13512345678
zhaohong 13838929457
qiansan 13900223399
zhouhao 18578294857
anhai 13573948758
liping 13512345678
zhaohong 13588339922
liping 13833220099
boliang 15033778877
zhaohong 13838922222
tianyang 18987283746
sunnan 13599882764
zhaohong 13099228475
liushifeng 13874763899
caibiao 13923567890*/