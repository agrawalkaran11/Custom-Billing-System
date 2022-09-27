#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int noi;
    struct items itm[50];
};

void BillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t       Agrawal Industries");
    printf("\n-----------------------------------------------");
    printf("\nDate: %s",date);
    printf("\nCustomer Name: %s \n",name);
    printf("-----------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------------\n\n");
}
void BillBody(char item[30], int qty, float price)
{
    printf("%s\t", item);
    printf("  %d\t\t\t", qty);
    printf("%.2f\n", qty*price);
}


void BillFooter(float total)
{
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal, grandTotal = netTotal + 2*cgst;
    printf("\n-----------------------------------------------\n");
    printf("Sub Total\t\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t       --------");
    printf("\nNet Total \t\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t\t%.2f","%",cgst);
    printf("\n-----------------------------------------------\n");
    printf("Grand Total \t\t\t\t%.2f",grandTotal);
    printf("\n-----------------------------------------------\n");
}
int main()
{
    int opt,n,i;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag='y';
    char name[50];
    FILE *fp;
    while(contFlag == 'y')
    {
    float total=0;
    int i, invoiceFound=0;
    printf("\n===============Agrawal Industries=================");
    printf("\n\nPlease Select Your Preffered Operation...\t");
    printf("\n1. Generate Invoice");
    printf("\n2. Show All Invoices");
    printf("\n3. Search Invoice");
    printf("\n4. Exit");
    printf("\n\nYour Choice: ");
    scanf("%d",&opt);
    fgetc(stdin);

    switch (opt)
    {
        case 1:
        system("cls");
        printf("Please Enter Customer Name: ");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("Please Enter the Number of Items: ");
        scanf("%d",&n);
        ord.noi=n;
        for(i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\nPlease Enter the Item %d> ",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please Enter the Quantity: ");
            scanf("%d",&ord.itm[i].qty);
            printf("Please Enter the Unit Price: ");
            scanf("%f",&ord.itm[i].price);
            total += (ord.itm[i].qty) * (ord.itm[i].price);


        }
        BillHeader(ord.customer,ord.date);
        for (i=0;i<ord.noi;i++)
        {
            BillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        BillFooter(total);
        printf("\nSave this Invoice?: (y/n)");
        scanf("\n%s",&saveBill);
        if(saveBill=='y')
            {
                fp=fopen("BillRecord.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite != 0)
                    printf("\nSuccessfully Saved!");
                else
                    printf("\nFailed! Please try again...");
                fclose(fp);
            }
        break;

        case 2:
            system("cls");
            fp=fopen("BillRecord.dat","r");
            printf("\n*********Your Previous Invoices*********");
            while(fread(&order,sizeof(struct orders),1,fp))
                {
                    float tot=0;
                    BillHeader(order.customer,order.date);
                    for(i=0;i<order.noi;i++)
                    {
                        BillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    BillFooter(tot);
                }
                fclose(fp);
         break;

        case 3:
            printf("\nEnter the Name of Customer: ");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            system("cls");
            fp=fopen("BillRecord.dat","r");
            printf("\n\t *****Invoice of %s*****\n",name);
            while(fread(&order,sizeof(struct orders),1,fp))
                {
                    float tot=0;
                    if(!strcmp(order.customer,name))
                    {
                    BillHeader(order.customer,order.date);
                    for(i=0;i<order.noi;i++)
                    {
                        BillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    BillFooter(tot);
                    }
                    invoiceFound=1;
                    }
                if(!invoiceFound)
                {
                    printf("\nSorry, The Invoice for %s does not exist!",name);
                }

                fclose(fp);
         break;

        case 4:
            system("cls");
            printf("\n\t\tThank You! See You Soon!\n");
            exit(0);
            break;

        default:
            printf("\nInvalid Option!");
            break;
    }
    printf("\nDo You Want to Perform Any Another Operation? [y/n]: ");
    scanf("%s",&contFlag);
    }
    printf("\n\t\tThank You! See You Soon!\n");
    return 0;
}
