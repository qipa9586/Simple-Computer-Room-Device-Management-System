#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "data.h"

/* 设备信息管理函数声明 */
void addNewDevice(Device device[], int *device_count);
void editDeviceInfo(Device device[], int *device_count);
void deleteDeviceInfo(Device device[], int *device_count);
void searchDeviceInfo(Device device[], int *device_count);
void displayAllDeviceInfo(Device device[], int *device_count);


/* 设备状态管理函数声明 */
void updateStatus(Device device[], int *device_count);
void addRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);
void searchRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);

/* 设备借用管理函数声明 */
void borrowDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count);
void returnDevice(Device device[], int *device_count, Borrow borrow[], int *borrow_count);
void searchBorrowRecord(Device device[], int *device_count, Borrow borrow[], int *borrow_count);


#endif