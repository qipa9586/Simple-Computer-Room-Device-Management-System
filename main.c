#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "mainFunctions.h"
#include "menu.h"

int main(void)
{

    int *device_count = 0;
    int *repair_count = 0;
    int *borrow_count = 0;

    Device device[MAX_DEVICES];
    Repair repair[MAX_DEVICES];
    Borrow borrow[MAX_DEVICES];

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
                
                switch(choice_case1) {
                    
                    case 1: {
                        printf("尚未开发\n\n");
                    }break;

                    case 2: {
                        printf("尚未开发\n\n");
                    }break;

                    case 3: {
                        printf("尚未开发\n\n");
                    }break;

                    case 4: {
                        printf("尚未开发\n\n");
                    }break;

                    case 5: {
                        printf("尚未开发\n\n");
                    }break;

                    case 0: 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;  

                }
            }break;

            case 2:
            {
                showStatusMenu();
                int choice_case2;
                scanf("%d", &choice_case2);

                switch(choice_case2) {

                    case 1: {
                        updateStatus(device, &device_count);
                    }break;

                    case 2: {
                        addRepairRecord(device, &device_count, repair, &repair_count);
                    }break;

                    case 3: {
                        searchRepairRecord(device, &device_count, repair, &repair_count);
                    }break;

                    case 0: 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;

                }
                printf("\n");

            }break;

            case 3:
            {
                showBorrowMenu();
                int choice_case3;
                scanf("%d", &choice_case3);

                switch(choice_case3) {

                    case 1: {
                        borrowDevice(device, borrow, &device_count, &borrow_count);
                    }break;
                
                    case 2: {
                        returnDevice(device, borrow, &device_count, &borrow_count);
                    }break;

                    case 3: {
                        searchBorrowRecord(device, borrow, &device_count, &borrow_count);
                    }break;

                    case 0: 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;
                
                }break;

            }break;

            case 4:
            {
                showOverallInfoMenu();
    
                int choice_case4;
                scanf("%d", &choice_case4);

                switch(choice_case4) {

                    case 1: {
                        printf("尚未开发\n\n");
                    }break;

                    case 2: {
                        printf("尚未开发\n\n");
                    }break;

                    case 3: {
                        printf("尚未开发\n\n");
                    }break;

                    case 4: {
                        printf("尚未开发\n\n");
                    }break;

                    case 0: 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;  

                }
            }break;

            case 0:
            {
                printf("感谢使用本程序!\n\n");
            }break;

            default:
            {
                printf("输入错误，请重试!\n\n");
            }break;

        }

    }while(choice != 0);

    system("pause");
    
    return 0;
}