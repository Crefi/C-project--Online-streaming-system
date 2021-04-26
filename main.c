#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
void login();
void registration();
void logout();
void top();
void list();
FILE *fp,*ft;
static int i=0;
struct user
{
    char username[20];
    char password[20];
    char canal[20];

};
struct user l;
int n;
int main()
{
    int ch;

    while(1)
    {
        system("cls");
        int i;
        printf("_________________________________________________________________________________________________");
        printf("\n\n                                       Main Menu \n");
        printf("_________________________________________________________________________________________________\n");
        printf("1. Register \n");
        printf("2. Login \n");
        printf("3. Logout \n");
        printf("4. Add Channel to list and search\n");
        printf("5. Top 25 Channels\n");
        printf("6. Exit \n");
        printf("\n");
        printf("Pick a number: ");
        scanf("%d",&ch);

        switch(ch)
        {
        case 1:
            registration();
            break;
        case 2:
            login();
            break;
        case 3:
            logout();
            break;
        case 4:
            list();
            break;
        case 5:
            top();
            break;
        case 6:
            exit(0);

        }

    }

    return 0;
}

void registration(void)
{

    FILE *fp;
    char c,username[13];
    int z=0;
    fp=fopen("file.dat","ab+");
    system("cls");
    printf("\n\n Enter name & password");
    for(i=0; i<99; i++)
    {
        printf("\n\n Name: ");
        scanf("%s",username);
        while(!feof(fp))
        {
            fread(&l,sizeof(l),1,fp);
            if(strcmp(username,l.username)==0)
            {
                system("cls");
                printf("\n\n Name is not available");
                printf("\n\n Press any key to return");
                getch();
                system("cls");
                main();
            }
            else
            {
                strcpy(l.username,username);
                break;
            }
        }
        z=0;
        printf("\n\n Password: ");
        while((c=getch())!=13)
        {
            l.password[z++]=c;
            printf("%c",'*');
        }
        fwrite(&l,sizeof(l),1,fp);
        fclose(fp);
        if((c=getch())==13)
        {
            system("cls");
            printf("\n\n You are reggister!");
            printf("\n\n Do you want to log in?\n\n");
            printf(" Press 1 for yes \n\n Press 2 for no \n\n");
            scanf("%d",&n);
            if(n==1)
            {
                system("cls");
                login();
            }
            else if(n==2)
            {
                system("cls");
                printf("\n\n Thank you for registering! \n");
            }
        }
        break;
    }
}
void login()
{
    FILE *fp;
    char c,name[10],pass[10];
    int z=0;
    int checkuser,checkpw;
    fp=fopen("file.dat","rb");
    for(i=0; i<=10; i++)
    {
        system("cls");
        printf("\n\n Name: ");
        scanf("%s",name);

        printf("\n\n Password: ");
        while((c=getch())!=13)
        {
            pass[z++]=c;
            printf("%c",'*');
        }
        pass[z]='\0';
        while(!feof(fp))
        {
            fread(&l,sizeof(l),1,fp);
            checkuser=strcmp(name,l.username);
            checkpw=strcmp(pass,l.password);
            if(checkuser==0&&checkpw==0)
            {
                system("cls");
                printf("\n\n\n LOGIN SUCCESSFUL!");
                break;
            }
            else if(checkuser==0)
            {
                printf("\n\n The password is  wrong!");
                printf("\n\n  (Press [Y] for relog or any  other key for return)");
                if (getch()=='y'||getch()=='Y')
                    system("cls");
                main();

            }
            else if(checkuser!=0&&checkpw!=0)
            {

                printf("\n\n You are not register\n Press [ENTER] to return");
                if(getch()==13)
                    system("cls");
                main();
            }
            else if(checkuser!=0&&checkpw==0)
            {
                main();
            }
        }
        break;
    }
    getch();
}
void logout ()
{

    struct user l;
    system("cls");
    char nume[20];
    printf("Log out by name\n");
    printf("Choose Name: \n");
    getchar();
    scanf("%[^\n]",nume);
    FILE * fp;
    fp = fopen("file.dat", "rb");
    FILE * tempPointer;
    tempPointer = fopen("file2.dat", "ab");

    char linie[500];
    if ( fp == NULL )
    {
        printf( "The file can't be accessed.\n" ) ;
    }
    else
    {
        while (fgets (linie, 500, fp))
        {
            sscanf(linie, "%s", l.username, l.password);
            if(strcmp(nume,l.username)!=0)
                fprintf(tempPointer, "%s", linie);
                system("cls");
                printf("You log out successfully\n");
        }
        }
        fclose(fp);
        fclose(tempPointer);
        remove("file.dat");
        rename("file2.dat", "file.dat");
        getch();
        return;

    }



void list()
{
    int nChoice = 0;
    system("cls");
    do
    {
        switch (nChoice)
        {
        case 1:
            Cautare();
            break;
        case 2:
            Abonare();
            break;
        case 3:
            Dezabonare();
            break;
        case 4:
            break;
        }
        printf("1.Search Channel \n2.Subscribe\n3.Unsubscribe\n4.Return\n");
        printf ("Pick a number: ");
        scanf ("%d", &nChoice);
        printf("\n");

        if (( nChoice < 1 ) || ( nChoice > 4))
        {
            printf("Wrong answer. Pick a correct number \n\n\n");
        }
    }
    while (nChoice != 4);

    return nChoice;
}

void Cautare()
{
    system("cls");
    FILE *fp;
    struct user l;
    char name[200];
    char linie[301];
    int rating;
    int found=0;
    printf("Choose name\n");
    scanf("%s",name);
    fp = fopen("list.dat", "rb");
    if ( fp == NULL )
    {
        printf( "the file can't be accessed.\n" ) ;
    }
    while(1)
    {
        fgets(linie, 300, fp);

        if(strstr(linie,name)!=NULL)
        {
            if (feof(fp))
            break;
            printf("Channel name and rating: %s\n",linie);
            found=1;
        }
    }
    if(found==0)
    {
        printf("The channel can't be found\n");
    }
    fclose(fp);
    return;
}
void Abonare()
{
    system("cls");
    FILE *fp;
    struct user l;
    int rating;
    fp=fopen("list.dat","ab");
    printf("Choose name:");
    getchar();
    scanf("%[^\n]",l.canal);
    printf("Choose rating:");
    scanf("%d",&rating);
    getchar();
    system("cls");

    if ( fp == NULL )
    {
        printf( "the file can't be accessed." ) ;
    }
    else
    {
        fprintf(fp, "%s,%d\n", l.canal,rating);
        fclose(fp) ;
    }
}


void Dezabonare()
{
    system("cls");
    int rating;
    char nume[20];
    printf("Delete by name\n");
    printf("Choose name \n");
    getchar();
    scanf("%[^\n]",nume);

    FILE * fp;
    fp = fopen("list.dat", "rb");

    FILE * tempPointer;
    tempPointer = fopen("list2.dat", "ab");

    char linie[500];
    if ( fp == NULL )
    {
        printf( "the file can't be accessed.\n" ) ;
    }
    else
    {
        while (fgets (linie, 500, fp))
        {
            sscanf(linie, "%[^,],%d", l.canal, &rating);
            if(strcmp(nume,l.canal)!=0)
                fprintf(tempPointer, "%s", linie);
        }
        fclose(fp);
        fclose(tempPointer);
        remove("list.dat");
        rename("list2.dat", "list.dat");
        return;

    }

}

void top()
{
    system("cls");
    FILE *fp;
    struct user l;
    int rating;
    fp=fopen("list.dat","rb");
    if ( fp == NULL )
    {
        printf( "The file can't be accessed.\n" ) ;
    }
    char line[500];
    while(1)
    {
        fscanf(fp, "%s", l.canal);
        if (feof(fp))
        break;
        printf("Name and rating: %s%\n",l.canal);

    }
    system("pause");
    fclose(fp);
}
