
#ifndef __defs_h__
#define __defs_h__

#include "___h.h"

#define TYPE_IS_NUMBER(type) (type==TINT?1:0)

float filed_type_size[] = {
    [TINT   ] = 4,
    [TBCD   ] = 4.0/8,
    [TSTRING] = 1,
};

filed_attr CssHeaderInfo[] = {
	{ .type=TINT   , .padflg=0, .padsize=0, .size=_sizeof(TINT)   , .penname="MsgLen" , .pchname="消息长度"  , .premark="不包含长度本身域大小" } ,
	{ .type=TSTRING, .padflg=0, .padsize=0, .size=_sizeof(TSTRING), .penname="Sender" , .pchname="消息发送方", .premark=""            } ,
	{ .type=TBCD   , .padflg=0, .padsize=0, .size=_sizeof(TBCD)   , .penname="Time"   , .pchname="时间"      , .premark="当前时间"     } ,
	{ .type=TINT   , .padflg=0, .padsize=0, .size=1               , .penname="Ver"    , .pchname="消息版本"  , .premark="默认0"        } ,
	{ .type=TINT   , .padflg=0, .padsize=0, .size=_sizeof(TINT)   , .penname="MSN"    , .pchname="消息流水"  , .premark=""           } ,
	{ .type=TINT   , .padflg=0, .padsize=0, .size=_sizeof(TINT)   , .penname="TranSeq", .pchname="交易序号"  , .premark=""           } ,
	{ .type=TINT   , .padflg=0, .padsize=0, .size=_sizeof(TINT)   , .penname="CRC"    , .pchname=""          , .premark=""       } ,
};

filed_attr CssBodyInfo[] = {
	{ .type=TINT   , .padflg=0, .padsize=0, .size=2               , .penname="MsgType", .pchname="消息类型"  , .premark="数据体中部分" },
};

filed_attr MsgTypeInfo[] = {
	{ .type=TINT   , .padflg=0, .padsize=0, .size=2               , .penname="MsgType", .pchname="消息类型"  , .premark="数据体中部分" },
};

filed_attr MSG0102Info[] = {
	{ .type=TSTRING, .padflg=0, .padsize=0, .size=_sizeof(TSTRING), .penname="DevID"  , .pchname="设备编号"  , .premark="" },
	{ .type=TSTRING, .padflg=0, .padsize=0, .size=_sizeof(TSTRING), .penname="OperID" , .pchname="操作员编号", .premark="" },
	{ .type=TINT   , .padflg=0, .padsize=0, .size=1               , .penname="LoginType", .pchname="登录类型", .premark="0:登录 1:登出" },
};

filed_attr MSG0604Info[] = {
	{ .type=TINT, .padflg=0, .padsize=0, .size=2, .penname="StatusType"  , .pchname="状态上报类型"  , .premark="00:全状态 01:变更状态" },
	{ .type=TINT, .padflg=0, .padsize=0, .size=2, .loopflg=1, .penname="StatusInfo_Cnt" , .pchname="StatusInfo_Cnt", .premark="" },
	{ .type=TSTRING   , .padflg=0, .padsize=0, .size=1               , .penname="StatusID", .pchname="状态类型", .premark="" },
	{ .type=TSTRING   , .padflg=0, .padsize=0, .size=1               , .penname="StatusValue", .pchname="状态值", .premark="" },
};

/*
MSG0102 {
	@CssHeaderInfo
	@MsgTypeInfo
	@MSG0102Info
	@MD5
}
*/

#endif
