#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "data.h"

/* 设备信息管理函数声明 */
void addNewDevice(Device device[], int *device_count);              // 添加设备信息
void editDeviceInfo(Device device[], int *device_count);            // 编辑设备信息
void deleteDeviceInfo(Device device[], int *device_count);          // 删除设备信息
void searchDeviceInfo(Device device[], int *device_count);          // 查询设备信息
void displayAllDeviceInfo(Device device[], int *device_count);      // 显示所有设备信息
void readDeviceInfo(Device device[], int *device_count);            // 读取设备信息

/* 设备状态管理函数声明 */
void updateStatus(Device device[], int *device_count);
void addRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);
void searchRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);
void readRepairInfo(Repair repair[], int *repair_count, Device device[], int *device_count);

/* 设备借用管理函数声明 */
void borrowDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count);
void returnDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count);
void searchBorrowRecord(Device device[], int *device_count, Borrow borrow[], int *borrow_count);
void readBorrowInfo(Borrow borrow[], int *borrow_count, Device device[], int *device_count);

/* 统计报表模块函数声明 */
void deviceCategoryStats(Device device[], int *device_count);
void deviceStatusStats(Device device[], int *device_count);
void deviceBorrowStats(Borrow borrow[], int *borrow_count, Device *device, int *device_count);
void generateReport(Device device[], int *device_count, Repair repair[], int *repair_count,
                    Borrow borrow[], int *borrow_count);


#endif