#ifndef __SMARTIOSSERVICE_DEFS_H__
#define __SMARTIOSSERVICE_DEFS_H__

#include "cutils/log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "smtios"

#define SMTLOGE(...) ALOGE(__VA_ARGS__)
#define SMTLOGD(...) ALOGD(__VA_ARGS__)
#define SMTASSERT(cond, ...) ALOG_ASSERT(cond, ## __VA_ARGS__)

#endif // __WFDSERVICE_DEFS_H__
