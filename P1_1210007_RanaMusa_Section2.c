///Rana Musa, 1210007, Section 2
#include <stdio.h>
#include <stdlib.h>
struct node
{

    struct node *next;
    struct node *prev;
    int data;
};

struct node *head, *new_node;

struct node *head2, *new_node2;
struct node *head3, *new_node3;
struct node *head4, *new_node4;
struct node *head5, *new_node5;
struct node *head_div, *new_node_div;

void file_to_linkedlist();

void display_addition (int sign);
void display_subtraction(int sign);
void disply_multiplication();
void display_division();

int get_size(struct node* heads);
int subtract2(struct node* head_new, struct node* head2_new, int counter);//used to get the result of division by frequent subtraction

void division();
void multiplication ();
int add();
int subtract();

int negative1;// i used integers to determine the sign of the number in the input file such that if negative1= 1, that means the number in the file is negatie
int negative2;//if negative2=0 that means it is positive
int zero=0;//this is used in division
int one=0;//used in division
/**
*i made a list of options as shown in the code , and it will keep appearing to the user till they enter 7 to exit
*the reason i used four functions to display the result to make sure the signs are correct for the four cases.
*/
int main()
{
    FILE* output=fopen("output.txt","w");
    printf("please choose an operation:\n");
    printf("1:read input file \n");
    printf("2:add\n");
    printf("3:subtract\n");
    printf("4:multiply\n");
    printf("5:division\n");
    printf("6:print on the output file\n");
    printf("7:exit\n");




    int selection;   // to select the operation as add, sub ...etc
    scanf("%d", &selection);
    while(selection!=7)
    {

        switch(selection)
        {
        case 1:
        {



            FILE* input=fopen("input.txt","r");

            if (input != NULL)
                printf("\nFile contains the following numbers : \n\n");
            char c = fgetc(input);//fgetc() is used to read the character from the file

            while (c != EOF)
            {


                printf ("%c", c);
                c = fgetc(input);

            }

            if (input == NULL)
                printf("\nThe file input does not exist.\n");

            fclose(input);


            break;
        }
        case 2:
        {

            file_to_linkedlist();///this calling to make sure the user chooses the numbers they want
            int sign = add();///sign is either 0 for positive or 1 for negative
            display_addition(sign);


            break;
        }


        case 3:
        {
            file_to_linkedlist();
            int sign=subtract ();
            display_subtraction(sign);
            break;
        }
        case 4:
        {

            file_to_linkedlist();
            multiplication ();

            disply_multiplication();

            break;
        }
        case 5:
        {
            file_to_linkedlist();
            division();
            display_division();


            break;
        }
        case 6:
        {

            FILE* output=fopen("output.txt","r");

            printf("The result printed on the file  = ");
            char c = fgetc(output);//fgetc() is used to read the character from the file

            while (c != EOF)
            {


                printf ("%c", c);
                c = fgetc(output);

            }
            printf("\n");
            fclose(output);

            break;
        }


        default:
            printf("inValid operation\n");
            break;


        }
        printf("\n\n");
        printf("please choose an operation:\n");
        printf("1:read input file \n");
        printf("2:add\n");
        printf("3:subtract\n");
        printf("4:multiply\n");
        printf("5:division\n");
        printf("6:print on the output file\n");
        printf("7:exit\n");
        scanf("%d", &selection);

    }




    return 0;
}
/**
*my idea in the add function is to add the last node in the first doubly linked list with the last node in list 2
*then it put the result in a new doubly linked list
*the carry obtained will be added to the previous node of the last node and so on
*/

int add()
{

    struct node* current = head;///i made head(list1) and head2(list2) global to make it easier

    while (current->next != NULL)
    {
        current = current->next;///current is the last value in the list head
    }

    struct node* current2 = head2;


    while (current2->next != NULL)
    {
        current2 = current2->next;///current2 is the last value in the list head2

    }

    int carry = 0;
    int sign=0;
    while(current != NULL || current2 != NULL)
    {
        int sum = carry;
        if (current != NULL)
        {
            /**if both numbers are positive or both are negative then it will do addition normally
              *for example (50+50)=100 and(-50+-50)=-(100) the only difference here is the sign and i put it when printing on file and on screen
              */
            if((negative1==1 && negative2==1) || (negative1==0 && negative2==0))
                sum += current->data;

            if(negative1==1 &&negative2==1)
            {
                sign=1;

            }
            ///in the case if the first number in negative and the other is positive, it turns out to be similar to subtraction
            ///if num1= -70 and the other is 50 that means it is 50-70=-20 which is subtraction process
            if((negative1==1 && negative2==0))
            {
                negative2=1;///i changed the sign here to match the rules in subtraction function
                sign = subtract();

                negative2=0;/// i turn it to its original case, in case the user wants to do other operations while running the code
                return sign;
            }
            if((negative1==0 && negative2==1))
            {
                negative2=0;
                sign= subtract();
                negative2=1;
                return sign;
            }

            current = current->prev;
        }
        if (current2 != NULL)
        {

            if((negative1==1 && negative2==1) || (negative1==0 && negative2==0))
                sum += current2->data;


            current2 = current2->prev;

        }

        carry = sum / 10;
        sum = sum % 10;

        // create a new node for the sum digit
        new_node3 = malloc(sizeof(struct node));
        new_node3->data = sum;
        new_node3->prev = NULL;
        new_node3->next = head3;

        if (head3 != NULL)
        {
            head3->prev = new_node3;
        }

        head3 = new_node3;
    }

/// if there is still a carry left it will be added to the number by creating a new node
    if (carry != 0)
    {
        new_node3 = malloc(sizeof(struct node));
        new_node3->data = carry;
        new_node3->prev = NULL;
        new_node3->next = head3;

        if (head3 != NULL)
        {
            head3->prev = new_node3;
        }

        head3 = new_node3;
    }

    return sign;
}
/**
*this function turn the values in the file into a doubly linked list.
*/
void file_to_linkedlist()
{
    FILE* input = fopen("input.txt", "r");
    struct node* temp;
    struct node* new_node;
    negative1=0;
    negative2=0;
    head = NULL;
    head3 = NULL;
    head2 = NULL;
    int selection1, selection2;
    printf("What numbers do you want to choose? (1-4)\n\n");
    printf("Enter the first one: ");
    scanf("%d", &selection1);
    if(selection1 >4 )
    {
        printf("fail->undefined value, choose again\n");
        scanf("%d", &selection1);
    }


    printf("Enter the second one: ");
    scanf("%d", &selection2);
    if(selection2 >4 )
    {
        printf("fail->undefined value, choose again\n");
        scanf("%d", &selection2);
    }

    char v;
    int counter = 1;
    struct node* headd = NULL;
    struct node* headd2 = NULL;
    int f1=0;
    int f2=0;

    v = fgetc(input);
    while (counter <=4 && v!=EOF) ///this loop will be executed 4 times because i have four numbers in the file, if i want more like 5 i just add 5 and so on
    {
        headd = NULL;

        if (counter > 1)
            v = fgetc(input);
        if(counter==selection1)
        {
            f1=1;
            if (v == '-')//this condition is for - sign because i don't want to store it in the linked list
            {

                negative1 = 1;
                f1=1;
                v = fgetc(input);// move to the next char without storing it
            }
        }
        if(counter==selection2)
        {
            f2=1;
            if (v == '-')
            {
                    f2=1;
                negative2 = 1;
                v = fgetc(input);
            }
        }

        if(selection1==selection2 && (f1==1 ||f2==1))// f1 and f2 are for the signs if the user chooses the same numbers twice they must have the same sign
           {
               negative1=negative2=1;
           }


        while (v != '\n' && v!=EOF) // it keeps reading until a new line comes
        {
            new_node = malloc(sizeof(struct node));
            new_node->prev = NULL;
            new_node->next = NULL;

            if (headd == NULL)
            {
                new_node->data = v - '0';//this return int value
                temp = new_node;
                headd = temp;
            }
            else
            {
                temp->next = new_node;
                new_node->data = v - '0';
                new_node->prev = temp;
                temp = new_node;
            }

            v = fgetc(input);
        }

        if (counter == selection1)
            head = headd;//headd is every number(list) in the file



        if (counter == selection2)
            head2 = headd;

        headd = NULL;
        counter++;
    }

    fclose(input);
    headd=NULL; //null to make sure it stores a new values in each loop


}


int get_size(struct node* heads)
{
    int size = 0;
    struct node* current = heads;

    if(heads->data=='-')// because if there is a case that have a sign i don't want to consider it as a number
        size--;



    while (current != NULL)
    {


        size++;
        current = current->next;
    }
    return size;
}

int subtract()
{


    int res=0;
    int borrow=0;
    struct node* current = head;

    while (current->next != NULL)
    {
        current = current->next;/// to get the last number in the doubly linked list(if the list is 13453245) so current =5
    }

    struct node* current2 = head2;


    while (current2->next != NULL)
    {
        current2 = current2->next;
    }

    int biggest_size;
    int flag=0;

    if(get_size(head)>get_size(head2))
    {
        biggest_size=get_size(head);
    }

    else if(get_size(head)<get_size(head2))
        biggest_size=get_size(head2);

    else
        biggest_size=get_size(head);/// in the case they are equal

    if(get_size(head) > get_size(head2))/// means that subtraction process will be normal
    {
        flag=1; // flag=1 means normal subtraction if head=100 and head2=50 so 100-50= +50.
    }

    if (get_size(head) == get_size(head2))///this case is to check which one is bigger if they have the same size for example 2451 and 2450
    {

        struct  node* temp1 = head;
        struct  node* temp2 = head2;

        int biggest_size = get_size(head);

        for (int i = 0; i < biggest_size; i++)
        {
            if (temp1->data > temp2->data)
            {
                flag = 1; //means first number is bigger
                break;
            }
            else if (temp2->data > temp1->data)
            {
                flag = 0;// means second number is bigger
                break;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;


        }

    }


    int sign=0; // sign is used when printing for diplay_addition and when printing on the file also

    if(flag==1) //normal subtraction list 2 from list 1
    {


        while(current2!=NULL || current!=NULL)
        {
            if (current2 != NULL && current2->data > current->data) //means we need to borrow
            {
                current->data += 10;
                borrow = 1;
                if (current->prev != NULL)
                {
                    current->prev->data -= borrow;
                }
            }


            if (current != NULL)
            {
                if(negative1==0 && negative2==0)
                {
                    sign=0;
                    res += current->data;
                }

                if(negative1==1 && negative2==1)
                {
                    res += current->data;
                    sign=1;
                }

                if((negative1==1 && negative2==0))//if number 1 is -50 and the other one is 100-->then -50-100=-150 it is like the condition in the addition function
                {
                    negative2=1;
                    add();
                    negative2=0;
                    sign=1;
                    return sign;

                }
                if((negative1==0 && negative2==1))//if n1=50 and n2=-100 --->then 50--100 =150 so it is addition
                {
                    negative1=1;
                    add(); //calling addition function
                    negative1=0;
                    sign=0;
                    return sign;

                }

                current = current->prev;
            }
            if (current2 != NULL)
            {

                if((negative1==1 && negative2==1) || (negative1==0 && negative2==0))
                    res =res- current2->data;

                current2 = current2->prev;

            }

            new_node3 = malloc(sizeof(struct node));
            new_node3->data = res;
            new_node3->prev = NULL;
            new_node3->next = head3;

            if (head3 != NULL)
            {
                head3->prev = new_node3;
            }

            head3 = new_node3;
            res=0;

        }
    }

    if(flag==0) //if list to is larger than list one ore they are the same size but list 2 is larger
    {
        res=0;
        struct node *head4;

        /*switching the lists so that the smalles will be subtracted by the largest normally and*/
        head4=head;
        head=head2;
        head2=head4;

        current = head;
        current2 = head2;

        while (current->next != NULL)
        {
            current = current->next;
        }




        while (current2->next != NULL)
        {
            current2 = current2->next;
        }


        while(current != NULL || current2 != NULL)// this loop adds 10 to the first number and set borrow to 1
        {


            if (current2 != NULL && current2->data > current->data)
            {
                current->data += 10;
                borrow = 1;
                if (current->prev != NULL)
                {
                    current->prev->data -= borrow;
                }
            }



            if (current != NULL)
            {
                if(negative1==0 && negative2==0)
                {
                    sign=1;

                    res += current->data;
                }

                if(negative1==1 && negative2==1)
                {
                    res += current->data;
                    sign=0;
                }

                if((negative1==1 && negative2==0))
                {
                    sign=1;
                    negative2=1;
                    add();
                    negative2=0;
                    break;

                }
                if((negative1==0 && negative2==1))
                {
                    sign=0;
                    negative1=1;
                    add();
                    negative1=0;
                    break;

                }
                current = current->prev;
            }
            if (current2 != NULL)
            {

                if((negative1==1 && negative2==1) || (negative1==0 && negative2==0))
                    res =res- current2->data;

                if((negative1==1 && negative2==0))
                {
                    res=res-current2->data;
                }

                current2 = current2->prev;

            }

            new_node3 = malloc(sizeof(struct node));
            new_node3->data = res;
            new_node3->prev = NULL;
            new_node3->next = head3;

            if (head3 != NULL)
            {
                head3->prev = new_node3;
            }

            head3 = new_node3;
            res=0;
        }
    }


    return sign; // 1 for negative and 0 for positive sign
}
///a function to print the result of addition on screen and on file
void display_addition (int sign)
{
    struct node *temp3;

    FILE* output=fopen("output.txt","w");
    temp3=head3;
    printf("\n");
    printf("res for addition = ");

    if(sign==1)//negative
    {
        printf("-");
        fprintf(output, "-");


    }

    while(temp3!=NULL)
    {

        printf("%d", temp3->data);
        fprintf(output, "%d",temp3->data);

        temp3=temp3->next;
    }
    fclose(output);
    printf("\n");
}
///a function to print the result of subtraction on screen and on file
void display_subtraction(int sign)
{
    FILE* output=fopen("output.txt","w");
    printf("\n");
    struct node *temp3;


    temp3=head3;
    printf("sub = ");
    if(sign==1)//negative
    {
        printf("-");
        fprintf(output, "-");


    }
    while(temp3!=NULL)
    {

        printf("%d", temp3->data);
        fprintf(output, "%d",temp3->data);
        temp3=temp3->next;
    }
    printf("\n");

    fclose(output);
}
/**
my multiplication function idea is traditional multiplication that first number from the second list will
be multiplied by the whole number then zero will be inserted and the second number in list 2 will be
multiplied by the whole number , then added together and so on until list 2 becomes null means multiplication process
finished.
*/

void multiplication ()
{
    int biggest_size=get_size(head2);
    int smallest_size=get_size(head);
    if( get_size(head)> get_size(head2))
    {
        biggest_size=get_size(head);
        smallest_size=get_size(head2);
    }
    /**
    switching lists because i want head2 the smallest always
    */
    if( get_size(head)< get_size(head2))
    {

        struct node *temp;
        temp=head;
        head=head2;
        head2=temp;
    }


    struct node*current=head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    struct node* current2 = head2;


    while (current2->next != NULL)
    {
        current2 = current2->next;
    }



    int counter=0;
    int res=0;
    int carry=0;
    int flag=0;


    while(current2!=NULL)
    {

        for(int i=0; i<biggest_size; i++)
        {
            res=0;
            if(current2!=NULL )
            {
                res=(current2->data*current->data)+carry;



                carry=res/10;
                res%=10;
                if(counter==0)
                {
                    new_node5 = malloc(sizeof(struct node));
                    new_node5->data = res;
                    new_node5->prev = NULL;
                    new_node5->next = head5;

                    if (head5 != NULL)
                    {
                        head5->prev = new_node5;
                    }

                    head5 = new_node5;

                    current=current->prev;

                }
                if(counter!=0)
                {

                    new_node4 = malloc(sizeof(struct node));
                    new_node4->data = res;
                    new_node4->prev = NULL;
                    new_node4->next = head4;

                    if (head4 != NULL)
                    {
                        head4->prev = new_node4;
                    }

                    head4 = new_node4;

                    current=current->prev;
                }



            }


        }

        current=head;
        while (current->next != NULL)
        {
            current = current->next;
        }


        if (carry != 0 && counter==0)
        {

            new_node5 = malloc(sizeof(struct node));
            new_node5->data = carry;
            new_node5->prev = NULL;
            new_node5->next = head5;

            if (head5 != NULL)
            {
                head5->prev = new_node5;
            }

            head5 = new_node5;
        }

        if (carry != 0 && counter!=0)
        {
            new_node4 = malloc(sizeof(struct node));
            new_node4->data = carry;
            new_node4->prev = NULL;
            new_node4->next = head4;

            if (head4!= NULL)
            {
                head4->prev = new_node4;
            }

            head4 = new_node4;
        }
        carry=0;
        current2=current2->prev;



        counter++;


        struct node *originalHead = head; // Variable to store the original head
        struct node *originalHead2 = head2;


        if (counter >= 2)
        {
            if (counter == 2)
            {
                head2 = head5;

            }

            // Variable to store the original head2
            head = head4;
            if(negative1==0 && negative2==1 )
            {
                negative2=0;
                int sign = add(); //sign here is useless but i used it to call addition because i need to add 2 liked list each loop
                negative2=1;
            }

            if(negative1==1 && negative2==0 )
            {
                negative1=0;
                int sign = add();
                negative1=1;
            }
            if(negative1==0 && negative2==0 || negative1==1 && negative2==1 )
            {

                int sign = add();

            }


            head2 = head3;  /// i put the valuse obtained from addition in head2, head2 and head3 are global so each operation i do will be in head3

            struct node *temp9;
            temp9=head4;




            if(current2 !=NULL)
                head3=NULL;

            head = originalHead;// giving them their original values


            originalHead=head3;
            originalHead2=head4;


        }
        /*adding zeros in the lift */

        if(counter>0&& current2!=NULL)
        {

            head4 = NULL;
            new_node4 = NULL;
            for(int i=0; i<counter; i++)
            {
                new_node4 = malloc(sizeof(struct node));
                new_node4->data = 0;
                new_node4->prev = NULL;
                new_node4->next = head4;

                if (head4 != NULL)
                {
                    head4->prev = new_node4;
                }

                head4 = new_node4;
            }

        }

        if(smallest_size==1)
        {
            head3=head5;
            struct node *temp10;
            temp10=head3;


        }

    }


    head5=NULL;


}
///this function is to print multiplication result on a file and on screen
void disply_multiplication()
{
    FILE* output=fopen("output.txt","w");

    struct node *temp9;
    temp9=head3;


    printf("\nres for multiplication = ");
    if(negative1==1 && negative2==0 || negative2==1 && negative1==0 ) //if both are positive or both are negative means the result of multiplication is positive
    {
        printf("-");
        fprintf(output, "-");
    }
    while(temp9!=NULL)
    {

        printf("%d", temp9->data);
        fprintf(output, "%d",temp9->data);
        temp9=temp9->next;
    }
    printf("\n");
    fclose(output);
}
/**
in my division function i checked sizes at first, if number 2 > number 1 the result will be zero
if number in list 1 > number in list 2 then it will split the list to the size of list 2 for example:list 1= 543215
list 2 = 342, list 1 becomes 543 the same length as list 2, and the rest will be stored in a new list (215 from 543215)
then list 1 and list 2 are sent to function subtract2 that will do frequent subtraction with increasing in the counter
until list2 become smaller than list1 (543-342=201) 201<342, counter is now 1 and that is the result of division and 201 is
the result i get if i do (1*543)-342, then 201 will be stored in a global variable and sent to division 2 from 215 will be inserted to 215
so it becomes 2155 and sent again to subtract2 that will keep doing frequent subtraction and the counter value will be division value and so on

the case if number1>number2 but they have the same beginning such as 2345612 and 2345, when splitting 2345612 it becomes 2345
in this case i inserted a digit before sending it to subtract2 or the result will be 1 and thats incorrect

the case they have the same size and same digits result will be 1 and exit the function.

the case the have same size but number2 > number1 result will be zero and exit the function

the case they have same size and number1 >number2 it will continue normally
*/

void division()
{
    head3=NULL;
    int counter=0;
    struct node* temp7=NULL;
    struct node *head_new=NULL;
    struct node *head2_new=head2;
    struct node *head_original=head;
    struct node *temp;
    struct node *rest_of_head;
    struct node*res_new=NULL;
    struct node *sub_res;


    int res=0;
    struct node* final_res=NULL;


    if(get_size(head2)> get_size(head))
    {

        printf("res for division = 0\n");
        zero=1;

        return;
    }
    /**
    this function is to split the largest list
    */

    for(int i=0; i<get_size(head2); i++)
    {


        struct node* new_node = malloc(sizeof(struct node));
        new_node->prev = NULL;
        new_node->next = NULL;

        if (head_new == NULL)
        {
            new_node->data = head_original->data;
            temp = new_node;
            head_new = temp;
        }
        else
        {
            temp->next = new_node;
            new_node->data =head_original->data ;
            new_node->prev = temp;
            temp = new_node;
        }

        head_original=head_original->next;
        rest_of_head=head_original; /// this stores the rest of number after splitting it

    }
    int flag1=0;
    int permision=0;
    if(get_size(head)>=get_size(head2))
    {

        if (get_size(head_new) == get_size(head2_new))// && rest_of_head==NULL
        {
            struct node* temp1 = head_new;
            struct node* temp2 = head2_new;

            int biggest_size = get_size(head_new);

            for (int i = 0; i < biggest_size; i++)
            {
                if (temp1->data > temp2->data)
                {
                    flag1 = 1; ///flag1= 1 means num1>num2
                    break;
                }
                else if (temp2->data > temp1->data && get_size(head)==get_size(head2))
                {
                    flag1 = 2;///flag1= 1 means num1<num2

                    break;
                }

                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            if(flag1==0 && get_size(head) == get_size(head2)) ///flag1=0 means they  have the same digits and equal, and if the original sizes are equal the result will be 1
            {
                   printf("res for division = ");
                if(negative1==1 && negative2==0 || negative2==1 && negative1==0 )
                {
                    printf("-");
                    one=1;
                }


                printf("1\n");


                return;
            }
            if(flag1==0 && get_size(head) > get_size(head2))/// this case when i need to insert a digit
            {
                flag1=1;
                permision=1;
            }

        }

        if(flag1==2)
        {
            printf("res for division = 0\n");
            zero=1;

            return;
        }

    }

    if(get_size(head)>=get_size(head2))
    {

        while(rest_of_head!=NULL || flag1==1)
        {
            flag1=0;
            if(counter==0)
            {


                int  flag=0;
                if (get_size(head_new) == get_size(head2_new) && flag1 ==0)
                {
                    struct node* temp1 = head_new;
                    struct node* temp2 = head2_new;

                    int biggest_size = get_size(head_new);

                    for (int i = 0; i < biggest_size; i++)
                    {
                        if (temp2->data > temp1->data)
                        {
                            flag = 1;
                            break;
                        }
                        else if (temp1->data > temp2->data)
                        {
                            flag = 0;

                            break;
                        }

                        temp1 = temp1->next;
                        temp2 = temp2->next;
                    }

                    if(flag1==0 && get_size(head) > get_size(head2))
                    {
                        flag1=1;
                        flag=1;
                    }
                }



                if(flag==1) ///this case when i need to insert a number to the first number
                {
                    struct node* temp9;
                    struct node* temp2 ;


                    temp2 = head_new;

                    // Create a new node and copy data into it
                    if(rest_of_head !=NULL || permision==1)
                    {
                        temp9 = malloc(sizeof(struct node));
                        temp9->prev = NULL;
                        temp9->next = NULL;
                        temp9->data = rest_of_head->data;


                        if (head_new == NULL)
                        {
                            // If the sub_res list is empty, make the new node the head
                            head_new = temp9;
                        }
                        else
                        {
                            // Traverse to the end of the sub_res list
                            while (temp2->next != NULL)
                            {
                                temp2 = temp2->next;
                            }

                            // Append the new node to the end of the sub_res list
                            temp2->next = temp9;
                            temp9->prev = temp2;
                        }



                        rest_of_head=rest_of_head->next; // move by one digit to insert the next didit the loop after this

                    }

                }


                res=subtract2(head_new,head2_new,0);/// res will store division result


                temp=temp7;
                temp7 = malloc(sizeof(struct node));
                temp7->prev = NULL;
                temp7->next = NULL;

                if (final_res == NULL) ///final result  is the doubly linked list that will store division result
                {
                    temp7->data = res;
                    temp = temp7;
                    final_res = temp;
                }
                else
                {
                    temp->next = temp7;
                    temp7->data =res;
                    temp7->prev = temp;
                    temp = temp7;
                }


            }
            counter++;

            if(counter>=1 && rest_of_head!=NULL)
            {


                if(counter==1)
                {
                    sub_res=head_div; ///head_div is a global doubly list that will store the final result of the frequent subtraction in subtract2 function
                }


                struct node* temp9;
                struct node* temp2 ;


                temp2 = sub_res;

                temp9 = malloc(sizeof(struct node));
                temp9->prev = NULL;
                temp9->next = NULL;
                temp9->data = rest_of_head->data; /// append a new number


                if (sub_res == NULL)
                {

                    sub_res = temp9;
                }
                else
                {

                    while (temp2->next != NULL)
                    {
                        temp2 = temp2->next;
                    }

                    temp2->next = temp9;
                    temp9->prev = temp2;
                }



                rest_of_head=rest_of_head->next;/// move one digit


                if(counter>=1)

                    res=subtract2(sub_res,head2_new,0);

                if(counter>1)

                    temp=temp7;
                temp7 = malloc(sizeof(struct node));
                temp7->prev = NULL;
                temp7->next = NULL;

                if (final_res == NULL)
                {
                    temp7->data = res;
                    temp = temp7;
                    final_res = temp;
                }
                else
                {
                    temp->next = temp7;
                    temp7->data =res;
                    temp7->prev = temp;
                    temp = temp7;
                }

            }




            if(counter>=1 && rest_of_head !=NULL)
            {


                sub_res=head_div;
                res_new=NULL;
                head=NULL;


            }


        }
        printf("res for division = ");
    }



    head3=final_res;


}
///this function is to print division result
void display_division()
{
    FILE* output=fopen("output.txt","w");


    if(negative1==1 && negative2==0 || negative2==1 && negative1==0 )
    {
        printf("-");
        fprintf(output, "-");
    }
    struct node* tempp =head3 ;

    if(head3 == NULL && zero==1)
        fprintf(output,"0");

    if(head3 == NULL && one==1)
        fprintf(output,"1");

    while (tempp != NULL)
    {
        printf("%d", tempp->data);
        fprintf(output, "%d",tempp->data);
        tempp = tempp->next;
    }
    printf("\n");
    fclose(output);
}

/**
this function's idea is to return division result by recursive operation that will increase the counter
each time till we obtain a  smaller number.
*/
int subtract2(struct node* head_new, struct node* head2_new, int counter)
{
    int res = 0;
    int flag = 0;
    int permition = 0;
    struct node* head_res = NULL;

    struct node* current = head_new;
    while (current->next != NULL)
    {
        current = current->next;
    }

    struct node* current2 = head2_new;
    while (current2->next != NULL)
    {
        current2 = current2->next;
    }

    if (get_size(head_new) > get_size(head2_new))
    {
        flag = 1;
    }

    if (get_size(head_new) == get_size(head2_new))
    {
        struct node* temp1 = head_new;
        struct node* temp2 = head2_new;

        int biggest_size = get_size(head_new);

        for (int i = 0; i < biggest_size; i++)
        {
            if (temp1->data > temp2->data)
            {
                flag = 1;
                break;
            }
            else if (temp2->data > temp1->data)
            {
                flag = 0;
                permition = 1;/// means exit the function and the loop and return counter value
                break;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;

        }
        if(flag==0 && permition==0 && head_new->data%head2_new->data==0)
            flag=2;



    }


/**flag=1 means keep going subtraction and flag=2  means the 2 numbers are equal
for example(8/2)=(8-2)=6, (6-2)=4, (4-2)=2 ,then it reaches(2-2) and they are equal so flag becomes 2 that i give it the permition
to enter the loop and by this the counter becomes 4 and this is the result of(8/2)
*/


    while (flag == 1 || flag==2)
    {
        while (current2 != NULL || current != NULL)
        {



            if(head_new->data%head2_new->data==0 && flag==2)

            {



                struct node* new_node3 = malloc(sizeof(struct node));
                new_node3->data = 0;
                new_node3->prev = NULL;
                new_node3->next = head_res;

                if (head_res != NULL)
                {
                    head_res->prev = new_node3;
                }

                head_res = new_node3;
                res = 0;
                return ++counter;

            }


            if (permition == 1 )///means the second number is larger
                return ;

            if (current2 != NULL && current2->data > current->data)///doing normal subtraction and borrowing
            {
                current->data += 10;
                int borrow = 1;
                if (current->prev != NULL)
                {
                    current->prev->data -= borrow;
                }
            }

            if (current != NULL)
            {
                res += current->data;
                current = current->prev;
            }
            if (current2 != NULL)
            {
                res = res - current2->data;
                current2 = current2->prev;
            }



            struct node* new_node3 = malloc(sizeof(struct node));
            new_node3->data = res;
            new_node3->prev = NULL;
            new_node3->next = head_res;

            if (head_res != NULL)
            {
                head_res->prev = new_node3;
            }

            head_res = new_node3;
            res = 0;
        }



        struct node* current = head_res;
        while (current != NULL && current->data == 0)///removing leading zeros in the left because if i don't it will cause a problem in size
        {
            struct node* next = current->next;
            free(current);
            current = next;
        }

        head_res = current;
        if (current != NULL)
        {
            current->prev = NULL;
        }


        head_new = head_res;

        head_div=head_res;



        if (flag ==1 && permition == 1)
        {
            return counter;
            // Exit the function when reaching this point
        }
        else
        {
            return subtract2(head_new, head2_new, ++counter);
        }
    }

    return counter;///counter is the result of division
}
