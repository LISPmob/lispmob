/*
 * lmlog.c
 *
 * This file is part of LISP Mobile Node Implementation.
 * Write log messages
 * 
 * Copyright (C) 2011 Cisco Systems, Inc, 2011. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Please send any bug reports or fixes you make to the email address(es):
 *    LISP-MN developers <devel@lispmob.org>
 *
 * Written or modified by:
 *    David Meyer       <dmm@cisco.com>
 *    Preethi Natarajan <prenatar@cisco.com>
 *    Alberto Rodriguez Natal <arnatal@ac.ucp.edu>
 *
 */


#include <syslog.h>
#include <stdarg.h>
#include <stdio.h>
#include "lmlog.h"
#ifdef ANDROID
#include <android/log.h>
#endif

inline void lispd_log(int log_level, char *log_name, const char *format,
        va_list args);


void llog(int lisp_log_level, const char *format, ...)
{
    va_list args;
    char *log_name; /* To store the log level in string format for printf output */
    int log_level;

    va_start(args, format);

    switch (lisp_log_level){
    case LCRIT:
        log_name = "CRIT";
        log_level = LOG_CRIT;
        lispd_log(log_level, log_name, format, args);
        break;
    case LERR:
        log_name = "ERR";
        log_level = LOG_ERR;
        lispd_log(log_level, log_name, format, args);
        break;
    case LWRN:
        log_name = "WARNING";
        log_level = LOG_WARNING;
        lispd_log(log_level, log_name, format, args);
        break;
    case LINF:
        log_name = "INFO";
        log_level = LOG_INFO;
        lispd_log(log_level, log_name, format, args);
        break;
    case LDBG_1:
        if (debug_level > 0){
            log_name = "DEBUG";
            log_level = LOG_DEBUG;
            lispd_log(log_level, log_name, format, args);
        }
        break;
    case LDBG_2:
        if (debug_level > 1){
            log_name = "DEBUG-2";
            log_level = LOG_DEBUG;
            lispd_log(log_level, log_name, format, args);
        }
        break;
    case LDBG_3:
        if (debug_level > 2){
            log_name = "DEBUG-3";
            log_level = LOG_DEBUG;
            lispd_log(log_level, log_name, format, args);
        }
        break;
    default:
        log_name = "LOG";
        log_level = LOG_INFO;
        lispd_log(log_level, log_name, format, args);
        break;
    }

#ifdef ANDROID
    //if (lisp_log_level != LISP_LOG_DEBUG_3)
        __android_log_vprint(ANDROID_LOG_INFO, "LISPmob-C ==>", format,args);
#endif
    va_end (args);
}

inline void
lispd_log(int log_level, char *log_name, const char *format,
        va_list args)
{
    if (daemonize) {
        vsyslog(log_level, format, args);
    } else {
        printf("%s: ", log_name);
        vfprintf(stdout, format, args);
        printf("\n");
    }
}

/*
 * Editor modelines
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */