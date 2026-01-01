#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "assistFunctions.h"

void showEditMenu(void);
void showGenerateReportMenu(void);

// 设备信息管理模块
void addNewDevice(Device device[], int *device_count)
{
    int judgment = FALSE;
    int valid_id = FALSE;
    int batch_add_count;

    do
    {
        batch_add_count = confirmBatchAdd();
        if(batch_add_count == 0)
        {
            system("cls");
            return;
        }    
        if(*device_count + batch_add_count > 100)
        {
            system("cls");
            printf("批量添加设备数超过系统剩余可容纳数,请重新输入！\n\n");
        }    
    } while (*device_count + batch_add_count > 100);

    printf("请输入以下信息:\n");
    
    // 输入验证
    do
    {
        valid_id = TRUE;

        printf("设备编号: ");
        while (scanf("%d", &device[*device_count].id) != 1)
        {
            printf("设备编号仅可为数字!\n");
            printf("请重新输入设备编号: ");
            cleanBuffer();
        }
        cleanBuffer();

        if (device[*device_count].id < 0)
        {
            printf("设备编号必须为正整数!\n");
            valid_id = FALSE;
            continue;
        }
    
        for (int i = 0; i < *device_count; i++)
        {
            if (device[i].id == device[*device_count].id)
            {
                printf("此设备编号: %d 已存在，请重新输入!\n\n", device[i].id);
                valid_id = FALSE;
                break;
            }
        } 
    } while (!valid_id);


    printf("设备名称: ");

    // 运用fgets好处:字符串中可以有空格, 用scanf("%s")遇到空格就停止了
    // 运用fgets的标准输入流存储字符串
    fgets(device[*device_count].name, sizeof(device[*device_count].name), stdin);
    // 此处strcspn函数含义:在device[*device_count].(结构体成员)读取到"\n"就返回在这个对应的下标
    // 用来清除字符数组中的换行符
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

    // 日期验证
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

        // 输入验证
        if (device[*device_count].price < 0) {
            printf("价格不能为负数, 请重试!\n\n");
            judgment = FALSE;
        } 
        else
            judgment = TRUE;
    } while (!judgment);

    // 输入验证
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

    for (int j = *device_count; j < (*device_count) + batch_add_count - 1; j++)
    {
        device[j].id = device[j - 1].id + 1;
        strcpy(device[j].name,  device[(*device_count) - 1].name);
        strcpy(device[j].type,  device[(*device_count) - 1].type);
        strcpy(device[j].brand, device[(*device_count) - 1].brand);
        strcpy(device[j].model, device[(*device_count) - 1].model);
        device[j].purchase_date.year = device[(*device_count) - 1].purchase_date.year;
        device[j].purchase_date.month = device[(*device_count) - 1].purchase_date.month;
        device[j].purchase_date.day = device[(*device_count) - 1].purchase_date.day;
        device[j].price = device[(*device_count) - 1].price;
        strcpy(device[j].status, "正常");
    }
    *device_count = (*device_count) + batch_add_count - 1;
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
            system("pause");
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

    printf("当前设备: %s\n\n", device[index].name);
    
    // for循环让后面的把要删除的覆盖掉
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

void readDeviceInfo(Device device[], int *device_count)
{
    // 使用.csv格式文件能更好读取数据
    FILE *file = fopen("device_report.csv", "r");

    if (file == NULL)
    {
        printf("无法打开设备信息文件!\n\n");
        printf("请确保已使用生成报表功能创建了设备信息文件!\n\n");
        return;
    }

    char line[256];
    int count = 0; // 读取的设备数

    printf("正在读取设备信息...\n");
    
    // 跳过报表表头
    fgets(line, sizeof(line), file);
    
    // while循环继续读取接下来的行中的数据
    while (*device_count < MAX_DEVICES && fgets(line, sizeof(line), file) != NULL)
    {
        // 定义临时变量
        Device temp; 
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';
        // 解析 CSV 格式
        char *token;           // 分割出来的存在这里
        int field = 0;         // 每一段
        char *line_ptr = line; // 保存指针
        // strtok_r函数: 线程安全的字符串分割函数, 这里用逗号分割CSV行
        // while循环进行分割各个部分
        while ((token = strtok_r(line_ptr, ",", &line_ptr)) != NULL && field < 8)
        {
            // 去除字段包含的引号
            if (token[0] == '"' && token[strlen(token) - 1] == '"')
            {
                token[strlen(token)-1] = '\0'; // 最后一个双引号变为'\0'
                token++;                       // 跳过开头的双引号
            }
            // atoi函数强制转换为整形, atof函数强制转换为浮点型
            // 并存入临时变量中
            switch(field)
            {
                case 0: temp.id = atoi(token); break;
                case 1: strcpy(temp.name, token); break;
                case 2: strcpy(temp.type, token); break;
                case 3: strcpy(temp.brand, token); break;
                case 4: strcpy(temp.model, token); break;
                case 5: temp.price = atof(token); break;
                case 6: strcpy(temp.status, token); break;
                case 7: 
                    sscanf(token, "%d-%d-%d", 
                           &temp.purchase_date.year,
                           &temp.purchase_date.month,
                           &temp.purchase_date.day);
                    break;
            }
            field++;

        }
        
        if (field == 8)
        {
            device[*device_count] = temp;
            (*device_count)++;
            count++;
            printf("成功读取设备: 编号 : %d, 名称 : %s\n", temp.id, temp.name);
        }
    }
    
    fclose(file);
    if (count == 0) {
        printf("没有找到设备信息。\n");
    } else {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("总共找到 %d 个设备。\n", count);
    }
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
    printf("请输入要更新的状态:\n(1-正常 2-故障 3-停用)\n");
    printf("请选择操作: ");
    scanf("%d", &choice);
    cleanBuffer();

    if (choice == 1)
        strcpy(device[index].status, "正常");
    else if (choice == 2)
        strcpy(device[index].status, "故障");
    else if (choice == 3)
        strcpy(device[index].status, "停用");
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

    int choose_status;
    strcpy(repair[new_repair_index].status, "未知状态");
    printf("请选择维修状态:\n(1-已维修 2-维修中 3-报废)\n");
    printf("请选择操作: ");
    scanf("%d", &choose_status);

    if (choose_status == 1) strcpy(repair[new_repair_index].status, "已维修");
    else if (choose_status == 2) strcpy(repair[new_repair_index].status, "维修中");
    else if (choose_status == 3) strcpy(repair[new_repair_index].status, "报废");
    else {
        printf("输入错误!请重试!\n\n");
        return;
    }

    strcpy(device[device_index].status, repair[new_repair_index].status);

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
        printf("%-8s %-8s %-15s %-20s %-10s %-10s %-10s %10s\n",
           "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修状态", "维修日期");
        printf("————————————————————————————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %-10s %04d-%02d-%02d"
           , repair[index].repair_id, repair[index].device_id, getDeviceName(device, repair[index].device_id, *device_count)
           , repair[index].fault_desc, repair[index].cost, repair[index].repair_person, repair[index].status
           , repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
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
        printf("%-8s %-8s %-15s %-20s %-10s %-10s %-10s %10s\n",
           "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修状态", "维修日期");
        printf("——————————————————————————————————————————————————————————————————\n");
        printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %-10s %04d-%02d-%02d"
            , repair[index].repair_id, repair[index].device_id, getDeviceName(device, repair[index].device_id, *device_count)
            , repair[index].fault_desc, repair[index].cost, repair[index].repair_person, repair[index].status
            , repair[index].repair_date.year, repair[index].repair_date.month, repair[index].repair_date.day);
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
        printf("%-8s %-8s %-15s %-20s %-10s %-10s %-10s %10s\n",
               "维修编号", "设备编号", "设备名称", "故障描述", "维修费用", "维修人员", "维修状态", "维修日期");
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

            printf("%-8d %-8d %-15s %-20s %-10.2lf %-10s %-10s %04d-%02d-%02d"
                ,repair[i].repair_id, repair[i].device_id, temp_device_name, repair[i].fault_desc
                , repair[i].cost, repair[i].repair_person, repair[index].status
                , repair[i].repair_date.year, repair[i].repair_date.month, repair[i].repair_date.day);
            printf("\n");
        }
        printf("\n");
    }
    break;

    default:
    {
        printf("输入错误!请重试!\n\n");
        return;
    }
    break;
    }

    if (!found)
    {
        printf("未找到该编号的维修记录!请重试!\n\n");
        return;
    }
}

void readRepairInfo(Repair repair[], int *repair_count, int *device_count)
{
    FILE *file = fopen("repair_report.csv", "r");

    if (file == NULL)
    {
        printf("无法打开维修信息文件!\n\n");
        printf("请确保已使用生成报表功能创建了维修信息文件!\n\n");
        return;
    }

    if (*device_count == 0)
    {
        printf("请先至少添加一个设备信息!\n\n");
        return;
    }

    char line[256];
    int count = 0;

    printf("正在读取维修信息...\n");
    
    // 跳过报表表头
    fgets(line, sizeof(line), file);
    
    while (*repair_count < MAX_DEVICES && fgets(line, sizeof(line), file) != NULL)
    {
        Repair temp;
        
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';
        
        // 解析 CSV 格式
        char *token;
        int field = 0;
        char *line_ptr = line;
        
        while ((token = strtok_r(line_ptr, ",", &line_ptr)) != NULL && field < 6)
        {
            // 去除字段包含的引号
            if (token[0] == '"' && token[strlen(token) - 1] == '"')
            {
                token[strlen(token)-1] = '\0';
                token++;
            }
            
            switch(field)
            {
                case 0: temp.repair_id = atoi(token); break;
                case 1: temp.device_id = atoi(token); break;
                case 2: strcpy(temp.fault_desc, token); break;
                case 3: strcpy(temp.repair_person, token); break;
                case 4: temp.cost = atof(token); break;
                case 5: sscanf(token, "%d-%d-%d", 
                           &temp.repair_date.year,
                           &temp.repair_date.month,
                           &temp.repair_date.day);
                        break;
            }
            field++;
        }
        
        if (field == 6)
        {
            repair[*repair_count] = temp;
            (*repair_count)++;
            count++;
            printf("成功读取设备: 编号 : %d\n", temp.device_id);
        }
    }
    
    fclose(file);
    if (count == 0) {
        printf("没有找到维修信息。\n");
    } else {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("总共找到 %d 个维修信息。\n", count);
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

    printf("当前借用设备: %s\n\n", device[device_index].name);
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

            printf("%-8d %-8d %-15s  %04d-%02d-%02d   %04d-%02d-%02d   %04d-%02d-%02d  %8s "
                , borrow[i].record_id, borrow[i].device_id, temp_device_name
                , borrow[i].borrow_date.year, borrow[i].borrow_date.month, borrow[i].borrow_date.day
                , borrow[i].return_date.year, borrow[i].return_date.month, borrow[i].return_date.day
                , borrow[i].actual_return_date.year, borrow[i].actual_return_date.month, borrow[i].actual_return_date.day
                , borrow[i].status);
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
        return;
    }
    break;
    }

    if (!found)
    {
        printf("未找到该设备!请重试!\n\n");
        return;
    }
    
}

void readBorrowInfo(Borrow borrow[], int *borrow_count, int *device_count)
{
    FILE *file = fopen("borrow_report.csv", "r");

    if (file == NULL)
    {
        printf("无法打开借用信息文件!\n\n");
        printf("请确保已使用生成报表功能创建了借用信息文件!\n\n");
        return;
    }

    if (*device_count == 0)
    {
        printf("请先至少添加一个设备信息!\n\n");
        return;
    }

    char line[256];
    int count = 0;

    printf("正在读取借用信息...\n");
    
    fgets(line, sizeof(line), file);
    
    while (*borrow_count < MAX_DEVICES && fgets(line, sizeof(line), file) != NULL)
    {
        Borrow temp;
        
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';
        
        // 解析 CSV 格式
        char *token;
        int field = 0;
        char *line_ptr = line;
        
        while ((token = strtok_r(line_ptr, ",", &line_ptr)) != NULL && field < 6)
        {
            // 去除字段可能包含的引号
            if (token[0] == '"' && token[strlen(token) - 1] == '"')
            {
                token[strlen(token)-1] = '\0';
                token++;
            }
            
            switch(field)
            {
                case 0: temp.record_id = atoi(token); break;
                case 1: temp.device_id = atoi(token); break;
                case 2: strcpy(temp.status, token); break;
                case 3: sscanf(token, "%d-%d-%d", 
                           &temp.borrow_date.year,
                           &temp.borrow_date.month,
                           &temp.borrow_date.day); 
                        break;
                case 4: sscanf(token, "%d-%d-%d", 
                           &temp.return_date.year,
                           &temp.return_date.month,
                           &temp.return_date.day); 
                        break;
                case 5: sscanf(token, "%d-%d-%d", 
                           &temp.actual_return_date.year,
                           &temp.actual_return_date.month,
                           &temp.actual_return_date.day);
                        break;
            }
            field++;
        }
        
        if (field == 6)
        {
            borrow[*borrow_count] = temp;
            (*borrow_count)++;
            count++;
            printf("成功读取设备: 编号 : %d\n", temp.device_id);
        }
    }
    
    fclose(file);
    if (count == 0) {
        printf("没有找到借用信息。\n");
    } else {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("总共找到 %d 个借用信息。\n", count);
    }
}
// 结束

// 统计报表模块
void deviceCategoryStats(Device device[], int *device_count)
{
    if (*device_count == 0)
    {
        printf("请先至少添加一个设备信息!\n\n");
        return;
    }

    char unique_types[MAX_DEVICES][30];     // 存储唯一的设备类型
    int type_counts[MAX_DEVICES] = {0};     // 存储每种类型的数量
    int unique_count = 0;                   // 不同设备类型的数量

    for (int i = 0; i < *device_count; i++)
    {
        int found = FALSE;
        for (int j = 0; j < unique_count; j++)
        {
            // 如果找到已有的类型, 让对应类型的数量加1
            if (strcmp(unique_types[j], device[i].type) == 0)
            {
                type_counts[j]++;
                found = TRUE;
                break; // 找到匹配的加完数量就退出
            }
        }

        // 新类型处理
        if (!found)
        {
            strcpy(unique_types[unique_count], device[i].type);
            type_counts[unique_count] = 1;  // 新类型数量默认为1
            unique_count++;                 // 增加类型数量
        }
    }

    printf("\n设备分类统计结果: \n");
    printf("————————————————————————————————————————————\n");
    printf("%-20s %-10s %10s\n", "设备类型", "数量", "百分比");
    printf("————————————————————————————————————————————\n");
    for (int i = 0; i < unique_count; i++)
    {
        double percentage = (double)type_counts[i] / *device_count * 100;
        printf("%-20s %-10d %9.2lf%%\n"
            , unique_types[i], type_counts[i], percentage);
    }
    printf("————————————————————————————————————————————\n");
    printf("设备总数: %d\n\n", *device_count);
}

void deviceStatusStats(Device device[], int *device_count)
{
    if (*device_count == 0)
    {
        printf("请先至少添加一个设备信息!\n\n");
        return;
    }

    char unique_status[MAX_DEVICES][30];     // 存储唯一的设备状态
    int status_counts[MAX_DEVICES] = {0};     // 存储每种状态的数量
    int unique_count = 0;                   // 唯一状态的数量

    for (int i = 0; i < *device_count; i++)
    {
        int found = FALSE;
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(unique_status[j], device[i].status) == 0)
            {
                status_counts[j]++;
                found = TRUE;
                break;
            }
        }

        if (!found)
        {
            strcpy(unique_status[unique_count], device[i].status);
            status_counts[unique_count] = 1;
            unique_count++;
        }
    }

    printf("\n设备状态分类统计结果: \n");
    printf("————————————————————————————————————————————\n");
    printf("%-20s %-10s %10s\n", "设备状态", "数量", "百分比");
    printf("————————————————————————————————————————————\n");
    for (int i = 0; i < unique_count; i++)
    {
        double percentage = (double)status_counts[i] / *device_count * 100;
        printf("%-20s %-10d %9.2lf%%\n"
            , unique_status[i], status_counts[i], percentage);
    }
    printf("————————————————————————————————————————————\n");
    printf("设备总数: %d\n\n", *device_count);
}

void deviceBorrowStats(Borrow borrow[], int *borrow_count, Device *device, int *device_count)
{
    if (*device_count == 0)
    {
        printf("请先至少添加一个设备信息!\n\n");
        return;
    }

    if (*borrow_count == 0)
    {
        printf("请先至少添加一个借用信息!\n");
        return;
    }

    char borrow_unique_status[MAX_DEVICES][30];     // 存储唯一的设备类型
    int borrow_type_counts[MAX_DEVICES] = {0};     // 存储每种类型的数量
    int borrow_unique_count = 0;                   // 唯一类型的数量

    for (int q = 0; q < *device_count; q++)
    {
        int found = FALSE;
        for (int m = 0; m < borrow_unique_count; m++)
        {
            if (strcmp(borrow_unique_status[m], borrow[q].status) == 0)
            {
                borrow_type_counts[m]++;
                found = TRUE;
                break;
            }
        }

        if (!found)
        {
            strcpy(borrow_unique_status[borrow_unique_count], borrow[q].status);
            borrow_type_counts[borrow_unique_count] = 1;
            borrow_unique_count++;
        }
    }

    printf("\n设备借用统计结果: \n");
    printf("————————————————————————————————————————————\n");
    printf("%-20s %-10s %10s\n", "借用类型", "数量", "百分比");
    printf("————————————————————————————————————————————\n");
    for (int q = 0; q< borrow_unique_count; q++)
    {
        double percentage1 = (double)borrow_type_counts[q] / *borrow_count * 100;
        printf("%-20s %-10d %9.2lf%%\n"
            , borrow_unique_status[q], borrow_type_counts[q], percentage1);
    }
    printf("————————————————————————————————————————————\n");
    printf("借用设备总数: %d\n", *borrow_count);
}

void generateReport(Device device[], int *device_count, Repair repair[], int *repair_count,
                    Borrow borrow[], int *borrow_count)
{
    if (*device_count == 0)
    {
        printf("没有设备信息可导出！\n\n");
        return;
    }

    int choice;

    do
    {
        showGenerateReportMenu();
        scanf("%d", &choice);
        cleanBuffer();

        switch (choice)
        {
        case 1:
        {
            FILE *file = fopen("device_report.csv", "w");
            if (file == NULL)
            {
                printf("无法创建报表文件!\n\n");
                return;
            }
            fprintf(file, "设备编号,设备名称,设备类型,设备品牌,设备型号,设备价格,设备状态,购买日期\n");

            for (int i = 0; i < *device_count; i++)
            {
                fprintf(file, "%d,\"%s\",\"%s\",\"%s\",\"%s\",%.2lf,\"%s\",%04d-%02d-%02d\n"
                    , device[i].id, device[i].name, device[i].type, device[i].brand
                    , device[i].model, device[i].price, device[i].status
                    , device[i].purchase_date.year, device[i].purchase_date.month, device[i].purchase_date.day);
            }

            fclose(file);
            printf("设备信息报表已成功导出到 device_report.csv 文件中!\n\n");
        }
        break;

        case 2:
        {
            FILE *file = fopen("repair_report.csv", "w");
            if (file == NULL)
            {
                printf("无法创建报表文件!\n\n");
                return;
            }
            fprintf(file, "维修编号,设备编号,故障描述,维修人员,维修费用,维修状态,维修日期\n");

            for (int i = 0; i < *repair_count; i++)
            {
                fprintf(file, "%d,%d,\"%s\",\"%s\",%.2lf,\"%s\",%04d-%02d-%02d\n"
                    , repair[i].repair_id, repair[i].device_id, repair[i].fault_desc
                    , repair[i].repair_person, repair[i].cost, repair[i].status
                    , repair[i].repair_date.year, repair[i].repair_date.month, repair[i].repair_date.day);
            }

            fclose(file);
            printf("设备信息报表已成功导出到 repair_report.csv 文件中!\n\n");
        }
        break;

        case 3:
        {
            FILE *file = fopen("borrow_report.csv", "w");
            if (file == NULL)
            {
                printf("无法创建报表文件!\n\n");
                return;
            }
            fprintf(file, "借用编号,设备编号,借用状态,借用日期,归还日期,实际归还日期\n");

            for (int i = 0; i < *borrow_count; i++)
            {
                fprintf(file, "%d,%d,\"%s\",%04d-%02d-%02d,%04d-%02d-%02d,%04d-%02d-%02d\n"
                    , borrow[i].record_id, borrow[i].device_id, borrow[i].status
                    , borrow[i].borrow_date.year, borrow[i].borrow_date.month, borrow[i].borrow_date.day
                    , borrow[i].return_date.year, borrow[i].return_date.month, borrow[i].return_date.day
                    , borrow[i].actual_return_date.year, borrow[i].actual_return_date.month, borrow[i].actual_return_date.day);
            }

            fclose(file);
            printf("设备信息报表已成功导出到 borrow_report.csv 文件中!\n\n");
        }
        break;

        case 0:
        break;

        default:
        {
            printf("输入错误，请重试!\n\n");
        }
        break;
        }
        
    }while (choice != 0);
}