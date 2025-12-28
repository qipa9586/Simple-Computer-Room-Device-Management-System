#ifndef ASSISTFUNCTIONS_H
#define ASSISTFUNCTIONS_H

#include "data.h"

void cleanBuffer(void);
int checkDeviceAvailable(int device_count);
int isLeapYear(int year);
int isFebruary(Date date);
int isDateValid(Date date);
int compareDate(Date date1, Date date2);
int isOverdue(Date date1, Date date2);
int overdueReminder(Date return_date, Date actual_date);
Date calcuReturnDate(Date borrow_date);
char* getDeviceName(Device device[], int device_id, int device_count);

#endif