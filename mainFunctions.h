#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "data.h"

void updateStatus(Device device[], int device_count);
void addRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);
void searchRepairRecord(Device device[], int *device_count, Repair repair[], int *repair_count);
void borrowDevice(Device device[], int *device_count, Repair repair[], int *repair_count);
void returnDevice(Device device[], int *device_count, Repair repair[], int *repair_count);
void searchBorrowRecord(Device device[], int *device_count, Borrow borrow[], int *borrow_count);


#endif