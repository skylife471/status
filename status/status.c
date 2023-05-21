#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[255];
    int age;
    char mail[255];
} Member;

void add_member(Member member) {
    FILE* fp = fopen("member.txt", "a");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�");
        return;
    }
    fprintf(fp,"\n%s / %d / %s", member.name, member.age, member.mail);
    fclose(fp);
}

void delete_member(char* name, char* mail) {
    FILE* fp = fopen("member.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�");
        return;
    }

    FILE* tempfp = fopen("temp.txt", "w");
    if (tempfp == NULL) {
        printf("������ �� �� �����ϴ�");
        fclose(fp);
        return;
    }

    Member member;
    int found = 0;
    while (fscanf(fp, "%[^/] / %d / %[^\n]", member.name, &member.age, member.mail) != EOF) {
        if (strcmp(member.name, name) == 0 && strcmp(member.mail, mail) == 0 ) {
            found = 1;
            continue;  // �ش� ȸ���� �������� �ʰ� �ǳʶ�
        }
        fprintf(tempfp, "%s / %d / %s", member.name, member.age, member.mail);
    }

    fclose(fp);
    fclose(tempfp);


    if (!found) {
        printf("ȸ���� ã�� ���߽��ϴ�");
    }
    else {
        printf("ȸ���� �����߽��ϴ�.");
        tempfp = fopen("temp.txt", "r");
        if (tempfp == NULL) {
            printf("������ �� �� �����ϴ�");
            return;
        }

        fp = fopen("member.txt", "w");
        if (fp == NULL) {
            printf("������ �� �� �����ϴ�");
            fclose(tempfp);
            return;
        }

        while (fgets(member.name, sizeof(member.name), tempfp) != NULL) {
            fprintf(fp, "%s", member.name);
        }

        fclose(tempfp);
        fclose(fp);
    }
}
//�����Լ��� �߰ߵ��� �ʾ��� �� temp�� �״�� ����


void print_member_list() {
    FILE* fp = fopen("member.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�");
        return;
    }

    Member member;
    while (fscanf(fp,"%[^/] / %d / %[^\n]", member.name, &member.age, member.mail) != EOF) {
        printf("%s / %d / %s", member.name, member.age, member.mail);
    }

    fclose(fp);
}

int is_mail(Member* member)
{
    int length = strlen(member->mail);
    int count = 0;

    for (int i = 0; i < length - 1; i++)
    {
        if (member->mail[i] == '@')
            count++;
    }

    for (int j = 0; j < length - 1; j++)
    {
        if (member->mail[j] == '.')
            count++;
    }

    if (count != 2) {
       
        return 0; // �̸��� ������ �߻������� ��Ÿ���� ���� ��ȯ
    }

    return 1; // �̸����� ��ȿ�� ��츦 ��Ÿ���� ���� ��ȯ
}
int main(void) {
    FILE* fp = fopen("member.txt", "r");
    int choice;
    char name[255];
    int age;
    char mail[255];
    int count;

    do {
        printf("1. �ű�ȸ�� ����\n");
        printf("2. ȸ������ ����\n");
        printf("3. ȸ�� ����\n");
        printf("4. ��� ȸ�� ����Ʈ\n");
        printf("5. ����\n");
        printf("�Է��ϼ���> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char YorN;
            Member member;

            do {
               
                printf("�̸�: ");
                getchar(); // �Է� ���ۿ� �����ִ� ���� ���� ����
                fgets(member.name, sizeof(member.name), stdin);
                member.name[strcspn(member.name, "\n")] = '\0';

                printf("����: ");
                scanf("%d", &member.age);
                getchar(); // �Է� ���ۿ� �����ִ� ���� ���� ����

                printf("�̸���: ");
                fgets(member.mail, sizeof(member.mail), stdin);
                member.mail[strcspn(member.mail, "\n")] = '\0';
                if (is_mail(&member) == 0)
                {
                    printf("�̸��� �����Դϴ� ___@____.___ �������� �Է����ּ���");
                    break;
                }
                add_member(member);
                printf("�ű� ȸ���� �����߽��ϴ�.\n");

                printf("��� �Է��Ͻðڽ��ϱ�? (Y/N) ");
                scanf(" %c", &YorN);
                
            } while (YorN == 'Y' || YorN == 'y');
            if (is_mail(&member) == 1)
            {
                
                printf("�Է��� �Ϸ�Ǿ����ϴ�\n");
            }
            printf("\n");
            
        } break;


        case 3: {
            printf("������ ȸ�� �̸�: ");
            getchar(); // Consume the newline character left in the input buffer
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("������ ȸ�� �̸���: ");
            getchar();
            fgets(mail, sizeof(mail), stdin);
            mail[strcspn(mail, "\n")] = '\0';
            delete_member(name, mail);
        } break;

        case 4:
            print_member_list();
            break;

        case 5:
            printf("\n�����մϴ�.\n");
            break;
        }

        printf("\n");
    } while (choice != 5);
    return 0;
}
