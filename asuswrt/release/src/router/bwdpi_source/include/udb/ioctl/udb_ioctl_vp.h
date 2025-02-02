/*
 * Copyright 2014 Trend Micro Incorporated
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software without 
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 */

#ifndef _UDB_IOCTL_VP_H_
#define _UDB_IOCTL_VP_H_

#include "udb/ioctl/udb_ioctl_common.h"

#define UDB_VIRTUAL_PATCH_LOG_SIZE 500

enum
{
	UDB_IOCTL_VP_OP_NA = 0,
	UDB_IOCTL_VP_OP_SET,
	UDB_IOCTL_VP_OP_GET_LOG,
	UDB_IOCTL_VP_OP_RESET_LOG,
	UDB_IOCTL_VP_OP_GET_LOG_RESET,
	UDB_IOCTL_VP_OP_GET_USER_LOG,
	UDB_IOCTL_VP_OP_GET_META,
	UDB_IOCTL_VP_OP_GET_USER_LOG_FIX_ROLE_DIR,
	UDB_IOCTL_VP_OP_MAX
};

#define GET_VP_DIR(p) \
({ \
	uint8_t d = 0; \
	if (!IS_CT_REPLY(p->ct_flag)) \
		d |= VP_DIR_C2S; \
	if (IS_SKB_UPLOAD(p->skb_flag)) \
		d |= VP_DIR_UL; \
	d; \
})

#define VP_ROLE_ATT	1
#define VP_ROLE_VIC	2

#define VP_DIR_UL	(1 << 0)
#define VP_DIR_C2S	(1 << 1)

typedef struct udb_vp_ioc_entry
{
	uint64_t btime; 	//!< Record event begin time, timestamp. Ex. get_second()
	uint32_t rule_id;

	uint32_t hit_cnt;	//!< event hit count
	uint8_t role; 		//!< 0 is unknown, 1 is attacker, 2 is victim
	uint8_t mac[6];

	uint8_t ip_ver;
	uint8_t proto;

	uint16_t sport;
	uint16_t dport;

	uint8_t dip[16];	//IP_ADDR_LEN
	uint8_t sip[16];	//IP_ADDR_LEN

	uint8_t action;		//!< the pkt action, 0 means accept, 1 means block
	uint8_t severity;
} udb_vp_ioc_entry_t;

typedef struct
{
	uint64_t btime; 	//!< Record event begin time, timestamp. Ex. get_second()
	uint32_t rule_id;

	uint32_t hit_cnt;	//!< event hit count
	uint8_t role;		//!< 0 is unknown, 1 is attacker, 2 is victim
	uint8_t dir; 		//!< 1st bit is upload/download, 2nd bit is c2s/s2c
	uint8_t mac[6];

	uint8_t ip_ver;
	uint8_t proto;

	uint16_t sport;
	uint16_t dport;

	uint8_t dip[16];	//IP_ADDR_LEN
	uint8_t sip[16];	//IP_ADDR_LEN

	uint8_t action;		//!< the pkt action, 0 means accept, 1 means block
	uint8_t severity;
} udb_vp_ioc_entry_fix_t;

typedef struct vp_ioc_mac
{
	uint8_t mac[6];
	uint16_t vp_cnt;

	uint8_t ipv4[4];
	uint8_t ipv6[16];

	udb_vp_ioc_entry_t entry[0];
} vp_ioc_mac_t;

typedef struct vp_ioc_list
{
	uint32_t mac_cnt;
	vp_ioc_mac_t mac_entry[0];
} vp_ioc_list_t;

#ifdef __KERNEL__
int udb_ioctl_vp_op_copy_out(uint8_t op, void *buf, uint32_t buf_len, uint32_t *buf_used_len);
int udb_ioctl_vp_op_copy_in(uint8_t op, void *buf, uint32_t buf_len);
int udb_ioctl_vp_op_copy_none(uint8_t op);
#endif

#endif /* _UDB_IOCTL_VP_H_ */

