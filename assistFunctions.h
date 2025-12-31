#ifndef ASSISTFUNCTIONS_H
#define ASSISTFUNCTIONS_H

#include "data.h"

void cleanBuffer(void);
int checkDeviceAvailable(int device_count);
int confirmEdit(void);
int confirmDelete(void);
int confirmReadInfo(void);
int confirmBatchAdd(void);

int isLeapYear(int year);
/* int isFebruary(Date date); */
int isDateValid(Date date);
int compareDate(Date return_date, Date actual_date);
int dateToDays(Date date);
int calculateOverdueDays(Date return_date, Date actual_date);
int overdueReminder(Date return_date, Date actual_date);
Date calcuReturnDate(Date borrow_date);

char* getDeviceName(Device device[], int device_id, int device_count);

#endif