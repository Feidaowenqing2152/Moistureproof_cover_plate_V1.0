/*
 * hmi_common.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef HIMI_COMMON_HMI_COMMON_H_
#define HIMI_COMMON_HMI_COMMON_H_

#include "../common.h"
#include "../hardware/dev_buttons.h"


typedef int (*ShownMenuDate)(int);
typedef int (*ShowUserSetPar)(int);

typedef enum{
	cursor_default_mode = 0 ,  //光标默认初始化位置模式(每次初始化)
	cursor_refresh_mode   ,  //光标刷新模式（关闭上次光标，刷新这次新光标）

}type_cursor_show_mode;


struct dev_address_reset_par{
	bool setting_sleet_type_flag ;
	int setting_cursor_dev_var_addr ;
	int setting_dev_reset_page ;
	int auto_exit_setting_page_time ;
	int dev_addr_reset_wait_var_addr ;
	int dev_addr_reset_success_var_addr ;
	int dev_addr_reset_error_var_addr ;
    void (*dev_reset_execute_function_cb)(void);
};



typedef struct slect_move_cursor{
	uint8_t max_slect_move ;     //最大光标选择
	uint8_t min_slect_move ;     //最小光标选择
	uint8_t now_slect_move ;     //当前光标位置
	uint8_t move_slect_step ;    //光标步进数q
	int dw_cursor_adderss ;     //迪文光标地址
}type_slect_move_cursor;


typedef enum{
	return_to_main_menu_grade_1  = 1 ,
	return_to_main_menu_grade_2   ,
	return_to_main_menu_grade_3   ,
}Return_To_Main_Menu;

typedef enum{
	cursor_down = 0 ,
	cursor_up,
	cursor_null ,
}Cursor_Action;







void Return_Previous_Menu_Page_Load(void);
void Back_Main_Page_Load(void);

void Device_Addr_Reversion_Load_Init(struct dev_address_reset_par *type_dev_address_reset_par_t );
void Device_Addr_Reversion_Page_Load(void);
void Device_Addr_Reversion_Page_Exit(void);
void Device_Addr_Reversion_Page_Task(void);



void slect_cursor_move_init(type_slect_move_cursor *move_cursor_t );
void default_now_slect_cursor_move(type_slect_move_cursor *move_cursor_t);

void show_eth_connect_state(void);
void show_refresh_time(void);

uint8_t slect_cursor_move(type_cursor_show_mode restore_default_enable ,Cursor_Action cursor_action);
int user_parameter_adjustment(int parameter_adj_date ,bool enable_symbol, uint8_t digit_wide, uint8_t key_number ,ShowUserSetPar ShowUserSetPar_t);
void clearn_Temp_Compensation_Slcet_buttons_cnt(void);

int *ip_str_analysis_number(char *ip_setting_str);

#endif /* HIMI_COMMON_HMI_COMMON_H_ */
