/*
 * mqtt_masg_task.c
 *
 *  Created on: 2023年4月20日
 *      Author: 好
 */
#define LOG_TAG    "mqtt_masg_task"

#include "../task/mqtt_masg_task.h"
#include "../mqtt/mqtt_topic.h"
#include "../mqtt/mqtt_post.h"
#include "../mqtt/mqtt_get.h"
#include "../mqtt/mqtt_set.h"

//static struct Mqtt_Client_Date Mqtt_Client ;


Set_Mqtt_Client_System Set_Mqtt_Client_System_t={
		.mqtt_host_change_flag = 1 ,
		.mqtt_password_change_flag = 1 ,
		.mqtt_port_change_flag = 1 ,
		.mqtt_username_change_flag = 1 ,
};

extern uint8_t switch_mode;

pthread_mutex_t pthread_mutex_t_mqtt_t = PTHREAD_MUTEX_INITIALIZER;;


static bool mqtt_client_connect_success_flag = false;	//客户端连接状态


extern GetInformMqttMasgEven GetInformMqttMasgEven_t ;


/*物理网口状态回调*/
static void get_eth_connect_state_cb(struct mosquitto *mosq,uint8_t state);
/*连接成功回调*/
static void disconnect_callback(struct mosquitto *mosq, void *obj, int rc);
/*连接断开回调*/
static void connect_callback(struct mosquitto *mosq, void *obj, int rc);
/*获取到订阅的内容*/
static void mqtt_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);

/*处理订阅到的 get 内容*/
static void handle_propert_get_topic(struct mosquitto *mosq,const struct mosquitto_message *msg);
/*处理订阅到的 set 内容*/
static void handle_propert_set_topic(struct mosquitto *mosq,const struct mosquitto_message *msg);
/* set 触发回调函数*/
static int Set_Topic_Execute_Function_cb(int remote_control_switch,int remote_control_cmd,int remote_control_timer);

static void post_device_event_status( struct mosquitto *mosq ,struct Client_Id_Name  *Client_Id_Name_t );
static void post_device_message(struct mosquitto *mosq ,struct Client_Id_Name  *Client_Id_Name_t);

static void get_eth_connect_state_cb(struct mosquitto *mosq,uint8_t state){
	static uint8_t eth_up_cnt = 0 ;
	if(state){
		if(eth_up_cnt){
			// 连接丢失，需要重新连接
			mosquitto_reconnect_async(mosq);
			log_i("Network cable physical disconnection, reconnecting.... .");
		}else{
			eth_up_cnt = 1 ;	//去除第一次初始化eth0状态
		}
	}else{
		type_dw_switch_ico.cascading_connection_state = 0 ;
		mqtt_client_connect_success_flag = false ;
	}

}


/*连接断开回调*/
static void disconnect_callback(struct mosquitto *mosq, void *obj, int rc){
	if(rc!= MOSQ_ERR_SUCCESS){
		if((rc == MOSQ_ERR_CONN_LOST)||(rc== MOSQ_ERR_KEEPALIVE)){ //客户端丢失连接或未收到心跳包
			// 连接丢失，需要重新连接
			mosquitto_reconnect_async(mosq);
			log_i("keep alive timeout, reconnecting..，because=%d,%s",rc,mosquitto_strerror(rc));
		 }else{
			 log_w("disconnect_callback =%d,%s.",rc,mosquitto_strerror(rc));
		 }
	}else{
		log_i("mqtt active disconnection.");
	}
	mqtt_client_connect_success_flag = false ;
	type_dw_switch_ico.cascading_connection_state = 0 ;
}



/*连接成功回调*/
static void connect_callback(struct mosquitto *mosq, void *obj, int rc){
	 if(rc == MOSQ_ERR_SUCCESS){
		 // 连接或重连成功后重新进行订阅操作
		Mqtt_Subscribe_Topic(mosq);
		mqtt_client_connect_success_flag = true ;
		type_dw_switch_ico.cascading_connection_state =1 ;
		log_i("Mqtt brokerport connect successfully.");
	 }else{
		mqtt_client_connect_success_flag = false ;
		type_dw_switch_ico.cascading_connection_state = 0 ;
		log_e("connect error,code=%d,-%s!",rc,mosquitto_strerror(rc));
			//exit(1);
	 }

}



/*获取到订阅的内容*/
// MQTT消息回调函数
static void mqtt_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
    if (strcmp((char*)msg->topic, Mqtt_Topic_Masg_t.propert_set_topic) == 0) {
        log_d("Mqtt_Masg_Date_t[Remote_Control_Topic_n].set_topic");
        handle_propert_set_topic(mosq,msg); // 调用子函数处理消息
        return ;
    } else if (strcmp((char*)msg->topic, Mqtt_Topic_Masg_t.propert_post_reply_topic) == 0) {
        log_d("Mqtt_Masg_Date_t[Remote_Control_Topic_n].propert_post_reply_topic");
    } else if (strcmp((char*)msg->topic, Mqtt_Topic_Masg_t.propert_get_topic) == 0) {
        log_d("Mqtt_Masg_Date_t[Remote_Control_Topic_n].propert_get_topic");
        handle_propert_get_topic(mosq,msg); // 调用子函数处理消息
        return ;
    } else {
        for (uint8_t i = 0; i < Max_Topic_Number; i++) {
            if (strcmp((char*)msg->topic, Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic) == 0) {
                log_d("Retrieve the subscription topics:%s", Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic);
                break;
            }
        }
    }
}

static struct mosquitto *Mqtt_Client_Init(struct Mqtt_Client_Date Mqtt_Client_Date_t){
    int                 rv;
    static struct mosquitto    *mosq_temp = NULL;
    static bool init_cnts = false ;
    int ret = -1 ;

    if( !init_cnts ){
    	init_cnts = true ;
        /* MQTT 初始化 */
         rv = mosquitto_lib_init();
         if(rv != MOSQ_ERR_SUCCESS) {
        	 log_e("mosquitto lib int failure:%s", mosquitto_strerror(rv));
         }
         log_d(" mosquitto lib init successfully!");
         /* 创建MQTT 客户端 */
         mosq_temp = mosquitto_new(Mqtt_Client_Date_t.clientid,true,(void *)&Mqtt_Client_Date_t);
    	 if(mosq_temp == NULL) {
    		 log_e(" create mosquitto client failed: %s",strerror(errno));
    		 goto fail_mosquitto_new;
    	 }
    	 log_d("create  mosquitto client successfully!");
    }
	 /* 设置账号密码 */
     ret = mosquitto_username_pw_set(mosq_temp,Mqtt_Client_Date_t.username,Mqtt_Client_Date_t.password);
	if(ret != MOSQ_ERR_SUCCESS){
		log_e("mosquitto_username_pw_set failed %d,message: %s",ret, mosquitto_strerror(ret));
		 return NULL;
	 }
	/* 连接成功回调函数 */
	mosquitto_connect_callback_set(mosq_temp,connect_callback);
	/* 断开连接回调函数 */
	mosquitto_disconnect_callback_set(mosq_temp,disconnect_callback);
    //网口状态回调函数 检测物理层面 拔掉和插上网线事件
	Eth_Connect_State_Register(mosq_temp,get_eth_connect_state_cb);
	/* 收到消息回调函数 */
	mosquitto_message_callback_set(mosq_temp, mqtt_message_callback);
	//客户端连接服务器
	 rv = mosquitto_connect_async(mosq_temp, Mqtt_Client_Date_t.brokeraddress, Mqtt_Client_Date_t.brokerport, Mqtt_Client_Date_t.keep_alive);
	if (rv !=MOSQ_ERR_SUCCESS){
		log_e("mosquitto connect fail: %s",mosquitto_strerror(rv));
		goto fail_mosq_conn;
	}
    //不阻塞，库函数中将自动创建线程实现
	rv = mosquitto_loop_start(mosq_temp);
    if(rv != MOSQ_ERR_SUCCESS){
        log_e("mosquitto loop fail: %s",mosquitto_strerror(rv));
        goto fail_mosq_loop_start;
    }
	 return mosq_temp;
 fail_mosq_loop_start:
	 mosquitto_disconnect(mosq_temp);
 fail_mosq_conn:
	 mosquitto_destroy(mosq_temp);
 fail_mosquitto_new:
	 mosquitto_lib_cleanup();
	    return NULL;
}



void create_mqtt_pub_pthread_init(void){
	//(1)timer thread
	pthread_t mqtt_pub_id;

	pthread_mutex_init(&pthread_mutex_t_mqtt_t,NULL);//初始化锁

	int mqtt_pub_ret = pthread_create(&mqtt_pub_id,NULL,mqtt_pub_msg_task,NULL);
	if(mqtt_pub_ret){
		perror("create_mqtt_pub_pthread_init error");
		log_e("create_mqtt_pub_pthread_init thread created error !.");
		exit(EXIT_FAILURE);
	}
	log_d("create_mqtt_pub_pthread_init thread created.");
}


void* mqtt_pub_msg_task(void *arg) {
	mqtt_ip_tcp_def mqtt_ip_tcp_def_t ;
	mqtt_port_tcp_def mqtt_port_tcp_def_t ;
	mqtt_login_def mqtt_login_def_t ;
	static struct Mqtt_Client_Date Mqtt_Client ;

	struct Client_Id_Name  Client_Id_Name_t ;
    struct Client_Name Client_Name_t ;
    struct Client_Id_Date  Client_Id_Date_t  ;


    Mqtt_Client.brokerport = 1883  ;
    Mqtt_Client.keep_alive = 60 ;
    Mqtt_Client.mosq = NULL ;


    Client_Id_Name_t.UserName = NULL ;
    Client_Name_t.Name = NULL ;
    memset(Client_Id_Date_t.Client_Id, 0, sizeof(Client_Id_Date_t.Client_Id));
    memset(Client_Id_Date_t.Time_Stamp, 0, sizeof(Client_Id_Date_t.Time_Stamp));

	Set_Mqtt_Message_Quality_Init();					//初始化消息服务质量 Qos

    while(1){
    	if( Set_Mqtt_Client_System_t.mqtt_username_change_flag || Set_Mqtt_Client_System_t.mqtt_password_change_flag  || \
    		Set_Mqtt_Client_System_t.mqtt_host_change_flag  || Set_Mqtt_Client_System_t.mqtt_port_change_flag ){
    		Set_Mqtt_Client_System_t.mqtt_username_change_flag  = 0 ;
    		Set_Mqtt_Client_System_t.mqtt_password_change_flag = 0 ;
    		Set_Mqtt_Client_System_t.mqtt_host_change_flag  = 0 ;
    		Set_Mqtt_Client_System_t.mqtt_port_change_flag = 0 ;
		    read_saveenv_cjson_mqttlogin_parameter( &mqtt_login_def_t);
		    read_saveenv_cjson_mqttip_parameter( &mqtt_ip_tcp_def_t);
		    read_saveenv_cjson_mqttport_parameter( &mqtt_port_tcp_def_t);
			Client_Id_Name_t.UserName = mqtt_login_def_t.username;
			Client_Id_Date_t = Greate_Client_Id(&Client_Id_Name_t);

			Client_Name_t.Name =  mqtt_login_def_t.username;
			Topics_Init(&Client_Name_t);   			//初始化Post主题
    		if( mqtt_client_connect_success_flag == true){		//已连接到服务器
    			Set_Topic_Execute_Function_UnRegister();		//注销set 执行函数
				mosquitto_disconnect(Mqtt_Client.mosq);			// 先断开连接
				 log_d("mosquitto disconnect,reset connect");
    		}
    		if(Mqtt_Client.mosq != NULL ){
        		mosquitto_reinitialise(Mqtt_Client.mosq,Client_Id_Date_t.Client_Id,true,NULL);//重新初始化 Mosquitto 客户端
        		log_i("mosquitto_reinitialise");
    		}
    	    memset(Mqtt_Client.clientid, 0, sizeof(Mqtt_Client.clientid));
    	    memset(Mqtt_Client.username, 0, sizeof(Mqtt_Client.username));
    	    memset(Mqtt_Client.password, 0, sizeof(Mqtt_Client.password));
    	    memset(Mqtt_Client.brokeraddress, 0, sizeof(Mqtt_Client.brokeraddress));

		    strncpy(Mqtt_Client.clientid,  Client_Id_Date_t.Client_Id , MQTT_CLIENT_MAX_SIZE );
		    strncpy(Mqtt_Client.username,  mqtt_login_def_t.username , MQTT_CLIENT_MAX_SIZE );
		    strncpy(Mqtt_Client.password,  mqtt_login_def_t.password , MQTT_CLIENT_MAX_SIZE );
		    strncpy(Mqtt_Client.brokeraddress,  mqtt_ip_tcp_def_t.Host , MQTT_CLIENT_MAX_SIZE ); //JSON数据结构转换为JSON字符串
		    Mqtt_Client.brokerport = mqtt_port_tcp_def_t.port ;
		    Mqtt_Client.keep_alive = mqtt_port_tcp_def_t.keep_alive ;
		    log_d("Mqtt clientid =%s",Mqtt_Client.clientid);
		    log_d("Mqtt username =%s",Mqtt_Client.username);
		    log_d("Mqtt password =%s",Mqtt_Client.password);
		    log_d("Mqtt passwbrokeraddressord =%s",Mqtt_Client.brokeraddress);
		    log_d("Mqtt brokerport =%d",Mqtt_Client.brokerport);

		    Mqtt_Client.mosq = Mqtt_Client_Init(Mqtt_Client);
		    Set_Topic_Execute_Function_Register(Set_Topic_Execute_Function_cb);
    	}else{
        	post_device_event_status(Mqtt_Client.mosq,&Client_Id_Name_t);
        	post_device_message(Mqtt_Client.mosq,&Client_Id_Name_t);
    	}
    }
    // 销毁互斥锁
    pthread_mutex_destroy(&pthread_mutex_t_mqtt_t);
    mosquitto_disconnect(Mqtt_Client.mosq);
    mosquitto_loop_stop(Mqtt_Client.mosq, true);
    mosquitto_destroy(Mqtt_Client.mosq);
    mosquitto_lib_cleanup();
    return 0;

}


//发送盖板事件消息
static void post_device_event_status(struct mosquitto *mosq ,struct Client_Id_Name  *Client_Id_Name_t ){
	 struct Client_Id_Date  Client_Id_Date_t ;
	    struct Event_Post Event_Post_t;
	if(mqtt_client_connect_success_flag == true){
    	if(check_time_arrive(SCAN_DEV_EVENT_POST_TIMER_NUMBER,500)){
    		clear_time_cnt(SCAN_DEV_EVENT_POST_TIMER_NUMBER);
    	    pthread_mutex_lock(&pthread_mutex_t_mqtt_t);  //加锁
        	for(uint8_t i=0;i<END_TRANSDUCER_NUMBER;i++){
            	Event_Post_t.Event_Post_Packet_Masg_t.Event_Params_t[i].Publish_Params =deal_transducer_masg_t.dev_online_state[i];
        	}
        	Event_Post_t.Event_Post_Packet_Masg_t.Event_Params_t[6].Publish_Params = 0 ;
        	Event_Post_t.Event_Post_Packet_Masg_t.Event_Params_t[7].Publish_Params = 0 ;
        	Event_Post_t.Event_Post_Packet_Masg_t.Event_Params_t[8].Publish_Params = 0 ;
        	Event_Post_t.Event_Post_Packet_Masg_t.Event_Params_t[9].Publish_Params = 0 ;
        	Event_Post_t.mosq = mosq ;
        	Client_Id_Date_t = Greate_Client_Id(Client_Id_Name_t);	//获取时间戳
        	Event_Post_t.Event_Post_Packet_Masg_t.TimeStamp = Client_Id_Date_t.Time_Stamp ;
        	 Event_Post_Massage(&Event_Post_t);
			 pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
    	}
	}
}

//发送盖板post消息
static void post_device_message(struct mosquitto *mosq ,struct Client_Id_Name  *Client_Id_Name_t){
	struct Client_Id_Date  Client_Id_Date_t ;
	struct Propert_Post Propert_Post_t ;
	if(mqtt_client_connect_success_flag == true){
		mqtt_port_tcp_def mqtt_port_tcp_def_t ;
	    read_saveenv_cjson_mqttport_parameter( &mqtt_port_tcp_def_t);
		if(check_time_arrive(SCAN_DEV_PROPERT_POST_TIMER_NUMBER,mqtt_port_tcp_def_t.sacn_change_paramter_timer*100)){
			clear_time_cnt(SCAN_DEV_PROPERT_POST_TIMER_NUMBER);
			pthread_mutex_lock(&pthread_mutex_t_mqtt_t);  //加锁
			Propert_Post_t.mosq = mosq ;
			Client_Id_Date_t = Greate_Client_Id(Client_Id_Name_t);	//获取时间戳
			Propert_Post_t.Propert_Post_Packet_Masg_t.TimeStamp = Client_Id_Date_t.Time_Stamp ;
			if(deal_transducer_masg_t.dev_online_state[external_temperature_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[External_Temperature].Publish_Params= deal_transducer_masg_t.external_temperature_date ;
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[External_Humidity].Publish_Params= deal_transducer_masg_t.external_humidity_date ;
			}
			if(deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Internal_Temperature].Publish_Params= deal_transducer_masg_t.internal_temperature_date ;
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Internal_Humidity].Publish_Params= deal_transducer_masg_t.internal_humidity_date ;
			}
			if(deal_transducer_masg_t.dev_online_state[illumination_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[External_Illumination].Publish_Params=deal_transducer_masg_t.illumination_par_t.illumination_percentage ;
			}
			if(deal_transducer_masg_t.dev_online_state[sleet_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[External_Sleet].Publish_Params= deal_transducer_masg_t.sleet_state ;
			}
			if(deal_transducer_masg_t.dev_online_state[smoke_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Internal_Smoke].Publish_Params= deal_transducer_masg_t.smoke_state ;
			}
			if(deal_transducer_masg_t.dev_online_state[water_transducer] == online){
				Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Internal_Water].Publish_Params= deal_transducer_masg_t.water_state ;
			}
			Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Fan_Velocity].Publish_Params= deal_transducer_masg_t.fan_velocity ;
			Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Run_Mode].Publish_Params= deal_transducer_masg_t.local_run_mode ;
			Propert_Post_t.Propert_Post_Packet_Masg_t.Propert_Params_t[Board_Status].Publish_Params=  deal_transducer_masg_t.board_status ;
			Propert_Post_Message(&Propert_Post_t);
			 pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
		}
	}
}



// 处理propert_get_topic消息的子函数
static void handle_propert_get_topic(struct mosquitto *mosq,const struct mosquitto_message *msg) {
	//检查mqtt消息有效载荷和长度
    if ( msg->payload == NULL) {
        log_e("mqtt recv get topic payload is NULL !!!");
        return  ;
    }
    struct Client_Id_Date  Client_Id_Date_t ;
    struct Client_Id_Name  Client_Id_Name_t ;
    Client_Id_Date_t = Greate_Client_Id(&Client_Id_Name_t);	//获取时间戳
    // 分配缓存空间
    struct Propert_Get *propert_get_topic_masg_t ;
    propert_get_topic_masg_t = malloc(sizeof( struct Propert_Get));
    if (propert_get_topic_masg_t == NULL) {
   	 log_e("Unable to allocate memory");
        return ;
    }
    memset(propert_get_topic_masg_t,0,sizeof( struct Propert_Get));
    size_t len = strlen((char *)msg->payload) + 1;
    propert_get_topic_masg_t->propert_get_string = malloc(len);
    if (  propert_get_topic_masg_t->propert_get_string == NULL) {
   	 log_e("Unable to allocate memory");
   	 return ;
     }
    memset(propert_get_topic_masg_t->propert_get_string,0,len);

    // 复制消息内容到结构体成员
    strncpy(propert_get_topic_masg_t->propert_get_string, (char*)msg->payload, msg->payloadlen);
    // 将mosq和Client_Id_Date_t指针赋值给结构体成员
    propert_get_topic_masg_t->mosq = mosq;
    propert_get_topic_masg_t->Time_Stamp = Client_Id_Date_t.Time_Stamp;
    propert_get_topic_masg_t->Propert_Params_t[External_Temperature].Publish_Params= deal_transducer_masg_t.external_temperature_date ;
    propert_get_topic_masg_t->Propert_Params_t[External_Humidity].Publish_Params= deal_transducer_masg_t.external_humidity_date ;
    propert_get_topic_masg_t->Propert_Params_t[Internal_Temperature].Publish_Params= deal_transducer_masg_t.internal_temperature_date ;
    propert_get_topic_masg_t->Propert_Params_t[Internal_Humidity].Publish_Params= deal_transducer_masg_t.internal_humidity_date ;
    propert_get_topic_masg_t->Propert_Params_t[External_Illumination].Publish_Params=deal_transducer_masg_t.illumination_par_t.illumination_percentage ;
    propert_get_topic_masg_t->Propert_Params_t[External_Sleet].Publish_Params= deal_transducer_masg_t.sleet_state ;
    propert_get_topic_masg_t->Propert_Params_t[Internal_Water].Publish_Params = deal_transducer_masg_t.water_state ;
    propert_get_topic_masg_t->Propert_Params_t[Internal_Smoke].Publish_Params= deal_transducer_masg_t.smoke_state ;
    propert_get_topic_masg_t->Propert_Params_t[Fan_Velocity].Publish_Params= deal_transducer_masg_t.fan_velocity ;
    propert_get_topic_masg_t->Propert_Params_t[Run_Mode].Publish_Params= deal_transducer_masg_t.local_run_mode ;
    propert_get_topic_masg_t->Propert_Params_t[Board_Status].Publish_Params=  deal_transducer_masg_t.board_status ;


    // 初始化线程属性
    pthread_attr_t mqtt_get_pthread_attr;
    pthread_t Propert_get_id;
    pthread_attr_init(&mqtt_get_pthread_attr);
    pthread_attr_setdetachstate(&mqtt_get_pthread_attr, PTHREAD_CREATE_DETACHED);
    // 创建新线程处理消息
    int ret = pthread_create(&Propert_get_id, &mqtt_get_pthread_attr, Propret_Get_Sub_Masg_pthread, (void*)propert_get_topic_masg_t);
    if (ret < 0) {
        log_e("creat pthread deal get propret masg error!!   ");
        free(propert_get_topic_masg_t->propert_get_string);
        free(propert_get_topic_masg_t);
    }
    // 销毁线程
    pthread_attr_destroy(&mqtt_get_pthread_attr);
    log_d("creat pthread deal get propret masg  ");

}



// 处理propert_set_topic消息的子函数
static void handle_propert_set_topic(struct mosquitto *mosq,const struct mosquitto_message *msg) {
	//检查mqtt消息有效载荷和长度
    if ( msg->payload == NULL) {
        log_e("mqtt recv set topic payload is NULL !!!");
        return;
    }
    struct Client_Id_Date  Client_Id_Date_t ;
    struct Client_Id_Name  Client_Id_Name_t ;
    Client_Id_Date_t = Greate_Client_Id(&Client_Id_Name_t);	//获取时间戳
     // 分配缓存空间
     struct Propert_Set *propert_set_topic_masg_t ;
     propert_set_topic_masg_t = malloc(sizeof( struct Propert_Set));
     if (propert_set_topic_masg_t == NULL) {
    	 log_e("Unable to allocate memory");
         return ;
     }
     memset(propert_set_topic_masg_t,0,sizeof( struct Propert_Set));
     size_t len = strlen((char *)msg->payload) + 1;
     propert_set_topic_masg_t->propert_set_string = malloc(len);
     if (  propert_set_topic_masg_t->propert_set_string == NULL) {
    	 log_e("Unable to allocate memory");
    	 return ;
      }
     memset(propert_set_topic_masg_t->propert_set_string,0,len);

     //复制消息给缓存结构体
     strncpy(propert_set_topic_masg_t->propert_set_string, (char*)msg->payload, msg->payloadlen);
     // 将mosq和Client_Id_Date_t指针赋值给结构体成员
     propert_set_topic_masg_t->mosq = mosq;
     propert_set_topic_masg_t->Time_Stamp = Client_Id_Date_t.Time_Stamp;

     pthread_t Propert_Set_id;
     pthread_attr_t mqtt_set_pthread_attr;
     // 初始化线程属性
     pthread_attr_init(&mqtt_set_pthread_attr);
     pthread_attr_setdetachstate(&mqtt_set_pthread_attr, PTHREAD_CREATE_DETACHED);
     // 创建新线程处理消息
     int ret = pthread_create(&Propert_Set_id, &mqtt_set_pthread_attr, Propret_Set_Sub_Masg_pthread, (void *)propert_set_topic_masg_t);
     if (ret < 0) {
         log_e("creat pthread deal set propret masg error!!   ");
         free(propert_set_topic_masg_t->propert_set_string);
         free(propert_set_topic_masg_t);
     }
     // 销毁线程
     pthread_attr_destroy(&mqtt_set_pthread_attr);
     log_d("creat pthread deal set propret masg  ");

}

static int Set_Topic_Execute_Function_cb(int remote_control_switch,int remote_control_cmd,int remote_control_timer){

	if(switch_mode != FIX_MODE){
		if(  get_motor_motion_status() !=MOTOR_MOVING_STATUS){
			if( remote_control_switch ==0 ){
				GetInformMqttMasgEven_t.test_motor_delay_T4_date = 0 ;
			}else{
				GetInformMqttMasgEven_t.test_motor_delay_T4_date = remote_control_timer;
			}
			GetInformMqttMasgEven_t.remote_test_flag = remote_control_switch ;
			GetInformMqttMasgEven_t.remote_test_motor_action_type = remote_control_cmd ;

			log_d("RemoteEnterTestMode Status is : %d",GetInformMqttMasgEven_t.remote_test_flag);
			log_d("Remote Control Switch Cmd is : %d",GetInformMqttMasgEven_t.remote_test_motor_action_type);
			log_d("Remote Control Switch timer is : %d",GetInformMqttMasgEven_t.test_motor_delay_T4_date);
			return 0;
		}else{
			log_w("motor moving .......,please wait move fish !!!");
			return -1 ;
		}
	}else{
		GetInformMqttMasgEven_t.remote_test_flag = 0 ; 		 //远程控制无效
		GetInformMqttMasgEven_t.test_motor_delay_T4_date = 0 ;
		log_w("remote Ineffective control !!!");
		return -2;
	}
}



