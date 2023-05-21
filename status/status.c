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
        printf("파일을 열 수 없습니다");
        return;
    }
    fprintf(fp,"\n%s / %d / %s", member.name, member.age, member.mail);
    fclose(fp);
}

void delete_member(char* name, char* mail) {
    FILE* fp = fopen("member.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다");
        return;
    }

    FILE* tempfp = fopen("temp.txt", "w");
    if (tempfp == NULL) {
        printf("파일을 열 수 없습니다");
        fclose(fp);
        return;
    }

    Member member;
    int found = 0;
    while (fscanf(fp, "%[^/] / %d / %[^\n]", member.name, &member.age, member.mail) != EOF) {
        if (strcmp(member.name, name) == 0 && strcmp(member.mail, mail) == 0 ) {
            found = 1;
            continue;  // 해당 회원은 삭제하지 않고 건너뜀
        }
        fprintf(tempfp, "%s / %d / %s", member.name, member.age, member.mail);
    }

    fclose(fp);
    fclose(tempfp);


    if (!found) {
        printf("회원을 찾지 못했습니다");
    }
    else {
        printf("회원을 삭제했습니다.");
        tempfp = fopen("temp.txt", "r");
        if (tempfp == NULL) {
            printf("파일을 열 수 없습니다");
            return;
        }

        fp = fopen("member.txt", "w");
        if (fp == NULL) {
            printf("파일을 열 수 없습니다");
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
//삭제함수는 발견되지 않았을 때 temp에 그대로 복사


void print_member_list() {
    FILE* fp = fopen("member.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다");
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
       
        return 0; // 이메일 오류가 발생했음을 나타내는 값을 반환
    }

    return 1; // 이메일이 유효한 경우를 나타내는 값을 반환
}
int main(void) {
    FILE* fp = fopen("member.txt", "r");
    int choice;
    char name[255];
    int age;
    char mail[255];
    int count;

    do {
        printf("1. 신규회원 저장\n");
        printf("2. 회원정보 수정\n");
        printf("3. 회원 삭제\n");
        printf("4. 모든 회원 리스트\n");
        printf("5. 종료\n");
        printf("입력하세요> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char YorN;
            Member member;

            do {
               
                printf("이름: ");
                getchar(); // 입력 버퍼에 남아있는 개행 문자 제거
                fgets(member.name, sizeof(member.name), stdin);
                member.name[strcspn(member.name, "\n")] = '\0';

                printf("나이: ");
                scanf("%d", &member.age);
                getchar(); // 입력 버퍼에 남아있는 개행 문자 제거

                printf("이메일: ");
                fgets(member.mail, sizeof(member.mail), stdin);
                member.mail[strcspn(member.mail, "\n")] = '\0';
                if (is_mail(&member) == 0)
                {
                    printf("이메일 오류입니다 ___@____.___ 형식으로 입력해주세요");
                    break;
                }
                add_member(member);
                printf("신규 회원을 저장했습니다.\n");

                printf("계속 입력하시겠습니까? (Y/N) ");
                scanf(" %c", &YorN);
                
            } while (YorN == 'Y' || YorN == 'y');
            if (is_mail(&member) == 1)
            {
                
                printf("입력이 완료되었습니다\n");
            }
            printf("\n");
            
        } break;


        case 3: {
            printf("삭제할 회원 이름: ");
            getchar(); // Consume the newline character left in the input buffer
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("삭제할 회원 이메일: ");
            getchar();
            fgets(mail, sizeof(mail), stdin);
            mail[strcspn(mail, "\n")] = '\0';
            delete_member(name, mail);
        } break;

        case 4:
            print_member_list();
            break;

        case 5:
            printf("\n종료합니다.\n");
            break;
        }

        printf("\n");
    } while (choice != 5);
    return 0;
}
