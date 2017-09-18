#ifndef SIREN_H_
#define SIREN_H_

#include <stdint.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t siren_status_t;
typedef int32_t siren_event_t;
typedef int32_t siren_state_t;
typedef int32_t siren_vt_t;

typedef unsigned long siren_t;


typedef int (*init_input_stream_t)(void *token);
typedef void (*release_input_stream_t)(void *token);
typedef int (*start_input_stream_t)(void *token);
typedef void (*stop_input_stream_t)(void *token);
typedef int (*read_input_stream_t)(void *token, char *buff, int len);
typedef void (*on_err_input_stream_t)(void *token);

#define VT_TYPE_AWAKE 1
#define VT_TYPE_SLEEP 2
#define VT_TYPE_HOTWORD 3
#define VT_TYPE_OTHER 4

typedef struct {
    float vt_block_avg_score;       // 所有phone声学平均得分门限
    float vt_block_min_score;       // 单个phone声学最低得分门限
    float vt_classify_shield;       // 本地激活二次确认门限

    bool vt_left_sil_det;
    bool vt_right_sil_det;
    bool vt_remote_check_with_aec;  // 是否在aec状态下进行远程asr确认，如果为true，则不会发出_nocmd类型事件
    bool vt_remote_check_without_aec; // 是否在非aec状态下进行远程asr确认
    bool vt_local_classify_check;   // 是否进行本地激活二次确认
    
    std::string nnet_path;          // 激活词模型绝对路径
} siren_vt_alg_config;

typedef struct {
    int vt_type;                    // 激活词类型，1是激活词，2是睡眠词，3是热词
    std::string vt_word;            // 激活词，utf-8的汉字
    std::string vt_phone;           // 激活词音素，拼音，假如激活词是“你好”，则这里填ni2hao3，声调轻声使用数字5
    bool use_default_config;
    siren_vt_alg_config alg_config;
} siren_vt_word;

typedef struct {
    init_input_stream_t init_input;
    release_input_stream_t release_input;
    start_input_stream_t start_input;
    stop_input_stream_t stop_input;
    read_input_stream_t read_input;
    on_err_input_stream_t on_err_input;
} siren_input_if_t;                    // 音频流输入回调函数集合

typedef struct {
    int start;          // 在下面第一个SIREN_EVENT_VAD_DATA语音帧中激活词所在的开始，单位是float
    int end;            // 语音帧中激活词结尾
    float energy;       // 激活词的能量绝对值
} vt_event_t;

#define VOICE_MASK (0x1 << 0)
#define SL_MASK (0x1 << 1)
#define VT_MASK (0x1 << 2)

typedef struct {
    siren_event_t event;
    int length;
    int flag;
   
    double sl;
    double background_energy;
    double background_threshold;
    
    vt_event_t vt;
    void *buff;
} voice_event_t;

#define HAS_VOICE(flag) ((flag & VOICE_MASK) != 0)
#define HAS_SL(flag) ((flag & SL_MASK) != 0)
#define HAS_VT(flag) ((flag & VT_MASK) != 0)

// 当发生特定语音事件时，siren会回掉该接口
// @token: 通过init_siren传入的token
typedef void (*on_voice_event_t)(void *token, voice_event_t *voice_event);


typedef void (*on_net_event_t)(void *token, char *data, int len);

typedef struct {
    on_voice_event_t voice_event_callback;
} siren_proc_callback_t;

typedef struct {
    on_net_event_t net_event_callback;
} siren_net_callback_t;

typedef void (*on_raw_voice_t)(void *token, int length, void *buff);

typedef struct {
    on_raw_voice_t raw_voice_callback;
} siren_raw_stream_callback_t;

typedef void (*on_siren_state_changed_t)(void *token, int current);

typedef struct {
    on_siren_state_changed_t state_changed_callback;
} siren_state_changed_callback_t;

enum {
    SIREN_STATUS_OK = 0,
    SIREN_STATUS_CONFIG_ERROR,
    SIREN_STATUS_CONFIG_NO_FOUND,
    SIREN_STATUS_ERROR
};

enum {
    SIREN_VT_OK = 0,                // 成功添加激活词
    SIREN_VT_DUP,                   // 激活词已经存在
    SIREN_VT_ERROR,                 // 添加激活词失败
    SIREN_VT_NO_EXIT
};

enum {
    SIREN_EVENT_VAD_START = 100,    // 语音帧的开始
    SIREN_EVENT_VAD_DATA,           // 携带语音信息
    SIREN_EVENT_VAD_END,            // 语音帧结束
    SIREN_EVENT_VAD_CANCEL,         // 误激活引发的cancel
    SIREN_EVENT_WAKE_VAD_START,
    SIREN_EVENT_WAKE_VAD_DATA,
    SIREN_EVENT_WAKE_VAD_END,
    SIREN_EVENT_WAKE_PRE,
    SIREN_EVENT_WAKE_NOCMD,         // 单独激活事件
    SIREN_EVENT_WAKE_CMD,           // 以激活词开头，以其他语音结尾的混合激活事件，需要通过asr来进一步判断激活情况
    SIREN_EVENT_WAKE_CANCEL,        // 可以本地判断的误激活事件
    SIREN_EVENT_SLEEP,              // 睡眠激活词
    SIREN_EVENT_HOTWORD,
    SIREN_EVENT_SR,
    SIREN_EVENT_VOICE_PRINT,        // 声纹事件，包含声纹信息
    SIREN_EVENT_DIRTY
};

enum {
    SIREN_STATE_AWAKE =1 ,          // 激活
    SIREN_STATE_SLEEP               // 睡眠
};

// @token: 将在后续回调方法中被调用
// @path:  JSON配置文件所在的本地文件绝对地址
// @input: 音频流输入回调函数集合
//
// @returns: siren对象的句柄
siren_t init_siren(void *token, const char *path, siren_input_if_t *input);

// 打开语音处理流，此时siren将源源不断的从siren_input_if_t提供的输入接口中读取音频数据，
// 直到stop_siren_process_stream或stop_siren_stream被调用
siren_t start_siren_process_stream(siren_t siren, siren_proc_callback_t *callback);

// 打开裸数据流，此时siren将源源不断的从siren_input_if_t提供的输入接口中读取音频数据，
// 直到stop_siren_raw_stream或stop_siren_stream被调用
siren_t start_siren_raw_stream(siren_t siren, siren_raw_stream_callback_t *callback);

// 关闭数据处理音频流，如果此时没有打开裸数据音频流，那么将调用siren_input_if_t的stop_stream方法
void stop_siren_process_stream(siren_t siren);

// 关闭裸数据音频流，如果此时没有打开语音处理音频流，那么将调用siren_input_if_t的stop_stream方法
void stop_siren_raw_stream(siren_t siren);

// 强制关闭音频流，将调用siren_input_if_t的stop_stream方法
void stop_siren_stream(siren_t siren);

// 强制设置siren的激活/睡眠状态
// @state: SIREN_STATE_AWAKE or SIREN_STATE_SLEEP
// @callback: 如果不是NULL则调用为异步，否则为同步，异步调用会在完成时调用callback接口
void set_siren_state(siren_t siren, siren_state_t state, siren_state_changed_callback_t *callback);

// 强制设置水平和垂直寻向角度
// @ho:  水平角度
// @ver: 垂直角度
void set_siren_steer(siren_t siren, float ho, float ver);

void destroy_siren(siren_t siren);

// 添加唤醒激活词
// @return: SIREN_VT_OK, SIREN_VT_DUP, SIREN_VT_ERROR
siren_vt_t add_vt_word(siren_t siren, siren_vt_word *word, bool use_default_config);
siren_vt_t remove_vt_word(siren_t siren, const char *word);

// 查询所有激活词
int get_vt_word(siren_t siren, siren_vt_word **words);


void start_siren_monitor(siren_t siren, siren_net_callback_t *callback);
siren_status_t broadcast_siren_event(siren_t siren, char *data, int len);


#ifdef __cplusplus
}
#endif

#endif
