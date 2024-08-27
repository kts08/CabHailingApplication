#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 6
#define COLS 6

struct myStructure
{
  char email[100][100];
  char password[100][100];
  char driver_assigned[100][10];
  char cancel[100][10];
  char advanced[100][100];
};

struct driver
{
  char driver_id[100][100];
  char driver_name[100][100];
  char driver_password[100][100];
  char driver_vehicle[100][100];
  char driver_location[100][100];
  char driver_destination[100][100];
  char driver_star[100][100];
  char driver_rides[100][100];
};

struct advanced_booking
{
    char email[100][100];
    char hr[100][100];
    char min[100][100]; 
    char hr1[100][100];
    char min1[100][100];
    char location[100][100];
    char destination[100][100];
    char type[100][100];
};

typedef struct Point
{
    int row;
    int col;
} Point;

Point createPoint(int row, int col);
void register1(char e[]);
void there(struct myStructure *s1, int *i, char email[], int *customers);
void login1(struct myStructure *s1, int *i, int *customers);
void locations(int area, int matrix[][6], Point *point);
void drive_assign_check(struct myStructure *s1, int *i, struct driver drive, int dr_id);
Point getMinDistanceNode(int distances[ROWS][COLS], bool visited[ROWS][COLS]);
bool isValid(int row, int col);
int dijkstra(int matrix[ROWS][COLS], Point start, Point end);
void driver(struct driver *drive, int *dr);
void driver_login(struct driver *drive, int *dr, int *dr_id);
void driver_register(struct driver *drive, int *dr, int *dr_id);
int peakhour();
float carcharges(struct driver drive, struct myStructure s1, int c_id);
float finalcharges(struct advanced_booking advanced , struct myStructure s1, int c_id, int o, int distance, struct driver drive);
void customer_booking(int matrix[][6], int *distance, int c_id, struct myStructure *s1);
void write_driver_file(struct driver drive, int dr);
void write_customer_file(struct myStructure s1, int no_customers);
void read_drivers(struct driver drive, struct myStructure s1, int c_id, int dr);
void book_advanced(int matrix[][6], struct myStructure *s1, int c_id, int *distance, struct advanced_booking advanced);
void finishride(struct driver *drive, struct myStructure *s1, int distance, int c_id, int dr, float price);
void cancellation(struct driver *drive, struct myStructure *s1, int c_id, int dr);
void check_alloted(int *i, char email[]);
void read_advanced_1(struct advanced_booking *s1,char email[], int *adv);
void read_advanced(struct advanced_booking *s1,char email[], int *i);
void append_advanced(struct advanced_booking *advanced, struct myStructure *s1, char email[], int matrix[][6], int *distance);
void update_advanced(struct advanced_booking s1, char email[], int ad);
void main();

Point createPoint(int row, int col)
{
    Point p;
    p.row = row;
    p.col = col;
    return p;
}

void register1(char e[])
{
    FILE *fp, *fptr;
    int there1=-1;
    char email[100];
    char password[100];
    char password1[100];
    int k=1;
    char dummy[40];
    int le=strlen(dummy);
    int cus=0;
    for(int i=0;i<le;i++)
    {
        dummy[i]='\0';
    }
    int c=0;
    int r=1;
    int t=0;
    int q=1;
    struct myStructure s2;
    fp=fopen("C:/Users/HP/Downloads/customer.txt","a");
    while(k==1)
    {
        while(k==1)
        {
            printf("enter the email address ");
            scanf("%s", email);
            int h;
            for(int i=0;email[i]!='\0';i++)
            {
                    if(email[i]=='@')
                    {
                        h=i;
                    }
            }
            c=0;
            for(int i=h;email[i]!='\0';i++)
            {
                dummy[c]=email[i];
                c++;
            }
            if(strcmp(dummy,"@gmail.com")==0)
            {

                there(&s2,&there1,email,&cus);
                if(there1==-1)
                {
                    k=2;
                    printf("valid email id\n");
                }
                else
                {
                    k=1;
                    printf("email id already exists\n");

                }
            }
            else
            {
                printf("enter valid email id syntax\n");
                k=1;
            }
        }
        while(r==1)
        {
            t=0;
            printf("enter a strong password of minimum 8 characters ");
            scanf("%s", password);
            for(int i=0;password[i]!='\0';i++)
            {
                t++;
            }
            if(t>=8)
            {
                printf("valid password\n");
                r=2;
            }
            else
            {
                printf("enter the right password ");
                r=1;
            }
        }
        while(q==1)
        {
            printf("enter the password again for verification ");
            scanf("%s", password1);
            if(strcmp(password1,password)==0)
            {
                printf("account created sucessfully\n");
                q=2;
            }
            else
            {
                printf("wrong pasword entered\n");
                q=1;
            }
        }
        fprintf(fp, "%s %s -1 0 0\n", email,password);
        fclose(fp);
        strcpy(e,email);
        int len = strlen(e);
        e[len]='\0';
    }
}

void there(struct myStructure *s1, int *i, char email[], int *customers)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/customer.txt","r");
    char myString[100];
    int a=0,c=0,k=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%5==0)
                {
                    s1->email[a][k]='\0';
                }
                else if(c%5==1)
                {
                    s1->password[a][k]='\0';
                }
                else if(c%5==2)
                {
                    s1->driver_assigned[a][k]='\0';
                }
                else if(c%5==3)
                {
                    s1->cancel[a][k]='\0';
                }
                else
                {
                    s1->advanced[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%5==0)
            {
               s1->email[a][k]=myString[i];
            }
            else if(c%5==1)
            {
                s1->password[a][k]=myString[i];
            }
            else if(c%5==2)
            {
                s1->driver_assigned[a][k]=myString[i];
            }
            else if(c%5==3)
            {
                s1->cancel[a][k]=myString[i];
            }
            else
            {
                s1->advanced[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    *customers = a;
    int j=-1;
    for(int i=0;i<100;i++)
    {
        if(strcmp(s1->email[i],email)==0)
        {
            j=i;
        }
    }
    *i = j;
    fclose(fptr);
}

void login1(struct myStructure *s1, int *i, int *customers)
{
    FILE *fptr;
    *i = -1;
    char email[100],password[100];
    fptr = fopen("C:/Users/HP/Downloads/customer.txt","r");
    char myString[100];
    int c=0,k=0,a=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%5==0)
                {
                    s1->email[a][k]='\0';
                }
                else if(c%5==1)
                {
                    s1->password[a][k]='\0';
                }
                else if(c%5==2)
                {
                    s1->driver_assigned[a][k]='\0';
                }
                else if(c%5==3)
                {
                    s1->cancel[a][k]='\0';
                }
                else
                {
                    s1->advanced[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%5==0)
            {
               s1->email[a][k]=myString[i];
            }
            else if(c%5==1)
            {
                s1->password[a][k]=myString[i];
            }
            else if(c%5==2)
            {
                s1->driver_assigned[a][k]=myString[i];
            }
            else if(c%5==3)
            {
                s1->cancel[a][k]=myString[i];
            }
            else
            {
                s1->advanced[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    *customers = a;
    int j=-1, c_em=0;
    while(j==-1)
    {
    	printf("Enter the email address ");
    	scanf("%s", email);
    	for(int i=0;i<100;i++)
    	{
        	if(strcmp(s1->email[i],email)==0)
        	{
            	j=i;
        	}
    	}
  		if(j==-1)
   		{
       		printf("Enter valid email address\n");
   		}
    }
    int pas=-1;
   	while(pas==-1)
   	{
   		printf("Enter the password ");
    	scanf("%s", password);
       	if(strcmp(s1->password[j],password)==0)
       	{
           	printf("Login Successfull\n");
           	break;
       	}
       	else
       	{
           	printf("Enter valid login password\n");
           	continue;
        }
    }
    *i = j;
    fclose(fptr);
}

void drive_assign_check(struct myStructure *s1, int *i, struct driver drive, int dr_id)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/customer.txt","r");
    char myString[100];
    int a=0,c=0,k=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%5==0)
                {
                    s1->email[a][k]='\0';
                }
                else if(c%5==1)
                {
                    s1->password[a][k]='\0';
                }
                else if(c%5==2)
                {
                    s1->driver_assigned[a][k]='\0';
                }
                else if(c%5==3)
                {
                    s1->cancel[a][k]='\0';
                }
                else
                {
                    s1->advanced[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%5==0)
            {
               s1->email[a][k]=myString[i];
            }
            else if(c%5==1)
            {
                s1->password[a][k]=myString[i];
            }
            else if(c%5==2)
            {
                s1->driver_assigned[a][k]=myString[i];
            }
            else if(c%5==3)
            {
                s1->cancel[a][k]=myString[i];
            }
            else
            {
                s1->advanced[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    int j;
    for(int i=0;i<100;i++)
    {
        if(strcmp(s1->driver_assigned[i],drive.driver_id[dr_id-1])==0)
        {
            j=i;
        }
    }
    *i = j;
    fclose(fptr);
}
void locations(int area, int matrix[][6], Point *point)
{
    if(area<=21)
    {
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
            {
                if(matrix[i][j]==area)
                {
                    *point = createPoint(i, j);
                }
            }
        }
    }
    else
    {
        printf("Enter valid location");
    }
}

Point getMinDistanceNode(int distances[ROWS][COLS], bool visited[ROWS][COLS])
{
    Point minNode = createPoint(-1, -1);
    int minDistance = INT_MAX;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!visited[i][j] && distances[i][j] < minDistance) {
                minDistance = distances[i][j];
                minNode = createPoint(i, j);
            }
        }
    }
    return minNode;
}

bool isValid(int row, int col)
{
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

int dijkstra(int matrix[ROWS][COLS], Point start, Point end)
{
    int distance=0;
    int distances[ROWS][COLS];
    bool visited[ROWS][COLS];
    Point previous[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            distances[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }

    distances[start.row][start.col] = 0;

    while (true)
    {
        Point current = getMinDistanceNode(distances, visited);

        if (current.row == -1 && current.col == -1)
            break;

        visited[current.row][current.col] = true;

        if (current.row == end.row && current.col == end.col)
            break;

        int row = current.row;
        int col = current.col;
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            if (isValid(newRow, newCol) && matrix[newRow][newCol] != 0 && !visited[newRow][newCol])
            {
                int newDistance = distances[row][col] + 1;

                if (newDistance < distances[newRow][newCol])
                {
                    distances[newRow][newCol] = newDistance;
                    previous[newRow][newCol] = current;
                }
            }
        }
    }
    if (visited[end.row][end.col])
    {
        Point current = end;

        while (current.row != start.row || current.col != start.col)
        {
            distance++;
            current = previous[current.row][current.col];
        }
    }
    else
    {
        printf("No valid path found.\n");
    }
    return distance;
}

void driver(struct driver *drive, int *dr)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/driver.txt","r");
    char myString[100];
    int c=0,k=0,a=0,i;
    while(fgets(myString, 100, fptr))
    {
        for(i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%8==0)
                {
                    drive->driver_id[a][k]='\0';
                }
                else if(c%8==1)
                {
                    drive->driver_name[a][k]='\0';
                }
                else if(c%8==2)
                {
                    drive->driver_password[a][k]='\0';
                }
                else if(c%8==3)
                {
                    drive->driver_vehicle[a][k]='\0';
                }
                else if(c%8==4)
                {
                    drive->driver_location[a][k] = '\0';
                }
                else if(c%8==5)
                {
                    drive->driver_destination[a][k]='\0';
                }
                else if(c%8==6)
                {
                    drive->driver_star[a][k]='\0';
                }
                else
                {
                    drive->driver_rides[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%8==0)
            {
                drive->driver_id[a][k]=myString[i];
            }
            else if(c%8==1)
            {
                drive->driver_name[a][k]=myString[i];
            }
            else if(c%8==2)
            {
                drive->driver_password[a][k]=myString[i];
            }
            else if(c%8==3)
            {
                drive->driver_vehicle[a][k]=myString[i];
            }
            else if(c%8==4)
            {
                drive->driver_location[a][k]=myString[i];
            }
            else if(c%8==5)
            {
                drive->driver_destination[a][k]=myString[i];
            }
            else if(c%8==6)
            {
                drive->driver_star[a][k]=myString[i];
            }
            else
            {
                drive->driver_rides[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    *dr = a;
    fclose(fptr);
}

void driver_login(struct driver *drive, int *dr, int *dr_id)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/driver.txt","r");
    char myString[100], password[100];
    int c=0,k=0,a=0,i, d_id;
    while(fgets(myString, 100, fptr))
    {
        for(i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%8==0)
                {
                    drive->driver_id[a][k]='\0';
                }
                else if(c%8==1)
                {
                    drive->driver_name[a][k]='\0';
                }
                else if(c%8==2)
                {
                    drive->driver_password[a][k]='\0';
                }
                else if(c%8==3)
                {
                    drive->driver_vehicle[a][k]='\0';
                }
                else if(c%8==4)
                {
                    drive->driver_location[a][k] = '\0';
                }
                else if(c%8==5)
                {
                    drive->driver_destination[a][k]='\0';
                }
                else if(c%8==6)
                {
                    drive->driver_star[a][k]='\0';
                }
                else
                {
                    drive->driver_rides[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%8==0)
            {
                drive->driver_id[a][k]=myString[i];
            }
            else if(c%8==1)
            {
                drive->driver_name[a][k]=myString[i];
            }
            else if(c%8==2)
            {
                drive->driver_password[a][k]=myString[i];
            }
            else if(c%8==3)
            {
                drive->driver_vehicle[a][k]=myString[i];
            }
            else if(c%8==4)
            {
                drive->driver_location[a][k]=myString[i];
            }
            else if(c%8==5)
            {
                drive->driver_destination[a][k]=myString[i];
            }
            else if(c%8==6)
            {
                drive->driver_star[a][k]=myString[i];
            }
            else
            {
                drive->driver_rides[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    *dr = a+1;
    d_id=-1;
    int ch=0;
    while(d_id==-1)
    {
        printf("Enter Driver ID ");
        scanf("%d", &d_id);
        for(int i=0;i<a;i++)
        {
            if(d_id == atoi(drive->driver_id[i]))
            {
                printf("Valid Driver Id\n");
                d_id = atoi(drive->driver_id[i]);
            }
            if(d_id==-1)
            {
                printf("Enter valid driver id\n");
                d_id = -1;
                continue;
            }
        }
    }
    while(ch==0)
    {
        printf("Enter password ");
        scanf("%s", password);
        if(strcmp(password, drive->driver_password[d_id-1])==0)
        {
            printf("Login Successfull\n");
            break;
        }
        else
        {
            printf("Please enter valid password\n");
        }
    }
    *dr_id = d_id;
    fclose(fptr);
}

void driver_register(struct driver *drive, int *dr, int *dr_id)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/driver.txt","r");
    char myString[100], password[100], name[100], type[100], location[100];
    int c=0,k=0,a=0,i, d_id;
    while(fgets(myString, 100, fptr))
    {
        for(i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%8==0)
                {
                    drive->driver_id[a][k]='\0';
                }
                else if(c%8==1)
                {
                    drive->driver_name[a][k]='\0';
                }
                else if(c%8==2)
                {
                    drive->driver_password[a][k]='\0';
                }
                else if(c%8==3)
                {
                    drive->driver_vehicle[a][k]='\0';
                }
                else if(c%8==4)
                {
                    drive->driver_location[a][k] = '\0';
                }
                else if(c%8==5)
                {
                    drive->driver_destination[a][k]='\0';
                }
                else if(c%8==6)
                {
                    drive->driver_star[a][k]='\0';
                }
                else
                {
                    drive->driver_rides[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%8==0)
            {
                drive->driver_id[a][k]=myString[i];
            }
            else if(c%8==1)
            {
                drive->driver_name[a][k]=myString[i];
            }
            else if(c%8==2)
            {
                drive->driver_password[a][k]=myString[i];
            }
            else if(c%8==3)
            {
                drive->driver_vehicle[a][k]=myString[i];
            }
            else if(c%8==4)
            {
                drive->driver_location[a][k]=myString[i];
            }
            else if(c%8==5)
            {
                drive->driver_destination[a][k]=myString[i];
            }
            else if(c%8==6)
            {
                drive->driver_star[a][k]=myString[i];
            }
            else
            {
                drive->driver_rides[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    fclose(fptr);
    fptr = fopen("C:/Users/HP/Downloads/driver.txt","a");
    printf("Please enter your name ");
    scanf("%s", name);
    int it=0;
    while(it==0)
    {
        printf("Please enter your password ");
        scanf("%s", password);
        if(strlen(password)<8)
        {
            printf("Password length should be greater than 8. Please re enter it\n");
            continue;
        }
        else
        {
            printf("Valid Password\n");
            break;
        }
    }
    char re_enter[100];
    while(it==0)
    {
        printf("Please re enter your password for confirmation ");
        scanf("%s", re_enter);
        if(strcmp(password,re_enter)==0)
        {
            printf("Password matches\n");
            break;
        }
        else
        {
            printf("Password does not match\n");
            continue;
        }
    }
    while(it==0)
    {
        printf("Please enter your type of vehicle without any spaces ");
        scanf("%s", type);
        for (int i = 0; type[i]!='\0'; i++) 
        {
            if(type[i] >= 'a' && type[i] <= 'z') 
            {
                type[i] = type[i] -32;
            }
        }
        if(strcmp(type,"SUV")==0 || strcmp(type,"PRIMESUV")==0 || strcmp(type,"PRIMESEDAN")==0 || strcmp(type,"SEDAN")==0)
            break;
        else
        {
            printf("Enter valid vehicle type ");
            break;
        }
    }
    while(it==0)
    {
        printf("1. Ennore\n");
        printf("2. Royappuram\n");
        printf("3. Kasimedu\n");
        printf("4. Washermanpet\n");
        printf("5. Madhavaram\n");
        printf("6. Central\n");
        printf("7. Alwarpet\n");
        printf("8. Royapettah\n");
        printf("9. Thiruvanmiyur\n");
        printf("10. Mylapore\n");
        printf("11. Nungambakkam\n");
        printf("12. Chetpet\n");
        printf("13. Vadapalani\n");
        printf("14. KK Nagar\n");
        printf("15. West Mambalam\n");
        printf("16. T Nagar\n");
        printf("17. Ashok Nagar\n");
        printf("18. Rampuram\n");
        printf("19. Tambaram\n");
        printf("20. Pallavaram\n");
        printf("21. Chrompet\n");
        printf("Enter your number based on your start location ");
        scanf("%s", location);
        if(atoi(location)>=1 && atoi(location)<=21)
        {
            break;
        }
        else
        {
            printf("Please enter valid start location\n");
            continue;
        }
    }
    *dr = a;
    *dr_id = a+1;
    char dri_id[100];
    sprintf(dri_id,"%d",(a+1));
    printf("This is your login id %d. Please remember it as it will be used to login in the future\n", a+1);
    strcpy(drive->driver_id[a], dri_id);
    strcpy(drive->driver_name[a], name);
    strcpy(drive->driver_password[a], password);
    strcpy(drive->driver_location[a], location);
    strcpy(drive->driver_vehicle[a], type);
    strcpy(drive->driver_destination[a], "-1");
    strcpy(drive->driver_rides[a], "0");
    strcpy(drive->driver_star[a], "0");
    fprintf(fptr,"%s %s %s %s %s %s %s %s\n", dri_id, name, password, type, location, "-1", "0", "0");
    fclose(fptr);
}

void customer_booking(int matrix[][6], int *distance, int c_id, struct myStructure *s1)
{
	int dr=0;
    Point start, end, drive1;
    struct driver drive;
    char type[100];
    int start_area, end_area;
    printf("1. Ennore\n");
    printf("2. Royappuram\n");
    printf("3. Kasimedu\n");
    printf("4. Washermanpet\n");
    printf("5. Madhavaram\n");
    printf("6. Central\n");
    printf("7. Alwarpet\n");
    printf("8. Royapettah\n");
    printf("9. Thiruvanmiyur\n");
    printf("10. Mylapore\n");
    printf("11. Nungambakkam\n");
    printf("12. Chetpet\n");
    printf("13. Vadapalani\n");
    printf("14. KK Nagar\n");
    printf("15. West Mambalam\n");
    printf("16. T Nagar\n");
    printf("17. Ashok Nagar\n");
    printf("18. Rampuram\n");
    printf("19. Tambaram\n");
    printf("20. Pallavaram\n");
    printf("21. Chrompet\n");
    printf("Enter your number based on your start location ");
    scanf("%d", &start_area);
    locations(start_area,matrix,&start);
    printf("Enter your number based on your end location ");
    scanf("%d", &end_area);
    locations(end_area, matrix,&end);
    *distance = dijkstra(matrix, end, start);
    driver(&drive, &dr);
    int ch=0;
    while(ch==0)
    {
        printf("1. SUV\n2. SEDAN\n3. PRIME SUV\n4. PRIME SEDAN\n");
        printf("Enter the type of vehicle you want by entering respective options ");
        scanf("%d", &ch);
        if(ch==1)
        {
            strcpy(type,"SUV\0");
        }
        else if(ch==2)
        {
            strcpy(type,"SEDAN\0");
        }
        else if(ch==3)
        {
            strcpy(type,"PRIMESUV\0");
        }
        else if(ch==4)
        {
            strcpy(type,"PRIMESEDAN\0");
        }
        else
        {
            ch=0;
            printf("Please enter valid choice\n");
        }
    }
    int min=10000;
    int j=-1;
    int min_star=0;
    for(int i=0;i<100;i++)
    {
        if((strcmp(drive.driver_vehicle[i],type)==0) && (strcmp(drive.driver_destination[i],"-1")==0))
        {
            int d=-1;
            int l = atoi(drive.driver_location[i]);
            locations(l,matrix,&drive1);
            d = dijkstra(matrix, drive1, start);
            if(d<min)
            {
                min=d;min=d;
                j=atoi(drive.driver_id[i]);
                min_star=atoi(drive.driver_star[i]);
                j=atoi(drive.driver_id[i]);
                min_star=atoi(drive.driver_star[i]);
            }
            else if(d==min)
            {
                int k = atoi(drive.driver_star[i]);
                if(min_star<k)
                {
                    min=d;
                    j=atoi(drive.driver_id[i]);
                    min_star=atoi(drive.driver_star[i]);
                }
            }
        }
    }
    for(int i=0;i<100;i++)
    {
        int allot = atoi(drive.driver_id[i]);
        if(allot==j)
        {
            printf("The driver alloted is %s with a star rating of %s and has completed %s rides\n", drive.driver_name[i],drive.driver_star[i],drive.driver_rides[i]);
			char dr1[101];
            strcpy(s1->driver_assigned[c_id],drive.driver_id[i]);
            sprintf(dr1,"%d",start_area);
            strcpy(drive.driver_location[i],dr1);
            sprintf(dr1,"%d",end_area);
            strcpy(drive.driver_destination[i],dr1);
            write_driver_file(drive,dr);
        }
    }
}

void write_driver_file(struct driver drive, int dr)
{
    FILE *fp, *fptr;
    fp=fopen("C:/Users/HP/Downloads/driver.txt","w");
    for(int i=0;i<dr;i++)
    {
        fprintf(fp, "%s %s %s %s %s %s %s %s\n", drive.driver_id[i],drive.driver_name[i], drive.driver_password[i], drive.driver_vehicle[i],drive.driver_location[i],drive.driver_destination[i],drive.driver_star[i],drive.driver_rides[i]);
    }
    fclose(fp);
}

void write_customer_file(struct myStructure s1, int no_customers)
{
    FILE *fp, *fptr;
    fp=fopen("C:/Users/HP/Downloads/customer.txt","w");
    for(int i=0;i<no_customers;i++)
    {
        fprintf(fp, "%s %s %s %s %s\n", s1.email[i],s1.password[i],s1.driver_assigned[i], s1.cancel[i], s1.advanced[i]);
    }
    fclose(fp);
}

void read_drivers(struct driver drive, struct myStructure s1, int c_id, int dr)
{
        printf("Your have already booked your ride\n");
        for(int i=0;i<dr;i++)
        {
            if(strcmp(drive.driver_id[i],s1.driver_assigned[c_id])==0)
            {
            	printf("Driver name: %s\n", drive.driver_name[i]);
            	printf("Start Location: %s\n", drive.driver_location[i]);
            	printf("End Destination: %s\n", drive.driver_destination[i]);
            	printf("Star Rating of Driver: %s\n", drive.driver_star[i]);
            	printf("The number of rides of Driver: %s\n", drive.driver_rides[i]);
			}
        }
}

void book_advanced(int matrix[][6], struct myStructure *s1, int c_id, int *distance, struct advanced_booking advanced)
{
    int dr=0;
    Point start, end, drive1;
    struct driver drive;
    int min=10000;
    int j=-1;
    int ad=-1;
    int min_star=0;
    int di = 0;
    driver(&drive, &dr);
    for(int i=0;i<100;i++)
    {
        if(strcmp(s1->email[c_id], advanced.email[i])==0)
        {
            ad=i;
        }
    }
    int st = atoi(advanced.location[ad]);
    locations(st,matrix,&start);
    int en = atoi(advanced.destination[ad]);
    locations(en,matrix,&end);
    di = dijkstra(matrix, end, start);
    *distance=di;
    for(int i=0;i<100;i++)
    {
        if((strcmp(drive.driver_vehicle[i],advanced.type[ad])==0) && (strcmp(drive.driver_destination[i],"-1")==0))
        {
            int d=-1;
            int l = atoi(drive.driver_location[i]);
            locations(l,matrix,&drive1);
            d = dijkstra(matrix, drive1, start);
            if(d<min)
            {
                min=d;min=d;
                j=atoi(drive.driver_id[i]);
                min_star=atoi(drive.driver_star[i]);
                j=atoi(drive.driver_id[i]);
                min_star=atoi(drive.driver_star[i]);
            }
            else if(d==min)
            {
                int k = atoi(drive.driver_star[i]);
                if(min_star<k)
                {
                    min=d;
                    j=atoi(drive.driver_id[i]);
                    min_star=atoi(drive.driver_star[i]);
                }
            }
        }
    }
    for(int i=0;i<100;i++)
    {
        int allot = atoi(drive.driver_id[i]);
        if(allot==j)
        {
            printf("The driver alloted is %s with a star rating of %s and has completed %s rides\n", drive.driver_name[i],drive.driver_star[i],drive.driver_rides[i]);
            strcpy(s1->driver_assigned[c_id],drive.driver_id[i]);
            strcpy(drive.driver_location[i],advanced.location[ad]);
            strcpy(drive.driver_destination[i],advanced.destination[ad]);
            write_driver_file(drive,dr);
        }
    }
}

int peakhour() 
{
	time_t currentTime = time(NULL);

	struct tm* localTime = localtime(&currentTime);

	int currentHour = localTime->tm_hour;

	int flag=0;

	if ((currentHour >= 8 && currentHour <= 11) || (currentHour >= 17 && currentHour <= 21)) 
	{
        flag=1;
		return flag;
	} 
	else 
	{
		return flag;
	}
}

float carcharges(struct driver drive, struct myStructure s1, int c_id)
{
	char sedan[50] ="SEDAN";
	char primesedan[50] ="PRIMESEDAN";
	char suv[50] ="SUV";
	char primesuv[50] ="PRIMESUV";
	float rate=0;
    int a = atoi(s1.driver_assigned[c_id]);
	if(strcmp(drive.driver_vehicle[a-1],sedan)==0)
	{
		if(peakhour()==0)
		{
			rate=12.5;
		}
		else if(peakhour()==1)
		{
			rate=12.5+3;
		}
	}
	if(strcmp(drive.driver_vehicle[a-1],primesedan)==0)
	{
		if(peakhour()==0)
		{
			rate=16.5;
		}
		else if(peakhour()==1)
		{
			rate=16.5+5;
		}
	}
	if(strcmp(drive.driver_vehicle[a-1],suv)==0)
	{
		if(peakhour()==0)
		{
			rate=20.5;
		}
		else if(peakhour()==1)
		{
			rate=20.5+5;
		}
	}
	if(strcmp(drive.driver_vehicle[a-1],primesuv)==0)
	{
		if(peakhour()==0)
		{
			rate=27.5;
		}
		else if(peakhour()==1)
		{
			rate=27.5+8;
		}
	}
    return rate;
}

float finalcharges(struct advanced_booking advanced , struct myStructure s1, int c_id, int o, int distance, struct driver drive)
{
	float total=30;
	int advancebooking=atoi(s1.advanced[c_id]);
    float total_min=0;
	if(advancebooking==1)
	{
        total_min = atof(advanced.hr1[o])*60 + atof(advanced.min1[o]);
	}
    total += 2*distance*carcharges(drive, s1, c_id) + total_min*1.5 + atof(s1.cancel[c_id]);
    return total;
}

void finishride(struct driver *drive, struct myStructure *s1, int distance, int c_id, int dr, float price)
{
    printf("The distance you have travelled is %d \n", distance*2);
	printf("The price to be paid to the driver is %.0f\n", price);
	printf("Please enter the star rating of the driver from 0 to 5 ");
	float m=-1, star;
	while(m==-1)
	{
        scanf("%f", &star);
        if(star>5 || star<0)
        {
            printf("Please enter the star rating of the driver from 0 to 5 ");
            continue;
        }
        else
        {
		    for(int i=0;i<dr;i++)
       	    {
           	    if(strcmp(drive->driver_id[i],s1->driver_assigned[c_id])==0)
           	    {
           	    	float star_r = atof(drive->driver_star[i]);
           		    float n_r = atof(drive->driver_rides[i]);
           		    star_r = (star+(star_r*n_r))/(n_r+1);
           		    char sw[101], ns[101];
           		    sprintf(sw,"%.1f", star_r);
           		    strcpy(drive->driver_star[i],sw);
           		    sprintf(ns,"%.0f", (n_r+1));
           		    strcpy(drive->driver_rides[i],ns);
           		    strcpy(drive->driver_location[i],drive->driver_destination[i]);
           		    strcpy(drive->driver_destination[i],"-1");
				    strcpy(s1->driver_assigned[c_id], "-1");
                    strcpy(s1->cancel[c_id],"0");
			    }
            }
		}
		break;
	}
}

void cancellation(struct driver *drive, struct myStructure *s1, int c_id, int dr)
{
	printf("Your ride has been cancelled. The cancellation charge is 25 Rupees. This will be taken into account the next time you finish the ride\n");
	for(int i=0;i<dr;i++)
   	{
        if(strcmp(drive->driver_id[i],s1->driver_assigned[c_id])==0)
        {
            float charge = atof(s1->cancel[c_id]);
            charge = charge + 25;
          	strcpy(drive->driver_location[i],drive->driver_destination[i]);
           	strcpy(drive->driver_destination[i],"-1");
			strcpy(s1->driver_assigned[c_id], "-1");
            char ch[100];
            sprintf(ch,"%.1f",charge);
            strcpy(s1->cancel[c_id], ch);
		}
	}
}

void check_alloted(int *i, char email[])
{
	struct myStructure s1;
	FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/customer.txt","r");
    char myString[100];
    int a=0,c=0,k=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%5==0)
                {
                    s1.email[a][k]='\0';
                }
                else if(c%5==1)
                {
                    s1.password[a][k]='\0';
                }
                else if(c%5==2)
                {
                    s1.driver_assigned[a][k]='\0';
                }
                else if(c%5==3)
                {
                    s1.cancel[a][k]='\0';
                }
                else
                {
                    s1.advanced[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%5==0)
            {
               s1.email[a][k]=myString[i];
            }
            else if(c%5==1)
            {
                s1.password[a][k]=myString[i];
            }
            else if(c%5==2)
            {
                s1.driver_assigned[a][k]=myString[i];
            }
            else if(c%5==3)
            {
                s1.cancel[a][k]=myString[i];
            }
            else
            {
                s1.advanced[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    int j=-1;
    for(int i=0;i<100;i++)
    {
        if(strcmp(s1.email[i],email)==0)
        {
            j=atoi(s1.driver_assigned[i]);
        }
    }
    *i = j;
}

void read_advanced_1(struct advanced_booking *s1,char email[], int *adv)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/customer_advanced.txt","r");
    char myString[100];
    int a=0,c=0,k=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')   
            {
                if(c%8==0)
                {
                    s1->email[a][k]='\0';
                }
                else if(c%8==1)
                {
                    s1->hr[a][k]='\0';
                }
                else if(c%8==2)
                {
                    s1->min[a][k]='\0';
                }
                else if(c%8==3)
                {
                    s1->hr1[a][k]='\0';
                }
                else if(c%8==4)
                {
                    s1->min1[a][k]='\0';
                }
                else if(c%8==5)
                {
                    s1->location[a][k]='\0';
                }
                else if(c%8==6)
                {
                    s1->destination[a][k]='\0';
                }
                else
                {
                    s1->type[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%8==0)
            {
               s1->email[a][k]=myString[i];
            }
            else if(c%8==1)
            {
                s1->hr[a][k]=myString[i];
            }
            else if(c%8==2)
            {
                s1->min[a][k]=myString[i];
            }
            else if(c%8==3)
            {
                s1->hr1[a][k]=myString[i];
            }
            else if(c%8==4)
            {
                s1->min1[a][k]=myString[i];
            }
            else if(c%8==5)
            {
                s1->location[a][k]=myString[i];
            }
            else if(c%8==6)
            {
                s1->destination[a][k]=myString[i];
            }
            else
            {
                s1->type[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    *adv = a;
}

void read_advanced(struct advanced_booking *s1,char email[], int *i)
{
    FILE *fptr;
    fptr = fopen("C:/Users/HP/Downloads/customer_advanced.txt","r");
    char myString[100];
    int a=0,c=0,k=0;
    while(fgets(myString, 100, fptr))
    {
        for(int i=0;i<strlen(myString);i++)
        {
            if(myString[i]==' ' || myString[i]=='\n')
            {
                if(c%8==0)
                {
                    s1->email[a][k]='\0';
                }
                else if(c%8==1)
                {
                    s1->hr[a][k]='\0';
                }
                else if(c%8==2)
                {
                    s1->min[a][k]='\0';
                }
                else if(c%8==3)
                {
                    s1->hr1[a][k]='\0';
                }
                else if(c%8==4)
                {
                    s1->min1[a][k]='\0';
                }
                else if(c%8==5)
                {
                    s1->location[a][k]='\0';
                }
                else if(c%8==6)
                {
                    s1->destination[a][k]='\0';
                }
                else
                {
                    s1->type[a][k]='\0';
                }
                c=c+1;
                k=0;
                continue;
            }
            if(c%8==0)
            {
               s1->email[a][k]=myString[i];
            }
            else if(c%8==1)
            {
                s1->hr[a][k]=myString[i];
            }
            else if(c%8==2)
            {
                s1->min[a][k]=myString[i];
            }
            else if(c%8==3)
            {
                s1->hr1[a][k]=myString[i];
            }
            else if(c%8==4)
            {
                s1->min1[a][k]=myString[i];
            }
            else if(c%8==5)
            {
                s1->location[a][k]=myString[i];
            }
            else if(c%8==6)
            {
                s1->destination[a][k]=myString[i];
            }
            else
            {
                s1->type[a][k]=myString[i];
            }
            k=k+1;
        }
        c=0;
        k=0;
        a=a+1;
    }
    int j=-1;
    for(int i=0;i<100;i++)
    {
        time_t now = time(NULL);
        struct tm *tm_struct = localtime(&now);
        int hour = tm_struct->tm_hour;
        int min = tm_struct->tm_min;
        int time,time1;
        if(strcmp(s1->email[i],email)==0)
        {
            time = atoi(s1->hr[i]);
            time1 = atoi(s1->min[i]);
            if(time<hour)
            {
                j=2;
            }
            else if(time==hour && min>=time1)
            {
                j=2;
            }
            else
            {
                printf("The hour at which you have scheduled the cab is %s\n", s1->hr[i]);
                printf("The minute at which you have scheduled the cab is %s\n", s1->min[i]);
                printf("If you want to book the cab now enter 1 else enter 0 ");
                while(j==-1)
                {
                    scanf("%d", &j);
                    if(j==1 || j==0)
                    {
                        break;
                    }
                    else
                    {
                        j=-1;
                        printf("Please enter valid choice ");
                    }
                }
            }
        }
    }
    *i = j;
    fclose(fptr);
}

void append_advanced(struct advanced_booking *advanced, struct myStructure *s1, char email[], int matrix[][6], int *distance)
{
    int dr=0;
    Point start, end, drive1;
    struct driver drive;
    char type[100];
    int start_area, end_area;
    printf("1. Ennore\n");
    printf("2. Royappuram\n");
    printf("3. Kasimedu\n");
    printf("4. Washermanpet\n");
    printf("5. Madhavaram\n");
    printf("6. Central\n");
    printf("7. Alwarpet\n");
    printf("8. Royapettah\n");
    printf("9. Thiruvanmiyur\n");
    printf("10. Mylapore\n");
    printf("11. Nungambakkam\n");
    printf("12. Chetpet\n");
    printf("13. Vadapalani\n");
    printf("14. KK Nagar\n");
    printf("15. West Mambalam\n");
    printf("16. T Nagar\n");
    printf("17. Ashok Nagar\n");
    printf("18. Rampuram\n");
    printf("19. Tambaram\n");
    printf("20. Pallavaram\n");
    printf("21. Chrompet\n");
    printf("Enter your number based on your start location ");
    scanf("%d", &start_area);
    locations(start_area,matrix,&start);
    printf("Enter your number based on your end location ");
    scanf("%d", &end_area);
    locations(end_area, matrix,&end);
    *distance = dijkstra(matrix, end, start);
    driver(&drive, &dr);
    int ch;
    while(ch==0)
    {
        printf("1. SUV\n2. SEDAN\n3.PRIME SUV\n4. PRIME SEDAN\n");
        printf("Enter the type of vehicle you want by entering respective options ");
        scanf("%d", &ch);
        if(ch==1)
        {
            strcpy(type,"SUV\0");
        }
        else if(ch==2)
        {
            strcpy(type,"SEDAN\0");
        }
        else if(ch==3)
        {
            strcpy(type,"PRIMESUV\0");
        }
        else if(ch==4)
        {
            strcpy(type,"PRIMESEDAN\0");
        }
        else
        {
            ch=0;
            printf("Please enter valid choice\n");
        }
    }
    char loc[100], dest[100];
    sprintf(loc, "%d", start_area);
    sprintf(dest,"%d", end_area);
    int j=0;
    FILE *fp;
    fp=fopen("C:/Users/HP/Downloads/customer_advanced.txt","a");
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    int hour = tm_struct->tm_hour;
    int mi = tm_struct->tm_min;
    char time[100],time1[100], time2[100], time3[100];
    int hr1,min1;
    int hr, min;
    while(j==0)
    {
        printf("Enter the hour you want to book the cab in 24 hrs clock ");
        scanf("%d", &hr);
        printf("Enter the minute you want to book the cab ");
        scanf("%d", &min);
        if(hr>=hour && min>=mi)
        {
            hr1=hr-hour;
            min1 = min-mi;
            break;
        }
        else if(hr>hour && min<mi)
        {
            hr1=hr-hour-1;
            min1 = 60-mi+min;
            break;
        }
        else
        {
            printf("Please enter the time in advanced you want to book\n");
        }
    }
    sprintf(time,"%d",hr);
    sprintf(time1,"%d", min);
    sprintf(time2,"%d", hr1);
    sprintf(time3,"%d",min1);
    fprintf(fp,"%s %s %s %s %s %s %s %s\n", email, time, time1, time2, time3, loc, dest, type);
    for(int i=0;i<100;i++)
    {
        if(strcmp(email,s1->email[i])==0)
        {
            strcpy(s1->advanced[i],"1");
        }
    }
}

void update_advanced(struct advanced_booking s1, char email[], int ad)
{
    FILE *fp;
    fp=fopen("C:/Users/HP/Downloads/customer_advanced.txt","w");
    for(int i=0;i<ad;i++)
    {
        if(strcmp(email, s1.email[i])==0)
        {
        }
        else
        {
            fprintf(fp,"%s %s %s %s %s %s %s %s\n", s1.email[i], s1.hr[i], s1.min[i], s1.hr1[i], s1.min1[i], s1.location[i], s1.destination[i], s1.type[i]);
        }
    }
}

void main()
{
    int c=0, c_id,distance=0,no_customers=0, no_drivers=0, d_or_c=0;
    char email[100];
    int dr=0;
    int leng = strlen(email);
    for(int i=0;i<leng;i++)
    {
    	email[i]='\0';
	}
    struct myStructure s1;
    while(d_or_c==0)
    {
        printf("Are you a:\n1. Driver\n2. Customer\nPlease enter your choice based on the number ");
        scanf("%d", &d_or_c);
        if(d_or_c==1)
        {
            struct driver drive;
            int dr=0, dr_id=0;
            while(c!=1 || c!=2)
            {
                printf("Enter 1 for login and 2 for register ");
                scanf("%d", &c);
                if(c==1)
                {
                    
                    driver_login(&drive, &dr, &dr_id);
                    break;
                }
                else if(c==2)
                {
                    driver_register(&drive, &dr, &dr_id);
                    printf("%d\n", dr_id);
                    break;
                }
                else
                {
                    printf("Please enter valid choice\n");
                    c=0;
                }
            }
            if(strcmp(drive.driver_destination[dr_id-1],"-1")==0)
            {
                printf("No customer is alloted to you and your present location is %s\n", drive.driver_location[dr_id-1]);
                printf("You have completed %s rides and have a star rating of %s\n", drive.driver_rides[dr_id-1], drive.driver_star[dr_id-1]);
            }
            else
            {
                struct myStructure s1;
                int c_id;
                drive_assign_check(&s1, &c_id, drive, dr_id);
                printf("Customer is alloted to you. The customer has email address %s. The location is %s and the destination is %s.\n", s1.email[c_id], drive.driver_location[dr_id-1], drive.driver_destination[dr_id-1]);
            }
            d_or_c=1;
            break;
        }
        else if(d_or_c==2)
        {
            while(c!=1 || c!=2)
            {
                printf("Enter 1 for login and 2 for register ");
                scanf("%d", &c);
                if(c==1)
                {
                    login1(&s1, &c_id,&no_customers);
                    break;
                }
                else if(c==2)
                {
                    register1(email);
                    there(&s1,&c_id,email,&no_customers);
                    break;
                }
                else
                {
                    printf("Please enter valid choice\n");
                    c=0;
                }
            }
            int matrix[ROWS][COLS] =
            {
                {0, 0, 0, 1, 0, 0},
                {2, 3, 4, 5, 6, 7},
                {0, 8, 0, 0, 0, 9},
                {0, 10, 11, 12, 13, 14},
                {0, 0, 15, 0, 0, 0},
                {16, 17, 18, 19, 20, 21}
            };
            c=0;
            int d_alloted=-1;
            int o;
            struct advanced_booking advanced;
            if(strcmp(s1.driver_assigned[c_id],"-1")!=0)
            {
                struct driver drive;
                driver(&drive, &dr);
                printf("Your have already booked your ride\n");
                for(int i=0;i<100;i++)
                {
                    if(strcmp(drive.driver_id[i],s1.driver_assigned[c_id])==0)
                    {
                        d_alloted = i;
                        printf("The driver alloted is %s with a star rating of %s and has completed %s rides\n", drive.driver_name[i],drive.driver_star[i],drive.driver_rides[i]);
                    }
                }
            }
            else
            {
                if(strcmp(s1.advanced[c_id],"0")!=0)
                {
                    int k=0;
                    read_advanced(&advanced,s1.email[c_id],&k);
                    if(k==1)
                    {
                        book_advanced(matrix,&s1,c_id, &distance, advanced);
                        write_customer_file(s1,no_customers);
                        struct driver drive;
                        driver(&drive, &dr);
                        check_alloted(&d_alloted,s1.email[c_id]);
                    }
                    else if(k==2)
                    {
                        book_advanced(matrix,&s1,c_id, &distance, advanced);
                        write_customer_file(s1,no_customers);
                        struct driver drive;
                        driver(&drive, &dr);
                        check_alloted(&d_alloted,s1.email[c_id]);
                    }
                    else
                    {
                        d_alloted=-3;
                    }
                }
                else
                {
                    printf("1. Advanced Booking\n");
                    printf("2. Instant Booking\n");
                    printf("Enter your choice ");
                    while(c==0)
                    {
                        scanf("%d", &c);
                        if(c==1 || c==2)
                        {
                            break;
                        }
                        else
                        {
                            printf("Please enter proper choice");
                            c=0;
                        }
                    }
                    if(c==1)
                    {
                        read_advanced_1(&advanced,s1.email[c_id], &o);
                        append_advanced(&advanced,&s1, s1.email[c_id], matrix, &distance);
                        write_customer_file(s1,no_customers);
                        d_alloted=-2;
                    }
                    else
                    {
                        customer_booking(matrix,&distance,c_id,&s1);
                        write_customer_file(s1,no_customers);
                        struct driver drive;
                        driver(&drive, &dr);
                        check_alloted(&d_alloted,s1.email[c_id]);
                    }
                }
            }
            if(d_alloted==-1)
            {
                printf("Sorry no driver are available near you right now. Please try again later.\n");
            }
            else if(d_alloted==-2)
            {
                printf("You have successfully booked your advanced ride. Please wait to ride in.\n");
            }
            else if(d_alloted==-3)
            {
                printf("Thank You\n");
            }
            else
            {
                printf("1. Ride Details\n");
                printf("2. Finish Ride\n");
                printf("3. Cancel Ride\n");
                printf("4. Logout\n");
                int it=0;
                while(it==0)
                {
                    printf("Enter your choice ");
                    scanf("%d", &c);
                    if(c==1)
                    {
                        struct driver drive;
                        driver(&drive, &dr);
                        read_drivers(drive,s1, c_id, dr);
                    }
                    else if(c==2)
                    {
                        int lm=-1;
                        if(strcmp(s1.advanced[c_id],"1")==0)
                        {
                            read_advanced_1(&advanced,s1.email[c_id], &lm);
                            for(int i=0;i<100;i++)
                            {
                                if(strcmp(s1.email[c_id],advanced.email[i])==0)
                                {
                                    lm=i;
                                }
                            }
                        }
                        struct driver drive;
                        driver(&drive, &dr);
                        Point sta,en; 
                        locations(atoi(drive.driver_location[atoi(s1.driver_assigned[c_id])-1]),matrix, &sta);
                        locations(atoi(drive.driver_destination[atoi(s1.driver_assigned[c_id])-1]),matrix, &en);
                        int distance = dijkstra(matrix,sta,en);
                        float price = finalcharges(advanced, s1, c_id, lm, distance, drive);
                        finishride(&drive,&s1,distance, c_id, dr, price);
                        if(strcmp(s1.advanced[c_id],"1")==0)
                        {
                            read_advanced_1(&advanced,s1.email[c_id], &o);
                            update_advanced(advanced, s1.email[c_id], o);
                            strcpy(s1.advanced[c_id],"0");
                        }
                        write_customer_file(s1, no_customers);
                        write_driver_file(drive, dr);
                        printf("Thank You For Riding With Us. Have a Good Day\n");
                        break;
                    }
                    else if(c==3)
                    {
                        struct driver drive;
                        driver(&drive, &dr);
                        cancellation(&drive, &s1, c_id, dr);
                        if(strcmp(s1.advanced[c_id],"1")==0)
                        {
                            read_advanced_1(&advanced,s1.email[c_id], &o);
                            update_advanced(advanced, s1.email[c_id], o);
                            strcpy(s1.advanced[c_id],"0");
                        }
                        write_customer_file(s1, no_customers);
                        write_driver_file(drive, dr);
                        printf("Thank you for your cooperation.\n");
                        break;
                    }
                    else if(c==4)
                    {
                        printf("You have been successfully logged out of the application\n");
                        break;
                    }
                    else
                    {
                        printf("Please enter the valid choice\n");
                    }
                }
            }
            d_or_c=2;
            break;
        }
        else
        {
            printf("Please enter valid choice\n");
            d_or_c=0;
            continue;
        }
    }
}