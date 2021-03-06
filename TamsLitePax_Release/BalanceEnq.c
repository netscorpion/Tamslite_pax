#include <posapi.h>
#include <posapi_all.h>
#include "TamsLite.h"
#include "PostRequest.h"
#include  "BalanceEnq.h"
#include  "Md5.h"
#include "EftUtil.h"

int BalanceEnq(EftTransaction * MyEftTransaction)
{
	int length  = -1;
	char  Xml[1024]  = {0};
	char  RequestData[70000] = {0};
	char  AuthenticationData[200] = {0};
	char  PurchaseData[50000] = {0};
	char *Pdata[1] = {0};
	char TransactionType[10] = {0};
	char BatchNo[10] = {0};
	char SequenceNo[10] = {0};
	char MerchantId[10] = {0};
	char TransactionDate[10] = {0};
	char TrackTwo[102] = {0};
	char Cvv[10] = {0};
	char Operator[10] = {0};
	char Supervisor[10] = {0};
	char Amount[10] = {0};
	char CashBack[10] = {0};
	char Tip[10] = {0};
	char Budget[10] = {0};
	char AccountType[10] = {0};
	char PinBlock[50] = {0};
	char KSN[50] = {0};
	char Offline[5] = {0};
	char Manual[5] = {0};
	char OriginalSequeneNo[10] = {0};
	char RSVD[2] = "";
	char RefrenceCode[10] = {0};
	char OriginalTerminalID[16] = {0};
	char ReversalDateAndTime[10] = {0};
	char ReversalTransactionType[10] = {0};
	char ReversalReferenceCode[10] = {0};
	char CurrencyCode[5] = {0};
	char ProcessorFee[10] = {0};
	char AcquiringFee[10] = {0};
	char AdditionalData[20] ={0};
	char ICCData[10240] = {0};
	char AuthId[10] = {0};
	BatchInformation LocalBatchInfo;
	sprintf(TransactionType,"%d",MyEftTransaction->TransType);
	sprintf(BatchNo,"%d",MyEftTransaction->BatchNo);
	sprintf(SequenceNo,"%d",MyEftTransaction->SequenceNo);
	sprintf(MerchantId,"%d",MyEftTransaction->MerchantId);
	sprintf(TransactionDate,"%s",MyEftTransaction->TransacDateAndTime);
	sprintf(TrackTwo,"%s",MyEftTransaction->Track2);
	sprintf(Cvv,"%s",MyEftTransaction->CVV);
	sprintf(Operator,"%d",MyEftTransaction->OperatorId);
	sprintf(Supervisor,"%s",MyEftTransaction->SupervisorFlag==0?"N":"Y" );
	sprintf(Amount,"%d",MyEftTransaction->PurchaseAmount);
	sprintf(CashBack,"%d",MyEftTransaction->CashBackAmount);
	sprintf(Tip,"%d",MyEftTransaction->TipAmount);
	sprintf(Budget,"%d",MyEftTransaction->BudgetPeriod);
	sprintf(AccountType,"%d|%d",MyEftTransaction->AcctType,0);
	if(strlen(MyEftTransaction->PinBlock) > 0)
	{
	sprintf(PinBlock,"%s",MyEftTransaction->PinBlock);
	}else
	{
		sprintf(PinBlock,"%s","OFFLINE");
	}
	sprintf(KSN,"%s",MyEftTransaction->PinSerial);
	sprintf(Offline,"%s",MyEftTransaction->Offline==0?"N":"Y" );
	sprintf(Manual,"%s",MyEftTransaction->ManualFlag==0?"N":"Y" );
	sprintf(OriginalSequeneNo,"%s","");
	sprintf(RefrenceCode,"%s",MyEftTransaction->RefCode);
	sprintf(OriginalTerminalID,"%s","");
	sprintf(ReversalDateAndTime,"%s","");
	sprintf(ReversalTransactionType,"%s","");
	sprintf(ReversalReferenceCode,"%s","");
	sprintf(CurrencyCode,"%s","566");
	sprintf(ProcessorFee,"%s","");
	sprintf(AcquiringFee,"%s","");
	sprintf(AdditionalData,"%s","");
	sprintf(ICCData,"%s",MyEftTransaction->ICCData);
	sprintf(AuthId,"%s","");
	sprintf(PurchaseData,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		TransactionType,
		BatchNo,
		SequenceNo,
		MerchantId,
		TransactionDate,
		TrackTwo,
		Cvv,
		Operator,
		Supervisor,
		Amount,
		CashBack,
		Tip,
		Budget,
		AccountType,
		PinBlock,
		KSN,
		Offline,
		Manual,
		OriginalSequeneNo,
		RSVD,
		RefrenceCode,
		OriginalTerminalID,
		ReversalDateAndTime,
		ReversalTransactionType,
		ReversalReferenceCode,
		CurrencyCode,
		ProcessorFee,
		AcquiringFee,
		AdditionalData,
		RSVD,
		RSVD,
		RSVD,
		RSVD,
		ICCData,
		AuthId
		);
	 Pdata[0] = PurchaseData;
	 GetHash(Pdata,1,AuthenticationData);
	sprintf(RequestData,"T[]=%s",PurchaseData);
	EftSaveTransaction(MyEftTransaction);
	
	PostRequest("/tams/eftpos/devinterface/transaction.php",RequestData,AuthenticationData,Xml);
	length = strlen(Xml);
	if(length >0)
	{
		//Response Successfull
		return ProcessResponseEnq(Xml,MyEftTransaction);
	}else
	{
		return -1;
	}

}
static int ProcessResponseEnq(char *Xml,EftTransaction *MyEftTransaction)
{
	return 0;
}