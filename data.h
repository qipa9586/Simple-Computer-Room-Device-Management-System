#ifndef DATA_H
#define DATA_H

#define MAX_DEVICES 100
#define TRUE 1
#define FALSE 0

// 日期的结构体
typedef struct
{
    int year;
    int month;
    int day;
}Date;


// 设备信息与状态的结构体
typedef struct
{
    int id;                 // 设备编号
    char name[50];          // 设备名称
    char type[30];          // 设备类型（台式机，笔记本，CPU，内存等）
    char brand[30];         // 品牌
    char model[30];         // 型号
    Date purchase_date;     // 购买日期
    double price;           // 价格
    char status[20];        // 状态（正常、故障、停用、维修中、报废）
} Device;

// 设备维修的结构体
typedef struct {
    int repair_id;          // 维修记录编号
    int equipment_id;       // 设备编号
    char fault_desc[100];   // 故障描述
    Date repair_date;       // 维修日期
    char repair_person[50]; // 维修人员
    double cost;            // 维修费用
} Repair;

// 设备借用的结构体
typedef struct
{
    int record_id;                 // 记录编号
    int equipment_id;              // 设备编号
    char borrow_date[20];          // 借用日期
    Date return_date;              // 应归还日期
    Date actual_return_date[20];   // 实际归还日期
    char status[20];               // 状态（借用中、已归还、逾期）
}Borrow;

// 声明全局变量（使用extern）
extern int device_count;
extern int repair_count;
extern Device device[MAX_DEVICES];
extern Repair repair[MAX_DEVICES];
extern Borrow borrow[MAX_DEVICES];

#endif
