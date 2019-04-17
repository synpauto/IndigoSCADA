/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "MMS"
 * 	found in "../mms-extended.asn"
 * 	`asn1c -fskeletons-copy`
 */

#ifndef	_ServiceSupportOptions_H_
#define	_ServiceSupportOptions_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ServiceSupportOptions {
	ServiceSupportOptions_status	= 0,
	ServiceSupportOptions_getNameList	= 1,
	ServiceSupportOptions_identify	= 2,
	ServiceSupportOptions_rename	= 3,
	ServiceSupportOptions_read	= 4,
	ServiceSupportOptions_write	= 5,
	ServiceSupportOptions_getVariableAccessAttributes	= 6,
	ServiceSupportOptions_defineNamedVariable	= 7,
	ServiceSupportOptions_defineScatteredAccess	= 8,
	ServiceSupportOptions_getScatteredAccessAttributes	= 9,
	ServiceSupportOptions_deleteVariableAccess	= 10,
	ServiceSupportOptions_defineNamedVariableList	= 11,
	ServiceSupportOptions_getNamedVariableListAttributes	= 12,
	ServiceSupportOptions_deleteNamedVariableList	= 13,
	ServiceSupportOptions_defineNamedType	= 14,
	ServiceSupportOptions_getNamedTypeAttributes	= 15,
	ServiceSupportOptions_deleteNamedType	= 16,
	ServiceSupportOptions_input	= 17,
	ServiceSupportOptions_output	= 18,
	ServiceSupportOptions_takeControl	= 19,
	ServiceSupportOptions_relinquishControl	= 20,
	ServiceSupportOptions_defineSemaphore	= 21,
	ServiceSupportOptions_deleteSemaphore	= 22,
	ServiceSupportOptions_reportSemaphoreStatus	= 23,
	ServiceSupportOptions_reportPoolSemaphoreStatus	= 24,
	ServiceSupportOptions_reportSemaphoreEntryStatus	= 25,
	ServiceSupportOptions_initiateDownloadSequence	= 26,
	ServiceSupportOptions_downloadSegment	= 27,
	ServiceSupportOptions_terminateDownloadSequence	= 28,
	ServiceSupportOptions_initiateUploadSequence	= 29,
	ServiceSupportOptions_uploadSegment	= 30,
	ServiceSupportOptions_terminateUploadSequence	= 31,
	ServiceSupportOptions_requestDomainDownload	= 32,
	ServiceSupportOptions_requestDomainUpload	= 33,
	ServiceSupportOptions_loadDomainContent	= 34,
	ServiceSupportOptions_storeDomainContent	= 35,
	ServiceSupportOptions_deleteDomain	= 36,
	ServiceSupportOptions_getDomainAttributes	= 37,
	ServiceSupportOptions_createProgramInvocation	= 38,
	ServiceSupportOptions_deleteProgramInvocation	= 39,
	ServiceSupportOptions_start	= 40,
	ServiceSupportOptions_stop	= 41,
	ServiceSupportOptions_resume	= 42,
	ServiceSupportOptions_reset	= 43,
	ServiceSupportOptions_kill	= 44,
	ServiceSupportOptions_getProgramInvocationAttributes	= 45,
	ServiceSupportOptions_obtainFile	= 46,
	ServiceSupportOptions_defineEventCondition	= 47,
	ServiceSupportOptions_deleteEventCondition	= 48,
	ServiceSupportOptions_getEventConditionAttributes	= 49,
	ServiceSupportOptions_reportEventConditionStatus	= 50,
	ServiceSupportOptions_alterEventConditionMonitoring	= 51,
	ServiceSupportOptions_triggerEvent	= 52,
	ServiceSupportOptions_defineEventAction	= 53,
	ServiceSupportOptions_deleteEventAction	= 54,
	ServiceSupportOptions_getEventActionAttributes	= 55,
	ServiceSupportOptions_reportEventActionStatus	= 56,
	ServiceSupportOptions_defineEventEnrollment	= 57,
	ServiceSupportOptions_deleteEventEnrollment	= 58,
	ServiceSupportOptions_alterEventEnrollment	= 59,
	ServiceSupportOptions_reportEventEnrollmentStatus	= 60,
	ServiceSupportOptions_getEventEnrollmentAttributes	= 61,
	ServiceSupportOptions_acknowledgeEventNotification	= 62,
	ServiceSupportOptions_getAlarmSummary	= 63,
	ServiceSupportOptions_getAlarmEnrollmentSummary	= 64,
	ServiceSupportOptions_readJournal	= 65,
	ServiceSupportOptions_writeJournal	= 66,
	ServiceSupportOptions_initializeJournal	= 67,
	ServiceSupportOptions_reportJournalStatus	= 68,
	ServiceSupportOptions_createJournal	= 69,
	ServiceSupportOptions_deleteJournal	= 70,
	ServiceSupportOptions_getCapabilityList	= 71,
	ServiceSupportOptions_fileOpen	= 72,
	ServiceSupportOptions_fileRead	= 73,
	ServiceSupportOptions_fileClose	= 74,
	ServiceSupportOptions_fileRename	= 75,
	ServiceSupportOptions_fileDelete	= 76,
	ServiceSupportOptions_fileDirectory	= 77,
	ServiceSupportOptions_unsolicitedStatus	= 78,
	ServiceSupportOptions_informationReport	= 79,
	ServiceSupportOptions_eventNotification	= 80,
	ServiceSupportOptions_attachToEventCondition	= 81,
	ServiceSupportOptions_attachToSemaphore	= 82,
	ServiceSupportOptions_conclude	= 83,
	ServiceSupportOptions_cancel	= 84
} e_ServiceSupportOptions;

/* ServiceSupportOptions */
typedef BIT_STRING_t	 ServiceSupportOptions_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ServiceSupportOptions;
asn_struct_free_f ServiceSupportOptions_free;
asn_struct_print_f ServiceSupportOptions_print;
asn_constr_check_f ServiceSupportOptions_constraint;
ber_type_decoder_f ServiceSupportOptions_decode_ber;
der_type_encoder_f ServiceSupportOptions_encode_der;
xer_type_decoder_f ServiceSupportOptions_decode_xer;
xer_type_encoder_f ServiceSupportOptions_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _ServiceSupportOptions_H_ */
