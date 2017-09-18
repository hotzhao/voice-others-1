﻿#ifndef SIREN_CONFIG_IF_H_
#define SIREN_CONFIG_IF_H_

#include <stdint.h>
#include <vector>
#include <string>


namespace BlackSiren {

struct MicPos {
    std::vector<long double> pos;
};


//JSON KEY
#define IPC_CHANNEL "channel"
#define IPC_DBUS "dbus"
#define IPC_BINDER "binder"
#define IPC_SHARE_MEM "share_mem"

#define KEY_BASIC_CONFIG "basic_config"
#define KEY_ALG_CONFIG "alg_config"
#define KEY_DEBUG_CONFIG "debug_config"

#define KEY_MIC_NUM "mic_num"
#define KEY_MIC_CHANNEL_NUM "mic_channel_num"
#define KEY_MIC_SAMPLE_RATE "mic_sample_rate"
#define KEY_MIC_AUDIO_BYTE "mic_audio_byte"
#define KEY_MIC_FRAME_LENGTH "mic_frame_length"

#define KEY_SIREN_IPC "siren_ipc"
#define KEY_SIREN_CHANNEL_RMEM "siren_channel_rmem"
#define KEY_SIREN_CHANNEL_WMEM "siren_channel_wmem"

#define KEY_SIREN_INPUT_ERR_RETRY_NUM "siren_input_err_retry_num"
#define KEY_SIREN_INPUT_ERR_RETRY_TIMEOUT "siren_input_err_retry_timeout"

#define KEY_SIREN_MONITOR_UDP_PORT "siren_monitor_udp_port"

#define KEY_ALG_USE_LEGACY_CONFIG_FILE "alg_use_legacy_config_file"
#define KEY_ALG_LEGACY_CONFIG_FILE_PATH "alg_legacy_config_file_path"
#define KEY_ALG_LAN "alg_lan"
#define KEY_ALG_RS_MICS "alg_rs_mics"
#define KEY_ALG_AEC "alg_aec"
#define KEY_ALG_AEC_MICS "alg_aec_mics"
#define KEY_ALG_AEC_REF_MICS "alg_aec_ref_mics"
#define KEY_ALG_AEC_SHIELD "alg_aec_shield"
#define KEY_ALG_AEC_AFF_CPUS "alg_aec_aff_cpus"
#define KEY_ALG_AEC_MAT_AFF_CPUS "alg_aec_mat_aff_cpus"
#define KEY_ALG_BF_SCALING "alg_bf_scaling"

#define KEY_ALG_RAW_STREAM_SL_DIRECTION "alg_raw_stream_sl_direction"
#define KEY_ALG_RAW_STREAM_BF "alg_raw_stream_bf"
#define KEY_ALG_RAW_STREAM_AGC "alg_raw_stream_agc"

#define KEY_ALG_VT_ENABLE "alg_vt_enable"
#define KEY_ALG_VAD_ENABLE "alg_vad_enable"

#define KEY_ALG_VAD_MICS "alg_vad_mics"
#define KEY_ALG_VAD_BASERANGE "alg_vad_baserange"
#define KEY_ALG_VAD_DYNRANGE_MIN "alg_vad_dynrange_min"
#define KEY_ALG_VAD_DYNRANGE_MAX "alg_vad_dynrange_max"

#define KEY_ALG_MIC_POS "alg_mic_pos"
#define KEY_ALG_NEED_I2S_DELAY_MICS "alg_need_i2s_delay_mics"
#define KEY_ALG_I2S_DELAY_MICS "alg_i2s_delay_mics"
#define KEY_ALG_SL_MICS "alg_sl_mics"
#define KEY_ALG_BF_MICS "alg_bf_mics"
#define KEY_ALG_OPUS_COMPRESS "alg_opus_compress"

#define KEY_ALG_VT_PHOMOD "alg_vt_phomod"
#define KEY_ALG_VT_DNNMOD "alg_vt_dnnmod"

#define KEY_ALG_DEF_VT "alg_def_vt"
#define KEY_VT_TYPE "vt_type"
#define KEY_VT_WORD "vt_word"
#define KEY_VT_PHONE "vt_phone"
#define KEY_VT_AVG_SCORE "vt_block_avg_score"
#define KEY_VT_MIN_SCORE "vt_block_min_score"
#define KEY_VT_LEFT_SIL_DET "vt_left_check"
#define KEY_VT_RIGHT_SIL_DET "vt_right_check"
#define KEY_VT_REMOTE_CHECK_WITH_AEC "vt_remote_check_with_aec"
#define KEY_VT_REMOTE_CHECK_WITHOUT_AEC "vt_remote_check_without_aec"
#define KEY_VT_LOCAL_CLASSIFY_CHECK "vt_local_classify_check"
#define KEY_VT_CLASSIFY_SHIELD "vt_classify_shield"
#define KEY_NNET_PATH "vt_nnet_path"

#define KEY_ALG_RS_DELAY_ON_LEFT_RIGHT_CHANNEL "alg_rs_delay_on_left_right_channel"

#define KEY_RAW_STREAM_CHANNEL_NUM "raw_stream_channel_num"
#define KEY_RAW_STREAM_SAMPLE_RATE "raw_stream_sample_rate"
#define KEY_RAW_STREAM_BYTE "raw_stream_byte"

#define KEY_DEBUG_MIC_ARRAY_RECORD "debug_mic_array_record"
#define KEY_DEBUG_PRE_RESULT_RECORD "debug_pre_result_record"
#define KEY_DEBUG_PROC_RESULT_RECORD "debug_proc_result_record"
#define KEY_DEBUG_RS_RECORD "debug_rs_record"
#define KEY_DEBUG_AEC_RECORD "debug_aec_record"
#define KEY_DEBUG_BF_RECORD "debug_bf_record"
#define KEY_DEBUG_BF_RAW_RECORD "debug_bf_raw_record"
#define KEY_DEBUG_VAD_RECORD "debug_vad_record"
#define KEY_DEBUG_OPU_RECORD "debug_opu_record"
#define KEY_DEBUG_RECORD_PATH "debug_record_path"


struct DefVTConfig {
    int vt_type;
    std::string vt_word;
    std::string vt_phone;
    float vt_avg_score;
    float vt_min_score;
    bool vt_left_sil_det;
    bool vt_right_sil_det;
    bool vt_remote_check_with_aec;
    bool vt_remote_check_without_aec;
    bool vt_local_classify_check;
    float vt_classify_shield;
    std::string vt_nnet_path;
};

struct AlgConfig {
    std::string alg_legacy_dir;
    std::vector<int> alg_rs_mics;                   // 降采样通道配置，数组形式，告知需要降采样的通道
    std::vector<int> alg_aec_mics;                  // aec音频通道，数组形式，告知aec的音频数据通道
    std::vector<int> alg_aec_ref_mics;              // 参考音源通道，数组形式，用来告知AEC算法哪些通道是参考通道
    std::vector<int> alg_aec_aff_cpus;              // aec处理线程的亲和性
    std::vector<int> alg_aec_mat_aff_cpus;          // aec矩阵运算的亲和性
    std::vector<int> alg_vad_mics;                  // vad使用的音频通道，数组形式
    std::vector<int> alg_need_i2s_delay_mics;
    std::vector<double> alg_i2s_delay_mics;
    std::vector<MicPos> alg_mic_pos;                // 所有麦克风的位置，每个位置由x,y,z三个double坐标描述
    std::vector<int> alg_sl_mics;                   // 寻向使用的音频通道
    std::vector<int> alg_bf_mics;                   // 波束成形使用的音频通道
    std::string alg_vt_config_file_path;
    std::string alg_vt_phomod;                      // 存放音素对应表的绝对路径
    std::string alg_vt_dnnmod;                      // 存放DNN模型的绝对路径
    std::vector<DefVTConfig> def_vt_configs;

    int alg_lan;                                    // 当前语言配置，zh/en，默认zh，已废弃
   
    float alg_aec_shield = 200.0f;
    float alg_raw_stream_sl_direction = 180.0f;     // 裸数据流sl方向
    
    float alg_vad_baserange = 1.25f;
    float alg_vad_dynrange_min = 3.5f;
    float alg_vad_dynrange_max = 6.0f;
    float alg_bf_scaling = 1.0f;

    bool alg_use_legacy_ssp_config_file = true;
    bool alg_aec = true;                            // 是否进行aec
    bool alg_rs_delay_on_left_right_channel;        // 左右声道是否存在不一致的delay，常发生在i2s采集的情况上
    bool alg_raw_stream_bf = true;                  // 裸数据流是否需要bf处理
    bool alg_raw_stream_agc = true;                 // 裸数据是否需要agc处理
    bool alg_vt_enable = true;                      // 是否需要vt事件
    bool alg_vad_enable = true;                     // 是否需要vad事件，此事前端处理流程退化成raw stream
    bool alg_opus_compress = false;                 // 是否输出opus编码后的语音
    bool alg_use_legacy_vt_config_file = true;
};

struct RawStreamConfig {
    int raw_stream_channel_num = 1;                 // 裸音频流输出的通道数，默认为1
    int raw_stream_sample_rate = 16000;             // 裸音频流输出的采样率，默认为16000
    int raw_stream_byte = 2;                        // 裸音频输出的位宽，默认为2
};

struct DebugConfig {
    bool mic_array_record = false;
    bool preprocessed_result_record = false;
    bool processed_result_record = false;
    bool rs_record = false;
    bool aec_record = false;
    bool bf_record = false;
    bool bf_raw_record = false;
    bool vad_record = false;
    bool debug_opu_record = false;

    std::string recording_path;
};

struct SirenConfig {
    int mic_num = 8;                // 麦克风数目（包括AEC参考音源数目）
    int mic_channel_num = 8;        // 麦克风通道数目（包括参考音源通道），一般情况下和mic_num相同
    int mic_sample_rate = 48000;    // 麦克风音频采样率
    int mic_audio_byte = 4;         // 麦克风音频位宽，一般取值为2（16位），4（32位）两种
    int mic_frame_length = 10;      // 建议的每一语音帧的时长，建议语音帧长度为10ms

    bool siren_use_share_mem = false;
    unsigned long siren_recording_socket_wmem = 4 * 1024 * 1024;
    unsigned long siren_recording_socket_rmem = 6 * 1024 * 1024;
    
    int siren_input_err_retry_num = 5;  // 输入音频流出错时重试的最大连续次数，已废弃
    int siren_input_err_retry_timeout = 100; // 两次重试间间隔的时间，单位时毫秒，已废弃

    int udp_port;

    struct AlgConfig alg_config;
    struct RawStreamConfig raw_stream_config;
    struct DebugConfig debug_config;
};

typedef int32_t config_error_t;
enum {
    CONFIG_OK = 0,
    CONFIG_ERROR_OPEN_FILE,
    CONFIG_ERROR_PARSE_FAIL,
    CONFIG_ERROR_UNKNOWN,
};

enum {
    CONFIG_LAN_ZH = 0,
    CONFIG_LAN_EN,
};

}

#endif

