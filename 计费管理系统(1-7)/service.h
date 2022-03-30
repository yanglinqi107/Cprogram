#pragma once
#include "model.h"

int readCard(CardNode** ppCardNodeHead, char* pPath);

int saveCard(Card* pCard, char* pPath);

void releaseCard(CardNode* pCardNodeHead);

int readBilling(BillingNode** ppBillingHead, char* pPath);

int saveBilling(Billing* pBilling, char* pPath);

void releaseBilling(BillingNode* pBillingNodeHead);

Card* cardIsExist(char* strNo, long* pCardIndex, CardNode* const pCardNodeHead);

Billing* billingIsExist(char* strNo, long* pBillingIndex, BillingNode* const pBillingNodeHead);

int updateCard(const Card* pCard, char* pPath, long nCardIndex);

int updateBilling(const Billing* pBilling, char* pPath, int nBillingIndex);

int logon(char* strNo, char* strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead, BillingNode** ppBilllingNodeHead);

int settle(char* strNo, char* strPwd, SettleInfo* pInfo, CardNode* pCardNodeHead, BillingNode* const pBillingNodeHead);

double getAmount(time_t tStart);

int logon2(char* strNo, char* strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead, BillingNode** ppBilllingNodeHead);

int settle2(char* strNo, char* strPwd, SettleInfo* pInfo, CardNode* pCardNodeHead, BillingNode* const pBillingNodeHead);

int AddMoney(char* strNo, char* strPwd, float fmoney, MoneyInfo* pInfo, CardNode* pCardNodeHead);

int ReturnMoney(char* strNo, char* strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead);

int IsLegal(int year, int mon, int day);

int IsLeapYear(int year);

int Logout(char* strNo, char* strPwd, CardNode* pCardNodeHead);

void queryCard(char* strNo, CardNode* pCardNodeHead);