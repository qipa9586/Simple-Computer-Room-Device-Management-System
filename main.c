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

        switch (choice)
        {
        case 1:
        {
            int choice_case1;
            do
            {
                system("cls");
                showInfoMenu();
                scanf("%d", &choice_case1);

                switch (choice_case1)
                {

                case 1:
                {
                    system("cls");
                    addNewDevice(device, &device_count);
                    system("pause");
                }
                break;

                case 2:
                {
                    system("cls");
                    editDeviceInfo(device, &device_count);
                    system("pause");
                }
                break;

                case 3:
                {
                    system("cls");
                    deleteDeviceInfo(device, &device_count);
                    system("pause");
                }
                break;

                case 4:
                {
                    system("cls");
                    searchDeviceInfo(device, &device_count);
                    system("pause");
                }
                break;

                case 5:
                {
                    system("cls");
                    displayAllDeviceInfo(device, &device_count);
                    system("pause");
                }
                break;

                case 6:
                {
                    system("cls");
                    int confirm = confirmReadInfo();
                    if (confirm)
                    {
                    readDeviceInfo(device, &device_count);
                    system("pause");
                    }
                    if (!confirm)
                    {
                        printf("已取消读取!\n\n");
                        system("pause");
                    }
                }

                case 0:
                {
                    system("cls");
                }
                break;

                default:
                {
                    printf("输入错误!请重试!\n\n");
                }
                break;
                }
            } while (choice_case1 != 0);
        }
        break;

        case 2:
        {
            int choice_case2;
            do
            {
                system("cls");
                showStatusMenu();

                scanf("%d", &choice_case2);

                switch (choice_case2)
                {

                case 1:
                {
                    system("cls");
                    updateStatus(device, &device_count);
                    system("pause");
                }
                break;

                case 2:
                {
                    system("cls");
                    addRepairRecord(device, &device_count, repair, &repair_count);
                    system("pause");
                }
                break;

                case 3:
                {
                    system("cls");
                    searchRepairRecord(device, &device_count, repair, &repair_count);
                    system("pause");
                }
                break;

                case 4:
                {
                    system("cls");
                    int confirm = confirmReadInfo();
                    if (confirm)
                    {
                    readRepairInfo(repair, &repair_count, device, &device_count);
                    system("pause");
                    }
                    if (!confirm)
                    {
                        printf("已取消读取!\n\n");
                        system("pause");
                    }
                }

                case 0:
                    system("cls");
                    break;

                default:
                {
                    printf("输入错误!请重试!\n\n");
                }
                break;
                }
            } while (choice_case2 != 0);
        }
        break;

        case 3:
        {
            int choice_case3;
            do
            {
                system("cls");
                showBorrowMenu();
                scanf("%d", &choice_case3);

                switch (choice_case3)
                {

                case 1:
                {
                    system("cls");
                    borrowDevice(device, &device_count, borrow, &borrow_count);
                    system("pause");
                }
                break;

                case 2:
                {
                    system("cls");
                    returnDevice(device, &device_count, borrow, &borrow_count);
                    system("pause");
                }
                break;

                case 3:
                {
                    system("cls");
                    searchBorrowRecord(device, &device_count, borrow, &borrow_count);
                    system("pause");
                }
                break;

                case 4:
                {
                    system("cls");
                    int confirm = confirmReadInfo();
                    if (confirm)
                    {
                    readBorrowInfo(borrow, &borrow_count, device, &device_count);
                    system("pause");
                    }
                    if (!confirm)
                    {
                        printf("已取消读取!\n\n");
                        system("pause");
                    }
                }

                case 0:
                    system("cls");
                    break;

                default:
                {
                    printf("输入错误!请重试!\n\n");
                }
                break;
                }
                break;
            } while (choice_case3 != 0);
        }
        break;

        case 4:
        {
            int choice_case4;

            do
            {
                system("cls");
                showOverallInfoMenu();
                scanf("%d", &choice_case4);

                switch (choice_case4)
                {

                case 1:
                {
                    system("cls");
                    deviceCategoryStats(device, &device_count);
                    system("pause");
                }
                break;

                case 2:
                {
                    system("cls");
                    deviceStatusStats(device, &device_count);
                    system("pause");
                }
                break;

                case 3:
                {
                    system("cls");
                    deviceBorrowStats(borrow, &borrow_count, device, &device_count);
                    system("pause");
                }
                break;

                case 4:
                {
                    system("cls");
                    generateReport(device, &device_count, repair, &repair_count,
                                   borrow, &borrow_count);
                    system("pause");
                }
                break;

                case 0:
                {
                    system("cls");
                }
                break;

                default:
                {
                    printf("输入错误!请重试!\n\n");
                }
                break;
                }
            } while (choice_case4 != 0);
        }
        break;

        case 0:
        {
            system("cls");
            printf("感谢使用本程序!\n制作: 第1小组\n\n");
        }
        break;

        default:
        {
            system("cls");
            printf("输入错误，请重试!\n\n");
        }
        break;
        }

    } while (choice != 0);

    system("pause");

    return 0;
}
