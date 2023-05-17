/*
 * user_elog.c
 *
 *  Created on: 2023年5月6日
 *      Author: 好
 */

#define LOG_TAG    "user_elog"

#include "../easylogger/user_elog.h"
#include <elog.h>
#include "elog_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEBUG

static void elog_user_assert_hook(const char* ex, const char* func, size_t line);


//static void test_elog(void);

int easylogger_init(void){

    /* close printf buffer */
    setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    /* 断言：输出所有内容 */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
#ifdef DEBUG
    /* 错误：输出除了方法名之外的所有内容 */
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC |ELOG_FMT_P_INFO|ELOG_FMT_T_INFO));
    /* 警告：输出除了方法名之外的所有内容 */
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC |ELOG_FMT_P_INFO|ELOG_FMT_T_INFO));
#else
    /* 错误：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    /* 警告：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
#endif
    /* 信息：输出级别、标签和时间 */
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    /* 调试：输出除了方法名之外的所有内容 */
  //  elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL &  ~(ELOG_FMT_FUNC |ELOG_FMT_P_INFO|ELOG_FMT_T_INFO));
    /* 详细：输出除了方法名之外的所有内容 */
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);

    /* set EasyLogger assert hook */
    elog_assert_set_hook(elog_user_assert_hook);

#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();

    /* dynamic set enable or disable for output logs (true or false) */
//    elog_set_output_enabled(false);
    /* dynamic set output logs's level (from ELOG_LVL_ASSERT to ELOG_LVL_VERBOSE) */
//    elog_set_filter_lvl(ELOG_LVL_WARN);
    /* dynamic set output logs's filter for tag */
//    elog_set_filter_tag("main");
    /* dynamic set output logs's filter for keyword */
//    elog_set_filter_kw("Hello");
    /* dynamic set output logs's tag filter */
//    elog_set_filter_tag_lvl("main", ELOG_LVL_WARN);

    /* test logger output */
  //  test_elog();

    return EXIT_SUCCESS;
}


/* EasyLogger断言钩子方法 */
static void elog_user_assert_hook(const char* ex, const char* func, size_t line) {
    /* 失能异步输出方式（异步输出模块自带方法） */
    elog_async_enabled(false);
    /* 失能日志输出锁 */
    elog_output_lock_enabled(false);
    /* 输出断言信息 */
    elog_a("elog", "(%s) has assert failed at %s:%ld.\n", ex, func, line);
    while(1);
}


/**
 * EasyLogger demo
 */
//static void test_elog(void) {
//
//	/* test log output for all level */
////	log_a("Hello EasyLogger!");
////	log_e("Hello EasyLogger!");
////	log_w("Hello EasyLogger!");
////	log_i("Hello EasyLogger!");
////	log_d("Hello EasyLogger!");
////	log_v("Hello EasyLogger!");
//	/* 原格式输出*/
////	elog_raw("Hello EasyLogger!");
//	/*十六进制格式输出*/
////  elog_hexdump("test", 16, buf, sizeof(buf));
//	int i = 0 ;
//	while(i<40){
//		elog_file_init();
//		char *log = "For college students , when graduation season comes.";
//		char str[700];
//		sprintf(str,"%d%s",i,log);
//		elog_file_write(str,strlen(str));
//		i++;
//		sleep(3);
//	}
//	elog_file_deinit();
//}


