#include <stdio.h>
#include <string.h>
#include "data.h"
#include "assistFunctions.h"

// 设备状态管理模块
void updateStatus(Device device[], int *device_count)
{
    if (!checkDeviceAvailable(*device_count)) return;

    int temp_device_id;
    int found = FALSE;
    int index = -1;
    int choice;
    
    printf("请输入要更新状态的设备的编号: ");
    scanf("%d", &temp_device_id);
    cleanBuffer();

    for (int i = 0; i < *device_count; i++)
    {
        if (device[i].id == temp_device_id)
        {
            found = TRUE;
            index = i;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该编号的设备!请重试!\n\n");
        return;
    }

    printf("该设备为: %s\n", device[index].name);
    printf("当前状态: %s\n", device[index].status);
    printf("请输入要更新的状态\n(1-正常 2-故障 3-停用 4-维修中 5-报废): ");
    scanf("%d", &choice);
    cleanBuffer();

    if (choice == 1) strcpy(device[index].status, "正常");
    else if (choice == 2) strcpy(device[index].status, "故障");
    else if (choice == 3) strcpy(device[index].status, "停用");
    else if (choice == 4) strcpy(device[index].status, "维修中");
    else if (choice == 5) strcpy(device[index].status, "报废");
    else 
    {
        printf("输入错误!请重试!\n\n");
        return;
    }

    printf("修改成功!\n当前设备状态: %s\n\n", device[index].status);
    
}


void addRepairRecord(Device device[], Repair repair[], int *device_count, int *repair_count)
{
    if (!checkDeviceAvailable(*device_count)) return;

    int temp_device_id;
    int found = FALSE;
    int device_index = -1;

    printf("请输入维修的设备的编号: ");
    scanf("%d", &temp_device_id);
    cleanBuffer();

    for (int i = 0; i < *device_count; i++)
    {
        if (device[i].id == temp_device_id)
        {
            found = TRUE;
            device_index = i;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该编号的设备!请重试!\n\n");
        return;
    }


    printf("当前设备: %s\n", device[device_index].name);

    int new_repair_index = *repair_count;

    repair[new_repair_index].repair_id = *repair_count + 1;
    repair[new_repair_index].device_id = device[device_index].id;

    printf("当前维修编号: %d\n\n", repair[new_repair_index].repair_id);

    printf("请输入故障描述: ");
    fgets(repair[new_repair_index].fault_desc, 
        sizeof(repair[new_repair_index].fault_desc), stdin);
    
    repair[new_repair_index].fault_desc
    [strcspn(repair[new_repair_index].fault_desc, "\n")] = '\0';
            
    printf("请输入维修日期[YYYY-MM-DD]: ");
    scanf("%d-%d-%d", &repair[new_repair_index].repair_date.year, 
                      &repair[new_repair_index].repair_date.month, 
                      &repair[new_repair_index].repair_date.day);
    cleanBuffer();
    // 输入验证
            
    printf("请输入维修人员: ");
    fgets(repair[new_repair_index].repair_person, 
        sizeof(repair[new_repair_index].repair_person), stdin);
    repair[new_repair_index].repair_person
    [strcspn(repair[new_repair_index].repair_person, "\n")] = '\0';

    printf("请输入维修费用: ");
    scanf("%lf", &repair[new_repair_index].cost);
    cleanBuffer();

    printf("维修信息添加成功!\n\n");

    *repair_count++;

}

void searchRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count)
{
    if (*repair_count == 0)
    {
        printf("请先至少输入一个维修信息!\n\n");
        return;
    }

    int temp_repair_id, temp_device_id;
    int choice_repair;
    int index = -1;
    int found = FALSE;

    printf("\n请选择查询方式:\n");
    printf("1. 按维修编号查询\n2. 按设备编号查询\n3. 显示最近10条维修记录\n");
    printf("请选择操作(1-3): ");
    scanf("%d", &choice_repair);
    cleanBuffer();

    switch (choice_repair)
    {
        case 1:
        {
            printf("\n请输入要查询的维修编号: ");
            scanf("%d", &temp_repair_id);
            cleanBuffer();

            for (int i = 0; i < *repair_count; i++)
            {
                if(repair[i].repair_id == temp_repair_id)
                {
                    index = i;
                    found = TRUE;
                    break;
                }
            }
        }break;

        case 2:
        {
            printf("\n请输入要查询的设备编号: ");
            scanf("%d", &temp_device_id);
            cleanBuffer();

            for (int i = 0; i < *repair_count; i++)
            {
                if(repair[i].device_id == temp_device_id)
                {
                    index = i;
                    found = TRUE;
                    break;
                }
            }
        }break;

        case 3:
        {
            found = TRUE;
            printf("最近10条维修记录:\n\n");
            
            int temp_repair_count;

            if (*repair_count < 10){
                temp_repair_count = *repair_count;
            }
            else {
                temp_repair_count = 10;
            }

            
            printf("\n——————————————————————————————————————————————————————————————————\n");
            printf("%-8s %-8s %-15s %-20s %-10s %-10s %10s\n", 
                        "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修日期");
            printf("——————————————————————————————————————————————————————————————————\n");

            for (int i = 0; i < temp_repair_count; i++)
            {
                char temp_device_name[50];
                strcpy(temp_device_name, "未知设备");

                for (int j = 0; j < *device_count; j++)
                {
                    if (device[j].id == repair[i].device_id)
                    {
                        strcpy(temp_device_name, device[j].name);
                        break;
                    }
                }

                printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %04d-%02d-%02d", 
                repair[i].repair_id, repair[i].device_id, temp_device_name
                , repair[i].fault_desc, repair[i].cost, repair[i].repair_person
                , repair[i].repair_date.year, repair[i].repair_date.month, repair[i].repair_date.day);
                printf("\n");
            }
            printf("\n");
        }break;

        default:
        {
            printf("输入错误!请重试!\n\n");
        }break;
    }

    if (!found)
    {
        printf("未找到该编号的维修记录!请重试!\n\n");
        return;
    }

    printf("\n——————————————————————————————————————————————————————————————————\n");
    printf("%-8s %-8s %-15s %-20s %-10s %-10s %10s\n", 
           "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修日期");
    printf("——————————————————————————————————————————————————————————————————\n");
    printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %04d-%02d-%02d", 
            repair[index].repair_id, repair[index].device_id, getDeviceName(device, repair[index].device_id, *device_count)
            , repair[index].fault_desc, repair[index].cost, repair[index].repair_person
            , repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
    printf("\n");
}
// 结束

// 设备借用管理模块
void borrowDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count)) return;
    
    int temp_borrow_id;
    int device_index = -1;
    int found = FALSE;

    printf("请输入要借用设备的编号: ");
    scanf("%d", &temp_borrow_id);
    cleanBuffer();

    for (int i = 0; i < *device_count; i++)
    {
        if (device[i].id == temp_borrow_id)
        {
            device_index = i;
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该设备!请重试!\n\n");
        return;
    }

    int new_borrow_index = *borrow_count;

    if (!strcmp(borrow[new_borrow_index].status, "借用中"))
    {
        printf("该设备已被借用!请重试!\n\n");
        return;
    }

    borrow[new_borrow_index].record_id = *borrow_count + 1;
    borrow[new_borrow_index].device_id = device[device_index].id;

    printf("请输入借用日期[YYYY-MM-DD]: ");
    scanf("%d-%d-%d", &borrow[new_borrow_index].borrow_date.year
                    , &borrow[new_borrow_index].borrow_date.month
                    , &borrow[new_borrow_index].borrow_date.day);
    cleanBuffer();
    
    //日期验证
    if (!isDateValid(borrow[new_borrow_index].borrow_date)) return;

    strcpy(borrow[new_borrow_index].status, "借用中");

    printf("借用成功!\n\n");
    printf("当前借用设备: %s\n", device[device_index].name);
    printf("当前借用编号: %d\n", borrow[new_borrow_index].record_id);
    
    borrow[new_borrow_index].actual_return_date = calcuReturnDate(borrow[new_borrow_index].borrow_date);
    printf("应归还时间: %04d-%02d-%02d\n\n"
        , borrow[new_borrow_index].actual_return_date.year     
        , borrow[new_borrow_index].actual_return_date.month
        , borrow[new_borrow_index].actual_return_date.day);

    *borrow_count++;
}

void returnDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count)) return;
    if (*borrow_count == 0) 
    {
        printf("请先至少输入一个借用信息!\n\n");
        return;
    }

    int temp_borrow_id;
    int index = -1;
    int found = FALSE;

    printf("请输入要归还的设备的借用编号: ");
    scanf("%d", &temp_borrow_id);
    cleanBuffer();

    for (int i = 0; i < borrow_count; i++)
    {
        if (borrow[i].record_id == temp_borrow_id)
        {
            index = i;
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该设备!请重试!\n\n");
        return;
    }

    if (!strcmp(borrow[index].status, "已归还"))
    {
        printf("该设备已归还!请重试!\n\n");
        return;
    }

    if (!strcmp(borrow[index].status, "借用中"))
    {
        printf("请输入归还日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d", &borrow[index].return_date.year
                        , &borrow[index].return_date.month
                        , &borrow[index].return_date.day);
        cleanBuffer();

        strcpy(borrow[index].status, "已归还");
        printf("该设备已归还!\n");

        if (compareDate(borrow[index].return_date, borrow[index].actual_return_date) == 1)
        {
            strcpy(borrow[index].status, "逾期");
            printf("您逾期 %d 天后归还!\n\n"
                , isOverdue(borrow[index].return_date, borrow[index].actual_return_date));
            return;
        }
    }

    *borrow_count--;
}


void searchBorrowRecord(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count)) return;
    if (*borrow_count == 0) 
    {
        printf("请先至少输入一个借用信息!\n\n");
        return;
    }

    int temp_borrow_id, temp_device_id;
    int choice_return;
    int found = FALSE;
    int index = -1;
    
    printf("\n请选择查询方式:\n");
    printf("1. 按借用编号查询\n2. 按设备编号查询\n3. 显示最近10条借用记录\n");
    printf("请选择操作(1-3): ");
    scanf("%d", &choice_return);
    cleanBuffer();

    switch (choice_return)
    {
        case 1:
        {
            printf("请输入借用编号: ");
            scanf("%d", &temp_borrow_id);
            cleanBuffer();

            for (int i = 0; i < *borrow_count; i++)
            {
                if (borrow[i].record_id == temp_borrow_id)
                {
                    index = i;
                    found = TRUE;
                    break;
                }
            } 
        }break;

        case 2:
        {
            printf("请输入设备编号: ");
            scanf("%d", &temp_device_id);
            cleanBuffer();

            for (int i = 0; i < *borrow_count; i++)
            {
                if (borrow[i].device_id == temp_device_id)
                {
                    index = i;
                    found = TRUE;
                    break;
                }
            }
        }break;

        case 3:
        {
            found = TRUE;
            printf("最近10条借用记录:\n\n");

            int temp_borrow_count = 0;

            if (*borrow_count < 10) {
                temp_borrow_count = *borrow_count;
            }
            else {
                temp_borrow_count = 10;
            }

            printf("\n——————————————————————————————————————————————————————————————————\n");
            printf("%-8s %-8s %-15s  %10s   %10s   %10s  %8s"
                    , "借用编号", "设备编号", "设备名称", "借用日期", "实际归还日期", "应归还日期", "状态");
            printf("——————————————————————————————————————————————————————————————————\n");

            for (int i = 0; i < temp_borrow_count; i++)
            {
                char temp_device_name[50];
                strcpy(temp_device_name, "未知设备");

                for (int j = 0; j < *device_count; j++)
                {
                    if (device[j].id == borrow[i].device_id) {
                        strcpy(temp_device_name, device[j].name);
                        break;
                    }
                }

                printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s", 
                borrow[i].record_id, borrow[i].device_id, temp_device_name
                , borrow[i].borrow_date.year, borrow[i].borrow_date.month, borrow[i].borrow_date.day
                , borrow[i].return_date.year, borrow[i].return_date.month, borrow[i].return_date.day
                , borrow[i].actual_return_date.year, borrow[i].actual_return_date.month, borrow[i].actual_return_date.day
                , borrow[i].status);
                printf("\n");
            }
            printf("\n");
        }break;

        default: {
            printf("输入错误!请重试!\n\n");
        }break;
    }

    if (!found)
    {
        printf("未找到该设备!请重试!\n\n");
        return;
    }

    //case1和case2共用区
    printf("\n——————————————————————————————————————————————————————————————————\n");
    printf("%-8s %-8s %-15s  %10s   %10s   %10s  %8s"
            , "借用编号", "设备编号", "设备名称", "借用日期", "实际归还日期", "应归还日期", "状态");
    printf("——————————————————————————————————————————————————————————————————\n");

    printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s", 
                borrow[index].record_id, borrow[index].device_id, getDeviceName(device, borrow[index].device_id, *device_count)
                , borrow[index].borrow_date.year, borrow[index].borrow_date.month, borrow[index].borrow_date.day
                , borrow[index].return_date.year, borrow[index].return_date.month, borrow[index].return_date.day
                , borrow[index].actual_return_date.year, borrow[index].actual_return_date.month, borrow[index].actual_return_date.day
                , borrow[index].status);
                printf("\n");

}
// 结束