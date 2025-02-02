
#ifndef __nt_eInfo_h__
#define __nt_eInfo_h__

#define APP_ACTION_AIHOME      0x01
#define APP_ACTION_AICLOUD     0x02
#define APP_ACTION_AIEXTEND    0x04
#define APP_ACTION_AIPLAYER    0x08

#define APP_SID_AIHOME         "1001"
#define APP_SID_AICLOUD        "1001.01"
#define APP_SID_AIEXTEND       "1001.02"
#define APP_SID_AIPLAYER       "1001.03"
#define MAX_APPS_NUM           4

#define ACT(var) APP_ACTION_##var
#define SID(var) APP_SID_##var

/* NOTIFY CENTER EVENT MAPPING INFO STRUCTURE
---------------------------------*/
struct eInfo {
	char    *eName;
	int      value;
	int      eType;
	int      appsid;
	int      action;
};
enum {
	TYPE_OF_RSV=0,
	TYPE_OF_TURN_OFF,
	TYPE_OF_IMPORTANT,
	TYPE_OF_TIPS,
	TYPE_OF_TOTAL
};


struct app {
	char    *sid;
	int      appx;
};

struct app appInfo[] =
{
	{SID(AIHOME)    ,ACT(AIHOME)   },
	{SID(AICLOUD)   ,ACT(AICLOUD)  },
	{SID(AIEXTEND)  ,ACT(AIEXTEND) },
	{SID(AIPLAYER)  ,ACT(AIPLAYER) },
	{0,0}
};

struct eInfo mapInfo[] =
{
	/* RESERVATION EVENT */
	{"RESERVATION_MAIL_REPORT_EVENT"             ,RESERVATION_MAIL_REPORT_EVENT               ,TYPE_OF_RSV        ,-1             ,ACTION_NOTIFY_RSV },
	{"RESERVATION_MAIL_CONFIRM_EVENT"            ,RESERVATION_MAIL_CONFIRM_EVENT              ,TYPE_OF_RSV        ,-1             ,ACTION_NOTIFY_RSV },
	/* ------------------------------
	   ### System ###
	---------------------------------*/
	/* WAN EVENT */
	{"SYS_WAN_DISCONN_EVENT"                     ,SYS_WAN_DISCONN_EVENT                       ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_BLOCK_EVENT"                       ,SYS_WAN_BLOCK_EVENT                         ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_CABLE_UNPLUGGED_EVENT"             ,SYS_WAN_CABLE_UNPLUGGED_EVENT               ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_PPPOE_AUTH_FAILURE_EVENT"          ,SYS_WAN_PPPOE_AUTH_FAILURE_EVENT            ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_USB_MODEM_UNREADY_EVENT"           ,SYS_WAN_USB_MODEM_UNREADY_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_IP_CONFLICT_EVENT"                 ,SYS_WAN_IP_CONFLICT_EVENT                   ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_UNABLE_CONNECT_PARENT_AP_EVENT"    ,SYS_WAN_UNABLE_CONNECT_PARENT_AP_EVENT      ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_MODEM_OFFLINE_EVENT"               ,SYS_WAN_MODEM_OFFLINE_EVENT                 ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_GOT_PROBLEMS_FROM_ISP_EVENT"       ,SYS_WAN_GOT_PROBLEMS_FROM_ISP_EVENT         ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_WAN_UNPUBLIC_IP_EVENT"                 ,SYS_WAN_UNPUBLIC_IP_EVENT                   ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* PASSWORD EVENT */
	{"SYS_PASSWORD_SAME_WITH_LOGIN_WIFI_EVENT"   ,SYS_PASSWORD_SAME_WITH_LOGIN_WIFI_EVENT     ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_PASSWORD_WIFI_WEAK_EVENT"              ,SYS_PASSWORD_WIFI_WEAK_EVENT                ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_PASSWORD_LOGIN_STRENGTH_CHECK_EVENT"   ,SYS_PASSWORD_LOGIN_STRENGTH_CHECK_EVENT     ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* GUEST NETWORK EVENT */
	{"SYS_GUESTWIFI_ONE_ENABLE_EVENT"            ,SYS_GUESTWIFI_ONE_ENABLE_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_GUESTWIFI_MORE_ENABLE_EVENT"           ,SYS_GUESTWIFI_MORE_ENABLE_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* RSSI EVENT */
	{"SYS_RSSI_LOW_SIGNAL_EVENT"                 ,SYS_RSSI_LOW_SIGNAL_EVENT                   ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_RSSI_LOW_SIGNAL_AGAIN_EVENT"           ,SYS_RSSI_LOW_SIGNAL_AGAIN_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* DUALWAN EVENT */
	{"SYS_DUALWAN_FAILOVER_EVENT"                ,SYS_DUALWAN_FAILOVER_EVENT                  ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"SYS_DUALWAN_FAILBACK_EVENT"                ,SYS_DUALWAN_FAILBACK_EVENT                  ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	/* SYS DETECT EVENT */
	{"SYS_SCAN_DLNA_PLAYER_EVENT"                ,SYS_SCAN_DLNA_PLAYER_EVENT                  ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_DETECT_ASUS_SSID_UNENCRYPT_EVENT"      ,SYS_DETECT_ASUS_SSID_UNENCRYPT_EVENT        ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_ECO_MODE_EVENT"                        ,SYS_ECO_MODE_EVENT                          ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_GAME_MODE_EVENT"                       ,SYS_GAME_MODE_EVENT                         ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_NEW_DEVICE_WIFI_CONNECTED_EVENT"       ,SYS_NEW_DEVICE_WIFI_CONNECTED_EVENT         ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_IFTTT },
	{"SYS_WIFI_DEVICE_DISCONNECTED_EVENT"        ,SYS_WIFI_DEVICE_DISCONNECTED_EVENT          ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"SYS_EXISTED_DEVICE_WIFI_CONNECTED_EVENT"   ,SYS_EXISTED_DEVICE_WIFI_CONNECTED_EVENT     ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* FIRMWARE EVENT */
	{"SYS_FW_NWE_VERSION_AVAILABLE_EVENT"        ,SYS_FW_NWE_VERSION_AVAILABLE_EVENT          ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"SYS_NEW_SIGNATURE_UPDATED_EVENT"           ,SYS_NEW_SIGNATURE_UPDATED_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	/* ------------------------------
	   ### Administration ###
	---------------------------------*/
	/* LOGIN EVENT */
	{"ADMIN_LOGIN_FAIL_LAN_WEB_EVENT"            ,ADMIN_LOGIN_FAIL_LAN_WEB_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_FAIL_WAN_WEB_EVENT"            ,ADMIN_LOGIN_FAIL_WAN_WEB_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_FAIL_SSH_EVENT"                ,ADMIN_LOGIN_FAIL_SSH_EVENT                  ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_FAIL_TELNET_EVENT"             ,ADMIN_LOGIN_FAIL_TELNET_EVENT               ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_FAIL_SSID_EVENT"               ,ADMIN_LOGIN_FAIL_SSID_EVENT                 ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_DEVICE_DOUBLE_EVENT"           ,ADMIN_LOGIN_DEVICE_DOUBLE_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"ADMIN_LOGIN_ACCOUNT_DOBLE_EVENT"           ,ADMIN_LOGIN_ACCOUNT_DOBLE_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"ADMIN_LOGIN_FAIL_AICLOUD_EVENT"            ,ADMIN_LOGIN_FAIL_AICLOUD_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"ADMIN_LOGIN_FAIL_VPNSERVER_EVENT"          ,ADMIN_LOGIN_FAIL_VPNSERVER_EVENT            ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	/* ------------------------------
	   ### Security ###
	---------------------------------*/
	/* PROTECTION EVENT */
	{"PROTECTION_INTO_MONITORMODE_EVENT"         ,PROTECTION_INTO_MONITORMODE_EVENT           ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"PROTECTION_VULNERABILITY_EVENT"            ,PROTECTION_VULNERABILITY_EVENT              ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"PROTECTION_CC_EVENT"                       ,PROTECTION_CC_EVENT                         ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"PROTECTION_DOS_EVENT"                      ,PROTECTION_DOS_EVENT                        ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"PROTECTION_SAMBA_GUEST_ENABLE_EVENT"       ,PROTECTION_SAMBA_GUEST_ENABLE_EVENT         ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_FTP_GUEST_ENABLE_EVENT"         ,PROTECTION_FTP_GUEST_ENABLE_EVENT           ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_FIREWALL_DISABLE_EVENT"         ,PROTECTION_FIREWALL_DISABLE_EVENT           ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_MALICIOUS_SITE_EVENT"           ,PROTECTION_MALICIOUS_SITE_EVENT             ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"PROTECTION_WEB_CROSS_SITE_EVENT"           ,PROTECTION_WEB_CROSS_SITE_EVENT             ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_IIS_VULNERABILITY_EVENT"        ,PROTECTION_IIS_VULNERABILITY_EVENT          ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_DNS_AMPLIFICATION_ATTACK_EVENT" ,PROTECTION_DNS_AMPLIFICATION_ATTACK_EVENT   ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_SUSPICIOUS_HTML_TAG_EVNET"      ,PROTECTION_SUSPICIOUS_HTML_TAG_EVNET        ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_BITCOIN_MINING_ACTIVITY_EVENT"  ,PROTECTION_BITCOIN_MINING_ACTIVITY_EVENT    ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_MALWARE_RANSOM_THREAT_EVENT"    ,PROTECTION_MALWARE_RANSOM_THREAT_EVENT      ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PROTECTION_MALWARE_MIRAI_THREAT_EVENT"     ,PROTECTION_MALWARE_MIRAI_THREAT_EVENT       ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* ------------------------------
	   ### Parental Contorl ###
	---------------------------------*/
	/* PERMISSION REQUEST EVENT */
	{"PERMISSION_FROM_BLOCKPAGE_EVENT"           ,PERMISSION_FROM_BLOCKPAGE_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"PERMISSION_FROM_TIME_SCHEDULE_EVENT"       ,PERMISSION_FROM_TIME_SCHEDULE_EVENT         ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* ------------------------------
	   ### Traffic Management ###
	---------------------------------*/
	/* TRAFFIC METER EVENT */
	{"TRAFFICMETER_ALERT_EVENT"                  ,TRAFFICMETER_ALERT_EVENT                    ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"TRAFFICMETER_BW_LIMITER_EVENT"             ,TRAFFICMETER_BW_LIMITER_EVENT               ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"TRAFFIC_REDUCE_LAG_EVENT"                  ,TRAFFIC_REDUCE_LAG_EVENT                    ,TYPE_OF_IMPORTANT  ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* ------------------------------
	   ### USB Function ###
	---------------------------------*/
	/* USB EVENT */
	{"USB_DM_TASK_FINISHED_EVENT"                ,USB_DM_TASK_FINISHED_EVENT                  ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"USB_DISK_SCAN_FAIL_EVENT"                  ,USB_DISK_SCAN_FAIL_EVENT                    ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"USB_DISK_EJECTED_FAIL_EVENT"               ,USB_DISK_EJECTED_FAIL_EVENT                 ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"USB_DISK_PARTITION_FULL_EVENT"             ,USB_DISK_PARTITION_FULL_EVENT               ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	{"USB_DISK_FULL_EVENT"                       ,USB_DISK_FULL_EVENT                         ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP | ACTION_NOTIFY_EMAIL },
	/* ------------------------------
	   ### Hint Item ###
	---------------------------------*/
	/* HINT EVENT */
	{"HINT_USB_CHECK_EVENT"                      ,HINT_USB_CHECK_EVENT                        ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_USB_FIRSTIME_CHECK_EVENT"             ,HINT_USB_FIRSTIME_CHECK_EVENT               ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_SAMBA_INLAN_EVENT"                    ,HINT_SAMBA_INLAN_EVENT                      ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_OSX_INLAN_EVENT"                      ,HINT_OSX_INLAN_EVENT                        ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_DUALBAND_WITHOUT_5G_EVENT"            ,HINT_DUALBAND_WITHOUT_5G_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_USB3_WITHOUT_ENHANCE_EVENT"           ,HINT_USB3_WITHOUT_ENHANCE_EVENT             ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_XBOX_PS_EVENT"                        ,HINT_XBOX_PS_EVENT                          ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_UPNP_RENDERER_EVENT"                  ,HINT_UPNP_RENDERER_EVENT                    ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_DETECT_GAME_SERVICE_EVENT"            ,HINT_DETECT_GAME_SERVICE_EVENT              ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_SUGGEST_ENABLE_DFS_CHANNEL_EVENT"     ,HINT_SUGGEST_ENABLE_DFS_CHANNEL_EVENT       ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_SUGGEST_IE_BROWSER_VERSION_EVENT"     ,HINT_SUGGEST_IE_BROWSER_VERSION_EVENT       ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	{"HINT_INTERNET_USAGE_INSIGHT_EVENT"         ,HINT_INTERNET_USAGE_INSIGHT_EVENT           ,TYPE_OF_TIPS       ,ACT(AIHOME)    ,ACTION_MULTI_UIAPP },
	/* The End */
	{0,0,0,0,0}
};

#endif
