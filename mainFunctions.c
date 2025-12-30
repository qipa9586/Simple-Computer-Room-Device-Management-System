#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "assistFunctions.h"

void showEditMenu(void);

// 设备信息管理模块
void addNewDevice(Device device[], int *device_count)
{
    int judgment = FALSE;

    printf("请输入以下信息:\n");

    printf("设备编号: ");
    while (scanf("%d", &device[*device_count].id) != 1)
    {
        printf("设备编号仅可为数字!\n");
        printf("请重新输入设备编号: ");
        cleanBuffer();
    }
    cleanBuffer();

    for (int i = 0; i < *device_count; i++)
    {
        if (device[i].id == device[*device_count].id)
        {
            printf("此设备编号: %d 已存在，请重新输入!\n\n", device[i].id);
            i = 0;
            printf("请重新输入设备编号: ");
            while (scanf("%d", &device[*device_count].id) != 1)
            {
                printf("设备编号仅可为数字!\n");
                printf("请重新输入设备编号: ");
                cleanBuffer();
            }
            cleanBuffer();
        }
    }

    

    printf("设备名称: ");

    fgets(device[*device_count].name, sizeof(device[*device_count].name), stdin);
    device[*device_count].name[strcspn(device[*device_count].name, "\n")] = '\0';

    printf("设备类型: ");

    fgets(device[*device_count].type, sizeof(device[*device_count].type), stdin);
    device[*device_count].type[strcspn(device[*device_count].type, "\n")] = '\0';

    printf("品牌: ");

    fgets(device[*device_count].brand, sizeof(device[*device_count].brand), stdin);
    device[*device_count].brand[strcspn(device[*device_count].brand, "\n")] = '\0';

    printf("型号: ");

    fgets(device[*device_count].model, sizeof(device[*device_count].model), stdin);
    device[*device_count].model[strcspn(device[*device_count].model, "\n")] = '\0';

    printf("购买日期[YYYY-MM-DD]: ");
    scanf("%d-%d-%d", &device[*device_count].purchase_date.year, 
                      &device[*device_count].purchase_date.month, 
                      &device[*device_count].purchase_date.day);
    cleanBuffer();

    while (!isDateValid(device[*device_count].purchase_date))
    {
        printf("请重新输入购买日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d", &device[*device_count].purchase_date.year, 
                      &device[*device_count].purchase_date.month, 
                      &device[*device_count].purchase_date.day);
        cleanBuffer();
    }


    do
    {
        printf("价格: ");
        scanf("%lf", &device[*device_count].price);
        cleanBuffer();

        if (device[*device_count].price < 0) {
            printf("价格不能为负数, 请重试!\n\n");
            judgment = FALSE;
        } 
        else
            judgment = TRUE;
    } while (!judgment);

    while (device[*device_count].price >= 1e9)
    {
        printf("价格金额过大!\n");
        printf("请重新输入价格: ");
        scanf("%lf", &device[*device_count].price);
        cleanBuffer();
    }

    printf("信息输入成功!\n\n");
    
    strcpy(device[*device_count].status, "正常");
    (*device_count)++;
}

void editDeviceInfo(Device device[], int *device_count)
{
    int temp_device_id[2];
    char temp_device_name1[50], temp_device_name2[50];
    char temp_device_type1[30], temp_device_type2[30];
    char temp_device_brand1[30], temp_device_brand2[30];
    char temp_device_model1[30], temp_device_model2[30];
    int temp_device_date_year[2], temp_device_date_month[2], temp_device_date_day[2];
    double temp_device_price[2];

    if (!checkDeviceAvailable(*device_count)) return;

    int choice_edit, comfirm = FALSE;
    int found = FALSE;
    int device_index = -1;
    int device_id_temp;

    printf("需进行修改的设备编号: ");
    scanf("%d", &device_id_temp);
    cleanBuffer();

    for (int i = 0; i < *device_count; i++)
    {
        if (device[i].id == device_id_temp)
        {
            found = TRUE;
            device_index = i;
            break;
        }
    }

    if (!found)
    {
        printf("未找到该编号的设备!请重试!\n\n");
        system("pause");
        return;
    }

    do
    {
        system("cls");
        showEditMenu();
        scanf("%d", &choice_edit);
        cleanBuffer();

        switch (choice_edit)
        {
        case 1:
        {
            do
            {
                system("cls");
                printf("修改设备编号:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("设备原编号: %d\n", device[device_index].id);

                printf("设备新编号: ");
                scanf("%d", &temp_device_id[0]);
                cleanBuffer();

                printf("请再次输入设备新编号: ");
                scanf("%d", &temp_device_id[1]);
                cleanBuffer();

                if (temp_device_id[0] == temp_device_id[1])
                {
                    device[device_index].id = temp_device_id[0];
                    printf("设备编号修改成功!\n\n");
                    comfirm = TRUE;
                }
                else
                {
                    printf("两次输入的设备编号不一致，请重新输入!\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            system("pause");
        }
        break;

        case 2:
        {
            do
            {
                system("cls");
                printf("修改设备名称:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("设备原名称: %s\n", device[device_index].name);

                printf("设备新名称: ");

                fgets(temp_device_name1, sizeof(temp_device_name1), stdin);
                temp_device_name1[strcspn(temp_device_name1, "\n")] = '\0';

                printf("请再次输入设备新名称: ");

                fgets(temp_device_name2, sizeof(temp_device_name2), stdin);
                temp_device_name2[strcspn(temp_device_name2, "\n")] = '\0';

                if (strcmp(temp_device_name1, temp_device_name2) == 0)
                {
                    strcpy(device[device_index].name, temp_device_name2);

                    printf("设备名称修改成功!\n\n");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备名称不一致，请重新输入!\n\n");
                    comfirm = FALSE;
                }

            } while (!comfirm);
            system("pause");
        }
        break;

        case 3:
        {
            do
            {
                system("cls");
                printf("修改设备类型:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("设备原类型: %s\n", device[device_index].type);
                printf("设备新类型: ");

                fgets(temp_device_type1, sizeof(temp_device_type1), stdin);
                temp_device_type1[strcspn(temp_device_type1, "\n")] = '\0';

                printf("请再次输入设备新类型: ");

                fgets(temp_device_type2, sizeof(temp_device_type2), stdin);
                temp_device_type2[strcspn(temp_device_type2, "\n")] = '\0';

                if (strcmp(temp_device_type1, temp_device_type2) == 0)
                {
                    strcpy(device[device_index].type, temp_device_type2);
                    
                    printf("设备类型修改成功!\n\n");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备类型不一致, 请重新输入!\n\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            system("pause");
        }
        break;

        case 4:
        {
            do
            {
                system("cls");
                printf("修改设备品牌:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("原设备品牌: %s\n", device[device_index].brand);
                printf("设备新品牌: ");

                fgets(temp_device_brand1, sizeof(temp_device_brand1), stdin);
                temp_device_brand1[strcspn(temp_device_brand1, "\n")] = '\0';

                printf("请再次输入设备新品牌: ");
                
                fgets(temp_device_brand2, sizeof(temp_device_brand2), stdin);
                temp_device_brand2[strcspn(temp_device_brand2, "\n")] = '\0';

                if (strcmp(temp_device_brand1, temp_device_brand2) == 0)
                {
                    strcpy(device[device_index].brand, temp_device_brand2);

                    printf("设备品牌修改成功!\n\n");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备品牌不一致，请重新输入!\n\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            comfirm = FALSE;

            
            do
            {
                printf("修改设备型号:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }
                printf("设备原型号: %s\n", device[device_index].model);

                printf("更新的设备型号: ");

                fgets(temp_device_model1, sizeof(temp_device_model1), stdin);
                temp_device_model1[strcspn(temp_device_model1, "\n")] = '\0';

                printf("请再次输入设备新型号: ");
                
                fgets(temp_device_model2, sizeof(temp_device_model2), stdin);
                temp_device_model2[strcspn(temp_device_model2, "\n")] = '\0';

                if (strcmp(temp_device_model1, temp_device_model2) == 0)
                {
                    strcpy(device[device_index].model, temp_device_model2);

                    printf("设备型号修改成功!\n\n");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备型号不一致，请重新输入!\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            system("pause");
        }
        break;

        case 5:
        {
            do
            {
                system("cls");
                printf("修改设备购买日期:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("设备原购买日期: %d-%d-%d\n", 
                       device[device_index].purchase_date.year,
                       device[device_index].purchase_date.month,
                       device[device_index].purchase_date.day);
                printf("更新的设备购买日期: ");

                scanf("%d-%d-%d", &temp_device_date_year[0],
                                  &temp_device_date_month[0],
                                  &temp_device_date_day[0]);
                cleanBuffer();

                printf("请再次输入设备新购买日期: ");

                scanf("%d-%d-%d", &temp_device_date_year[1],
                                  &temp_device_date_month[1],
                                  &temp_device_date_day[1]);
                cleanBuffer();

                if (temp_device_date_year[0] == temp_device_date_year[1] &&
                    temp_device_date_month[0] == temp_device_date_month[1] &&
                    temp_device_date_day[0] == temp_device_date_day[1])
                {
                    device[device_index].purchase_date.year = temp_device_date_year[0];
                    device[device_index].purchase_date.month = temp_device_date_month[0];
                    device[device_index].purchase_date.day = temp_device_date_day[0];
                    printf("设备购买日期修改成功!\n\n");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备购买日期不一致，请重新输入!\n\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            system("pause");
        }
        break;

        case 6:
        {
            do
            {
                system("cls");
                printf("修改设备价格:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("设备原价格: %.2lf\n", device[device_index].price);

                printf("设备新价格: ");
                scanf("%lf", &temp_device_price[0]);
                cleanBuffer();

                printf("请再次输入设备新价格: ");
                scanf("%lf", &temp_device_price[1]);
                cleanBuffer();

                if (temp_device_price[0] == temp_device_price[1])
                {
                    device[device_index].price = temp_device_price[0];
                    printf("设备价格修改成功!");
                    comfirm = TRUE;
                }

                else
                {
                    printf("两次输入的设备价格不一致，请重新输入!\n\n");
                    comfirm = FALSE;
                }
            } while (!comfirm);
            system("pause");
        }
        break;

        case 7:
        {
            do
            {
                system("cls");
                printf("修改设备全部信息:\n");
                if (!confirmEdit())
                {
                    printf("已取消修改!\n\n");
                    return;
                }

                printf("原设备编号: %d\n", device[device_index].id);
                printf("原设备名称: %s\n", device[device_index].name);
                printf("原设备类型: %s\n", device[device_index].type);
                printf("原设备品牌: %s\n", device[device_index].brand);
                printf("原设备型号: %s\n", device[device_index].model);
                printf("原设备日期: %d-%d-%d\n", device[device_index].purchase_date.year,
                       device[device_index].purchase_date.month,
                       device[device_index].purchase_date.day);
                printf("原设备价格: %.2lf\n", device[device_index].price);
                printf("\n");

                printf("新设备编号: ");
                scanf("%d", &temp_device_id[0]);
                cleanBuffer();

                printf("新设备名称: ");
                fgets(temp_device_name1, sizeof(temp_device_name1), stdin);
                temp_device_name1[strcspn(temp_device_name1, "\n")] = '\0';

                printf("新设备类型: ");
                fgets(temp_device_type1, sizeof(temp_device_type1), stdin);
                temp_device_type1[strcspn(temp_device_type1, "\n")] = '\0';

                printf("新设备品牌: ");
                fgets(temp_device_brand1, sizeof(temp_device_brand1), stdin);
                temp_device_brand1[strcspn(temp_device_brand1, "\n")] = '\0';

                printf("新设备型号: ");
                fgets(temp_device_model1, sizeof(temp_device_model1), stdin);
                temp_device_model1[strcspn(temp_device_model1, "\n")] = '\0';

                printf("新设备购买日期: ");
                scanf("%d-%d-%d", &temp_device_date_year[0],
                                  &temp_device_date_month[0],
                                  &temp_device_date_day[0]);
                cleanBuffer();

                printf("新设备价格: ");
                scanf("%lf", &temp_device_price[0]);
                cleanBuffer();

                printf("\n");

                printf("请确认输入新设备信息是否正确!\n");
                confirmEdit();

                device[device_index].id = temp_device_id[0];

                strcpy(device[device_index].name, temp_device_name1);
                strcpy(device[device_index].type, temp_device_type1);
                strcpy(device[device_index].brand, temp_device_brand1);
                strcpy(device[device_index].model, temp_device_model1);
                
                device[device_index].purchase_date.year = temp_device_date_year[0];
                device[device_index].purchase_date.month = temp_device_date_month[0];
                device[device_index].purchase_date.day = temp_device_date_day[0];

                device[device_index].price = temp_device_price[0];

                printf("全部信息修改成功!\n\n");

                comfirm = TRUE;

            } while (!comfirm);
            system("pause");
        }
        break;

        case 0: {
            system("cls");
            choice_edit = 0;
        }
        break;

        default:
        {
            printf("输入错误!请重试!\n\n");
        }
        break;

        }
    } while (choice_edit != 0);

}

void deleteDeviceInfo(Device device[], int *device_count) 
{
    if (!checkDeviceAvailable(*device_count)) return;

    int temp_device_id;
    int found = FALSE;
    int index = -1;

    printf("需删除设备编号：");
    scanf("%d", &temp_device_id);
    cleanBuffer();

    for(int i = 0; i < *device_count; i++)
    {
        if(device[i].id == temp_device_id)
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

    if (strcmp(device[index].status, "借用中") == 0 || 
        strcmp(device[index].status, "维修中") == 0)
    {
        printf("=== 警告 ===\n该设备当前状态为'%s'，删除前请确认!\n", device[index].status);
    }

    if (!confirmDelete())
    {
        printf("已取消删除!\n\n");
        return;
    }
    
    for (int i = index; i < *device_count - 1; i++)
    {
        //id 前移
        device[i].id = device[i + 1].id;
        //名称前移
        strcpy(device[i].name, device[i + 1].name);
        //类型前移
        strcpy(device[i].type, device[i + 1].type);
        //品牌前移
        strcpy(device[i].brand, device[i + 1].brand);
        //型号前移
        strcpy(device[i].model, device[i + 1].model);
        //购买日期前移
        device[i].purchase_date.year  = device[i + 1].purchase_date.year;
        device[i].purchase_date.month = device[i + 1].purchase_date.month;
        device[i].purchase_date.day   = device[i + 1].purchase_date.day;
        //价格前移
        device[i].price = device[i + 1].price;
    }
    

    printf("设备信息删除成功!\n\n");
    (*device_count)--;
}

void searchDeviceInfo(Device device[], int *device_count)
{
    if (*device_count == 0)
    {
        printf("请先至少添加一个设备!\n\n");
        return;
    }

    int temp_device_id; 
    int index = -1;
    int found = FALSE;
    
    printf("请输入需要搜索的设备编号：");
    scanf("%d", &temp_device_id);

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
        
    printf("\n——————————————————————————————————————————————————————————————————————————————————————\n");
    printf("%8s %20s %10s %10s %10s %10s %10s %15s\n"
        , "设备编号", "设备名称", "设备类型", "设备品牌", "设备型号", "设备价格", "设备状态", "购买日期");
    printf("——————————————————————————————————————————————————————————————————————————————————————\n");
    printf("%8d %20s %10s %10s %10s %10.2lf %10s      %04d-%02d-%02d\n"
        , device[index].id, device[index].name, device[index].type, device[index].brand
        , device[index].model, device[index].price, device[index].status
        , device[index].purchase_date.year, device[index].purchase_date.month, device[index].purchase_date.day);
    printf("——————————————————————————————————————————————————————————————————————————————————————\n\n");  
}

void displayAllDeviceInfo(Device device[], int *device_count)
{
    printf("\n——————————————————————————————————————————————————————————————————————————————————————\n");
    printf("%8s %20s %10s %10s %10s %10s %10s %15s\n"
        , "设备编号", "设备名称", "设备类型", "设备品牌", "设备型号", "设备价格", "设备状态", "购买日期");
    printf("——————————————————————————————————————————————————————————————————————————————————————\n");
    for (int i = 0; i < *device_count; i++)
    {
        printf("%8d %20s %10s %10s %10s %10.2lf %10s      %04d-%02d-%02d"
        , device[i].id, device[i].name, device[i].type, device[i].brand
        , device[i].model, device[i].price, device[i].status
        , device[i].purchase_date.year, device[i].purchase_date.month, device[i].purchase_date.day);
        printf("\n");
    }
    printf("——————————————————————————————————————————————————————————————————————————————————————\n\n");
}
// 结束

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
    printf("当前状态: %s\n\n", device[index].status);
    printf("请输入要更新的状态\n(1-正常 2-故障 3-停用 4-维修中 5-报废): ");
    scanf("%d", &choice);
    cleanBuffer();

    if (choice == 1)
        strcpy(device[index].status, "正常");
    else if (choice == 2)
        strcpy(device[index].status, "故障");
    else if (choice == 3)
        strcpy(device[index].status, "停用");
    else if (choice == 4)
        strcpy(device[index].status, "维修中");
    else if (choice == 5)
        strcpy(device[index].status, "报废");
    else
    {
        printf("输入错误!请重试!\n\n");
        return;
    }

    printf("修改成功!\n当前设备状态: %s\n\n", device[index].status);
}

void addRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count)
{
    if (!checkDeviceAvailable(*device_count))
        return;

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
    strcpy(device[device_index].status, "维修中");

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
    while (!isDateValid(repair[new_repair_index].repair_date))
    {
        printf("请重新输入维修日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d", &repair[new_repair_index].repair_date.year,
          &repair[new_repair_index].repair_date.month,
          &repair[new_repair_index].repair_date.day);
        cleanBuffer();
    }

    while (compareDate(repair[new_repair_index].repair_date, device[device_index].purchase_date) == -1)
    {
        printf("维修日期不能早于购买日期!");
        printf("请重新输入维修日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d",&repair[new_repair_index].repair_date.year,
          &repair[new_repair_index].repair_date.month,
          &repair[new_repair_index].repair_date.day);
        cleanBuffer();
    }

    printf("请输入维修人员: ");
    fgets(repair[new_repair_index].repair_person,
          sizeof(repair[new_repair_index].repair_person), stdin);
    repair[new_repair_index].repair_person
        [strcspn(repair[new_repair_index].repair_person, "\n")] = '\0';

    printf("请输入维修费用: ");
    scanf("%lf", &repair[new_repair_index].cost);
    cleanBuffer();

    printf("维修信息添加成功!\n\n");

    

    (*repair_count)++;
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

    printf("请选择查询方式:\n");
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
            if (repair[i].repair_id == temp_repair_id)
            {
                index = i;
                found = TRUE;
                break;
            }
        }

        printf("\n————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8s %-8s %-15s %-20s %-10s %-10s %10s\n",
           "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修日期");
        printf("————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %04d-%02d-%02d",
           repair[index].repair_id, repair[index].device_id, getDeviceName(device, repair[index].device_id, *device_count), repair[index].fault_desc, repair[index].cost, repair[index].repair_person, repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
        printf("\n");
    }
    break;

    case 2:
    {
        printf("\n请输入要查询的设备编号: ");
        scanf("%d", &temp_device_id);
        cleanBuffer();

        for (int i = 0; i < *repair_count; i++)
        {
            if (repair[i].device_id == temp_device_id)
            {
                index = i;
                found = TRUE;
                break;
            }
        }

        printf("\n——————————————————————————————————————————————————————————————————\n");
        printf("%-8s %-8s %-15s %-20s %-10s %-10s %10s\n",
           "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修日期");
        printf("——————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %04d-%02d-%02d",
           repair[index].repair_id, repair[index].device_id, getDeviceName(device, repair[index].device_id, *device_count), repair[index].fault_desc, repair[index].cost, repair[index].repair_person, repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
        printf("\n");
    }
    break;

    case 3:
    {
        found = TRUE;
        printf("最近10条维修记录:\n\n");

        int temp_repair_count;

        if (*repair_count < 10)
        {
            temp_repair_count = *repair_count;
        }
        else
        {
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
                   repair[i].repair_id, repair[i].device_id, temp_device_name, repair[i].fault_desc, repair[i].cost, repair[i].repair_person, repair[i].repair_date.year, repair[i].repair_date.month, repair[i].repair_date.day);
            printf("\n");
        }
        printf("\n");
    }
    break;

    default:
    {
        printf("输入错误!请重试!\n\n");
    }
    break;
    }

    if (!found)
    {
        printf("未找到该编号的维修记录!请重试!\n\n");
        return;
    }
}
// 结束

// 设备借用管理模块
void borrowDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count))
        return;

    int temp_borrow_id;
    int device_index = -1;
    int found = FALSE;

    printf("请输入要借用的设备的编号: ");
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

    if (!strcmp(device[device_index].status, "借用中"))
    {
        printf("该设备已被借用!请重试!\n\n");
        return;
    }

    if (!strcmp(device[device_index].status, "报废"))
    {
        printf("该设备已报废, 无法借用!\n\n");
        return;
    }

    if (!strcmp(device[device_index].status, "停用"))
    {
        printf("该设备已停用, 无法借用!\n\n");
        return;
    }

    borrow[new_borrow_index].record_id = *borrow_count + 1;
    borrow[new_borrow_index].device_id = device[device_index].id;

    printf("请输入借用日期[YYYY-MM-DD]: ");
    scanf("%d-%d-%d", &borrow[new_borrow_index].borrow_date.year, 
        &borrow[new_borrow_index].borrow_date.month, 
        &borrow[new_borrow_index].borrow_date.day);
    cleanBuffer();

    // 日期验证
    while (!isDateValid(borrow[new_borrow_index].borrow_date))
    {
        printf("请重新输入借用日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d", &borrow[new_borrow_index].borrow_date.year, 
            &borrow[new_borrow_index].borrow_date.month, 
            &borrow[new_borrow_index].borrow_date.day);
        cleanBuffer();
    }

    while (compareDate(borrow[new_borrow_index].borrow_date, device[device_index].purchase_date) == -1)
    {
        printf("借用日期不能早于购买日期!");
        printf("请重新输入借用日期[YYYY-MM-DD]: ");
        scanf("%d-%d-%d", &borrow[new_borrow_index].borrow_date.year, 
            &borrow[new_borrow_index].borrow_date.month, 
            &borrow[new_borrow_index].borrow_date.day);
        cleanBuffer();
    }

    strcpy(borrow[new_borrow_index].status, "借用中");

    printf("借用成功!\n\n");
    printf("当前借用设备: %s\n", device[device_index].name);
    printf("当前借用编号: %d\n", borrow[new_borrow_index].record_id);

    borrow[new_borrow_index].actual_return_date = calcuReturnDate(borrow[new_borrow_index].borrow_date);
    printf("应归还时间: %04d-%02d-%02d\n\n", borrow[new_borrow_index].actual_return_date.year, borrow[new_borrow_index].actual_return_date.month, borrow[new_borrow_index].actual_return_date.day);

    (*borrow_count)++;
}

void returnDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count))
        return;
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

    for (int i = 0; i < *borrow_count; i++)
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

        // 日期验证与比较日期: 不能比借用时间早

        while (!isDateValid(borrow[index].return_date))
        {
            printf("请重新输入归还日期[YYYY-MM-DD]: ");
            scanf("%d-%d-%d", &borrow[index].return_date.year
                        , &borrow[index].return_date.month
                        , &borrow[index].return_date.day);
            cleanBuffer();
        }

        while (compareDate(borrow[index].return_date, borrow[index].borrow_date) == -1)
        {
            printf("归还日期不能早于借用日期!\n\n");
            printf("请重新输入归还日期[YYYY-MM-DD]: ");
            scanf("%d-%d-%d", &borrow[index].return_date.year
                        , &borrow[index].return_date.month
                        , &borrow[index].return_date.day);
            cleanBuffer();
        }

        strcpy(borrow[index].status, "已归还");
        printf("该设备已归还!\n\n");

        if (compareDate(borrow[index].return_date, borrow[index].actual_return_date) == 1)
        {
            strcpy(borrow[index].status, "逾期");
            printf("您逾期 %d 天后归还!\n\n", calculateOverdueDays(borrow[index].return_date, borrow[index].actual_return_date));
            return;
        }
    }

}

void searchBorrowRecord(Device device[], int *device_count, Borrow borrow[], int *borrow_count)
{
    if (!checkDeviceAvailable(*device_count))
        return;
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

        printf("\n————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8s %-8s %-15s  %10s   %10s   %10s  %8s %15s\n"
                , "借用编号", "设备编号", "设备名称", "借用日期", "实际归还日期", "应归还日期", "状态", "逾期提醒");
        printf("————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s \n",
            borrow[index].record_id, borrow[index].device_id, getDeviceName(device, borrow[index].device_id, *device_count)
            , borrow[index].borrow_date.year, borrow[index].borrow_date.month, borrow[index].borrow_date.day
            , borrow[index].return_date.year, borrow[index].return_date.month, borrow[index].return_date.day
            , borrow[index].actual_return_date.year, borrow[index].actual_return_date.month, borrow[index].actual_return_date.day
            , borrow[index].status);
        // 逾期提醒
        int overdue_days = calculateOverdueDays(borrow[index].return_date, borrow[index].actual_return_date);
        if (strcmp(borrow[index].status, "已归还") == 0) {
                printf("%15s", "\\");
        }
        if (strcmp(borrow[index].status, "已归还") != 0)
        {
            if (overdue_days > 0) {
                printf("%15s", "\\");
            }
            else if(overdue_days > 0) {
                printf("您已逾期 %d 天", overdue_days);
            }
            else {
                printf("%15s", "即将逾期");
            }
            printf("\n");
        }
    }
    break;

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

        printf("\n————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8s %-8s %-15s  %10s   %10s   %10s  %8s %15s\n"
                , "借用编号", "设备编号", "设备名称", "借用日期", "实际归还日期", "应归还日期", "状态", "逾期提醒");
        printf("————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s \n",
            borrow[index].record_id, borrow[index].device_id, getDeviceName(device, borrow[index].device_id, *device_count), borrow[index].borrow_date.year, borrow[index].borrow_date.month, borrow[index].borrow_date.day, borrow[index].return_date.year, borrow[index].return_date.month, borrow[index].return_date.day, borrow[index].actual_return_date.year, borrow[index].actual_return_date.month, borrow[index].actual_return_date.day, borrow[index].status);
        // 逾期提醒
        int overdue_days = calculateOverdueDays(borrow[index].return_date, borrow[index].actual_return_date);
        if (strcmp(borrow[index].status, "已归还") == 0) {
                printf("%15s", "\\");
        }
        if (strcmp(borrow[index].status, "已归还") != 0)
        {
            if (overdue_days > 0) {
                printf("%15s", "\\");
            }
            else if(overdue_days > 0) {
                printf("您已逾期 %d 天", overdue_days);
            }
            else {
                printf("%15s", "即将逾期");
            }
            printf("\n");
        }
    }
    break;

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
        printf("%-8s %-8s %-15s  %10s   %10s   %10s  %8s %15s\n"
            , "借用编号", "设备编号", "设备名称", "借用日期", "实际归还日期", "应归还日期", "状态", "逾期提醒");
        printf("——————————————————————————————————————————————————————————————————\n");

        for (int i = 0; i < temp_borrow_count; i++)
        {
            char temp_device_name[50];
            strcpy(temp_device_name, "未知设备");

            for (int j = 0; j < *device_count; j++)
            {
                if (device[j].id == borrow[i].device_id)
                {
                    strcpy(temp_device_name, device[j].name);
                    break;
                }
            }

            printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s ",
                   borrow[i].record_id, borrow[i].device_id, temp_device_name, borrow[i].borrow_date.year, borrow[i].borrow_date.month, borrow[i].borrow_date.day, borrow[i].return_date.year, borrow[i].return_date.month, borrow[i].return_date.day, borrow[i].actual_return_date.year, borrow[i].actual_return_date.month, borrow[i].actual_return_date.day, borrow[i].status);
            // 添加即将逾期提醒
            int overdue_days = calculateOverdueDays(borrow[i].return_date, borrow[i].actual_return_date);

            if (strcmp(borrow[i].status, "已归还") == 0) {
                printf("%15s", "\\");
            }
            if (strcmp(borrow[i].status, "已归还") != 0)
            {
                if (overdue_days > 0) {
                    printf("%15s", "\\");
                }
                else if(overdue_days > 0) {
                    printf("您已逾期 %d 天", overdue_days);
                }
                else {
                    printf("%15s", "即将逾期");
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    break;

    default:
    {
        printf("输入错误!请重试!\n\n");
    }
    break;
    }

    if (!found)
    {
        printf("未找到该设备!请重试!\n\n");
        return;
    }
    
}
// 结束

// 统计报表模块
void deviceCategoryStats(Device device[], int device_count)
{
    
}