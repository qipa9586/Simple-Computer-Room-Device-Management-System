#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "menu.h"
#include "mainFunctions.h"


int main(void)
{

    int device_count = 0;
    int repair_count = 0;
    int borrow_count = 0;

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
                system("cls");
                showInfoMenu();
                int choice_case1;
                scanf("%d", &choice_case1);
                
                switch(choice_case1) {
                    
                    case 1: {
                        system("cls");
                        addNewDevice(device, &device_count);
                    }break;

                    case 2: {
                        system("cls");
                        editDeviceInfo(device, &device_count);
                    }break;

                    case 3: {
                        system("cls");
                        deleteDeviceInfo(device, &device_count);
                    }break;

                    case 4: {
                        system("cls");
                        searchDeviceInfo(device, &device_count);
                    }break;

                    case 5: {
                        system("cls");
                        displayAllDeviceInfo(device, &device_count);
                    }break;

                    case 0: {
                        system("cls");
                    } 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;  

                }
            }break;

            case 2:
            {
                system("cls");
                showStatusMenu();
                int choice_case2;
                scanf("%d", &choice_case2);

                switch(choice_case2) {

                    case 1: {
                        system("cls");
                        updateStatus(device, &device_count);
                    }break;

                    case 2: {
                        system("cls");
                        addRepairRecord(device, &device_count, repair, &repair_count);
                    }break;

                    case 3: {
                        system("cls");
                        searchRepairRecord(device, &device_count, repair, &repair_count);
                    }break;

                    case 0:
                        system("cls"); 
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;

                }
                printf("\n");

            }break;

            case 3:
            {
                system("cls");
                showBorrowMenu();
                int choice_case3;
                scanf("%d", &choice_case3);

                switch(choice_case3) {

                    case 1: {
                        system("cls");
                        borrowDevice(device, &device_count, borrow, &borrow_count);
                    }break;
                
                    case 2: {
                        system("cls");
                        returnDevice(device, &device_count, borrow, &borrow_count);
                    }break;

                    case 3: {
                        system("cls");
                        searchBorrowRecord(device, &device_count, borrow, &borrow_count);
                    }break;

                    case 0: 
                        system("cls");
                    break;

                    default: {
                        printf("输入错误!请重试!\n\n");
                    }break;
                
                }break;

            }break;

            case 4:
            {
                system("cls");
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
                system("cls");
                printf("感谢使用本程序!\n\n");
            }break;

            default:
            {
                system("cls");
                printf("输入错误，请重试!\n\n");
            }break;

        }

    }while(choice != 0);

    system("pause");
    
    return 0;
}