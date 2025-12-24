#include <stdio.h>
#include "data.h"
#include "functions.h"
#include "menu.h"

// 定义全局变量
int device_count = 0;
int repair_count = 0;
Device device[MAX_DEVICES];
Repair repair[MAX_DEVICES];
Borrow borrow[MAX_DEVICES];

int main()
{
    int choice;
    
    do
    {
        showMainMenu();
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                showInfoMenu();
                int choice_case1;
                scanf("%d", &choice_case1);
                
                switch(choice_case1)
                {
                    case 1:

                }
            }break;
            case 2:
            {
                showStatusMenu();
                int choice_case2;
                scanf("%d", &choice_case2);

                switch(choice_case2)
                {
                    case 1:
                    {
                        updateStatus(device, device_count);
                    }break;

                    case 2:
                    {
                        repair_count = addRepairRecord(device, repair, device_count);
                    }break;

                    case 3:
                    {
                        searchRepairRecord(repair, repair_count);
                    }break;

                    case 0:
                    {
                        choice_case2 = 0; 
                    }break;

                    default:
                    {
                        printf("输入错误!请重试!\n\n");
                        return 0;
                    }break;
                }
                printf("\n");
            }break;
            case 3:
            {
                showBorrowMenu();
                int choice_case3;
                scanf("%d", &choice_case3);

                switch(choice_case3)
                {
                    case 1:
                }
            }break;
            case 4:
            {
                showOverallInfoMenu();
                {
                    int choice_case4;
                    scanf("%d", &choice_case4);

                    switch(choice_case4)
                    {
                        case 1:

                    }
                }
            }break;
            case 0:
            {
                printf("感谢使用本程序!\n\n");
                choice = 0;
            }break;
            default:
            {
                printf("输入错误，请重试!\n\n");
            }break;
        }



    }while(choice != 0);
   
    return 0;
}
