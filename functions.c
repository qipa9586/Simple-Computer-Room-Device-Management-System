#include <stdio.h>
#include <string.h>
#include "data.h"


int check_device_availability(int device_count)
{
    if (device_count > MAX_DEVICES)
    {
        printf("机房设备已满！\n\n");
        return 0;
    }

    if (device_count == 0)
    {
        printf("请先至少添加一个设备！\n\n");
        return 0;
    }

    return 1;
}

void cleanBuffer(void)
{
    int c;
    do{
        c = getchar();
    }while(c != '\n');
}


void updateStatus(Device device[], int device_count)
{
    if (!check_device_availability(device_count)) return;

    int temp_device_id;
    int found = FALSE;
    int index;
    int choice;
    
    printf("请输入要更新状态的设备的编号: ");
    scanf("%d", &temp_device_id);
    cleanBuffer();

    for (int i = 0; i < device_count; i++)
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


int addRepairRecord(Device device[], Repair repair[], int device_count)
{
    if (!check_device_availability(device_count)) return repair_count;

    int temp_device_id;
    int found = FALSE;
    int device_index = -1;

    printf("请输入维修的设备的编号: ");
    scanf("%d", &temp_device_id);
    cleanBuffer();

    for (int i = 0; i < device_count; i++)
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
        return repair_count;
    }


    printf("当前设备: %s\n", device[device_index].name);

    int new_repair_index = repair_count;

    repair[new_repair_index].repair_id = repair_count + 1;
    repair[new_repair_index].equipment_id = device[device_index].id;

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

    repair_count++;
    return repair_count;
}

void searchRepairRecord(Repair repair[], int repair_count)
{
    if (repair_count == 0)
    {
        printf("请先至少输入一个维修信息!\n\n");
        return;
    }

    int temp_repair_id;
    int index;
    int found = FALSE;

    printf("请输入要查询的维修编号: ");
    scanf("%d", &temp_repair_id);
    cleanBuffer();

    for (int i = 0; i < repair_count; i++)
    {
        if(temp_repair_id == repair[i].repair_id)
        {
            index = i;
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该编号的维修记录!请重试!\n\n");
        return;
    }

    printf("%-8s %8s %-20s %-10s %-10s %10s\n", 
           "维修编号", "设备编号", "故障描述", "维修费用", "维修人员", "维修日期");
    printf("——————————————————————————————————————————————————————————————————\n");
    printf("%-8s %8d %-20s %-10.2lf %-10s %04d-%02d-%02d", 
            repair[index].repair_id, repair[index].equipment_id, repair[index].fault_desc
            , repair[index].cost, repair[index].repair_person
            , repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
    printf("\n");
}
