#include <stdio.h>
#include "data.h"

// 清除缓冲区
void cleanBuffer(void)
{
    int c;
    do{
        c = getchar();
    }while(c != '\n');
}

// 检查设备数量
int checkDeviceAvailable(int device_count)
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

// 闰年检查
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 二月检查,暂时无用
/* 
int isFebruary(Date date)
{
    if (date.month != 2) 
    {
        return TRUE;  
    }
    
    if (date.day < 1) 
    {
        printf("日期不能小于1天,请重新输入!\n\n");
        return FALSE;
    }
    
    if (isLeapYear(date.year))
    {
        if (date.day > 29) {
            printf("闰年2月不能大于29天,请重新输入!\n\n");
            return FALSE;
        }
    } 
    else {
        if (date.day > 28) {
            printf("2月天数不能大于28天,请重新输入!\n\n");
            return FALSE;
        }
    }
    
    return TRUE;
}
    
*/

// 日期检查
int isDateValid(Date date)
{
    // 年份检查
    if (date.year < 2000 || date.year > 2100) 
    {
        printf("年份输入错误,请重试!\n\n");
        return FALSE;
    }

    // 月份检查
    if (date.month < 1 || date.month > 12) 
    {
        printf("月份输入错误,请重试!\n\n");
        return FALSE;
    }

    // 日期最小值检查
    if (date.day < 1) 
    {
        printf("日期不能小于1天,请重新输入!\n\n");
        return FALSE;
    }

    // 每月最大天数数组
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // 闰年调整2月天数
    if (isLeapYear(date.year))
    {
        days_in_month[1] = 29;
    }

    // 检查日期是否超过当月最大天数
    if (date.day > days_in_month[date.month - 1]) 
    {
        printf("天数输入错误,请重试!\n\n");
        return FALSE;
    }

    return TRUE;
}

int compareDate(Date return_date, Date actual_date)
{
    // -1: (date1 < date2), 0: (相等), 1: (date1 > date2)
    if (return_date.year != actual_date.year)
    {
        return (return_date.year < actual_date.year) ? -1 : 1;
    }

    if (return_date.month != actual_date.month)
    {
        return (return_date.month < actual_date.month) ? -1 : 1;
    }

    if (return_date.day != actual_date.day)
    {
        return (return_date.day < actual_date.day) ? -1 : 1;
    }

    return 0;
}

// 逾期提醒
int overdueReminder(Date return_date, Date actual_date)
{
    if (return_date.year == actual_date.year && return_date.month == actual_date.month)
    {
        if (return_date.day > actual_date.day)
        {
            int reminder = return_date.day - actual_date.day;
            return reminder;
        }
    }

    return 0;
}

int isOverdue(Date return_date, Date actual_date)
{
    int days_between = 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int days1 = return_date.year * 365 + return_date.month * days_in_month[return_date.month - 1] 
                + days_in_month[return_date.month - 1];
    int days2 = actual_date.year * 365 + actual_date.month * days_in_month[actual_date.month - 1]
                + days_in_month[actual_date.month - 1];
    
    days_between = days2 - days1;

    return days_between;
}

Date calcuReturnDate(Date borrow_date)
{
    Date return_date = borrow_date;

    // 非闰年
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    // 闰年2月有29天
    if (isLeapYear(return_date.year))
    {
        days_in_month[1] = 29;
    }

    // 限制30天
    return_date.day += 30;

    while (return_date.day > days_in_month[return_date.month - 1])
    {
        return_date.day -= days_in_month[return_date.month - 1];
        return_date.month++;

        if (return_date.month > 12)
        {
            return_date.month = 1;
            return_date.year++;

            if (isLeapYear(return_date.year)){
                days_in_month[1] = 29;
            }
            else{
                days_in_month[1] = 28;
            }
        }

    }
    return return_date;
}

char* getDeviceName(Device device[], int device_id, int device_count)
{
    for (int i = 0; i < device_count; i++)
    {
        if (device[i].id == device_id)
        {
            return device[i].name;
        }
    }

    return "未知设备";
}