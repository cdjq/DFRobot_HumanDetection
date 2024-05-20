#ifndef _DFROBOT_HUMAN_DETECTION_
#define _DFROBOT_HUMAN_DETECTION_
#include "Arduino.h"

#if (defined ARDUINO_AVR_UNO) && (defined ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

#define ENABLE_DBG ///< 打开这个宏, 可以看到程序的详细运行过程
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define TIME_OUT  5 *1000

#define CMD_HEAD 0
#define CMD_CONFIG 1
#define CMD_CMD   2
#define CMD_LEN_H 3
#define CMD_LEN_L 4
#define CMD_END_H 5
#define CMD_END_L 6
#define CMD_WHITE 7
#define CMD_DATA 8

/**
     * @brief 睡眠综合状态数据
    */
    typedef struct 
    {
        uint8_t presence; ///<存在状态
        uint8_t sleepState;///<睡眠状态
        uint8_t averageRespiration;///<平均呼吸
        uint8_t averageHeartbeat;///<平均心跳
        uint8_t turnoverNumber;///翻身次数
        uint8_t largeBodyMove;///<大幅度体动占比
        uint8_t minorBodyMove;///<小幅度体动占比
        uint8_t apneaEvents;///<呼吸暂停次数

    }sSleepComposite;

    /**
     * @brief 睡眠统计查询
    */
    typedef struct 
    {
        uint8_t sleepQualityScore;///<睡眠质量评分
        uint16_t sleepTime; ///<睡眠时长 单位：分钟
        uint8_t wakeDuration;///<清醒时长
        uint8_t shallowSleepPercentage;///<浅睡时长占比
        uint8_t deepSleepPercentage; ///<深睡时长占比
        uint8_t timeOutOfBed;///<离床时长
        uint8_t exitCount; ///<离床次数
        uint8_t turnOverCount;///<翻身次数
        uint8_t averageRespiration;///<平均呼吸
        uint8_t averageHeartbeat; ///平均心跳
        uint8_t apneaEvents; ///<呼吸暂停
        
    }sSleepStatistics;
    
class DFRobot_HumanDetection{
public:

    /**
     * @brief 工作模式配置结构体
    */
    typedef enum
    {
        eSleepMode = 0x02,
        eFallingMode = 0x01,
    }eWorkMode;

    /**
     * @brief LED灯选择
    */
    typedef enum
    {
        eFALLLed = 0x03,
        eHPLed = 0x04,
    }eLed;

    /**
     * @brief 在睡眠模式下关于人体的数据
    */
    typedef enum
    {
        // eHumanPresenceSwitch, ///<人体存在开关查询
        eHumanPresence,       ///<人体存在查询
        eHumanMovement,       ///<运动信息查询
        eHumanMovingRange,    ///<移动距离，范围 0~100
        eHumanDistance,       ///<人体距离
        
    }esmHuman;

    /**
     * @brief 在睡眠模式下的睡眠数据
    */
    typedef enum
    {
        // eSleepSwitch,///<获取睡眠开关查询
        eInOrNotInBed,///<获取入床或离床状态
        eSleepState,///<获取睡眠状体
        eWakeDuration,///<获取清醒时长
        eDeepSleepDuration,///<获取深睡眠时长
        eSleepQuality,///<获取睡眠质量
        eSleepDisturbances,///<睡眠异常查询
        eSleepQualityRating,///<睡眠质量评级
        eAbnormalStruggle,///<异常挣扎
        eUnattendedState,///<无人计时查询
        eAbnormalStruggleSwitch,///<异常挣扎开关查询
        eUnattendedSwitch,///<无人计时开关查询
        eUnattendedTime,///<无人计时时间查询
        esleepDeadline,///<睡眠截止时间
    }eSmSleep;

    /**
     * @brief 在睡眠模式下睡眠功能配置
    */
    typedef enum
    {
        eSleepStateC,///<获取睡眠状体
        eAbnormalStruggleC,///<异常挣扎
        eUnattendedStateC,///<无人计时
        eUnattendedTimeC,///<无人计时时间
        esleepDeadlineC,///<睡眠截止时间

    }eSmSleepConfig;

    

    

    /**
     * @brief 跌倒模式下人体数据
    */
    typedef enum
    {
        //eHumanSwitch,///<获取跌倒模式人体存在开关查询
        eExistence,///<人体存在查询
        eMotion, ///<运动查询
        eBodyMove,///<体动查询
        eTrajectorySwitch, ///<轨迹点开关查询
        eSeatedHorizontalDistance,///<静坐水平距离
        eMotionHorizontalDistance,///运动水平距

    }eDmHuman;

    /**
     * @brief 获取跌倒数据
    */
    typedef enum
    {
        // eFallSwitch,///<跌倒模式开关查询
        eFallState, ///<跌倒状态
        eFallBreakHeight,///<跌倒打破高度
        eHeightRatioSwitch,///<高度占比开关查询
        estaticResidencyState,///<静止驻留状态
        estaticResidencySwitch,///<静止驻留开关
        eFallSensitivity,///<跌倒灵敏度
    }eDmFall;

    /**
     * @brief 跌倒模式下人体配置
    */
    typedef enum
    {
        eSeatedHorizontalDistanceC,///<静坐水平距离
        eMotionHorizontalDistanceC,///运动水平距
    }eDmHumanConfig;


     /**
     * @brief 获取跌倒数据
    */
    typedef enum
    {
        eFallBreakHeightC,///<跌倒打破高度
        eHeightRatioSwitchC,///<高度占比开关
        eReportFreqC,///<轨迹点信息上报频率
        eReportSwitchC,///<轨迹点上报开关
        eAltTimeC,///<高度累计时间
        eFallSensitivityC,///<跌倒灵敏度设置
        eResidenceSwitchC,///<驻留开关
        eResidenceTime,///<驻留时间

    }eDmFallConfig;



    /**
     * @fn DFRobot_HumanDetection
     * @brief 毫米波人体检测传感器的构造函数
     * @param s 串口接收对象
    */
    DFRobot_HumanDetection(Stream *s);
    ~DFRobot_HumanDetection(){};

    /**
     * @fn begin
     * @brief 初始化传感器
     * @return 返回初始化状态
     * @retval 0 初始化成功
     * @retval 1 初始化失败
    */
    uint8_t begin(void);

    /**
     * @fn configWorkMode
     * @brief 初始化模式
     * @param mode 模式选择
     * @return 返回初始化状态
     * @retval 0 模式配置成功
     * @retval 1 模式配置失败
    */
    uint8_t configWorkMode(eWorkMode mode);

    /**
     * @fn getWorkMode
     * @brief 获取工作模式
     * @return 返回工作模式
    */
    uint8_t getWorkMode(void);

    /**
     * @fn configLEDLight
     * @brief 配置LED灯
     * @param led 选择打开那个LED灯
     * @param sta 0:打开，1:关闭
     * @return 返回控制啊状态
     * @retval 0 配置成功
     * @retval 1 配置失败
    */
    uint8_t configLEDLight(eLed led, uint8_t sta);

    /**
     * @fn getLEDLightStatic
     * @brief 获取LED灯的状态
     * @param led LED灯选择
     * @return 返回灯状态
     * @retval 0 灯关闭
     * @retval 1 灯打开
    */
    uint8_t getLEDLightState(eLed led);

    /**
     * @fn sensorRet
     * @brief 复位传感器
     * @return 返回复位状态
     * @retval 0 复位成功
     * @retval 1 复位失败
    */
    uint8_t sensorRet(void);

    // /**
    //  * @fn getInitState
    //  * @brief 获取初始化是否完成状态
    //  * @return 返回初始化状态
    //  * @retval 0 已完成
    //  * @retval 1 未完成
    // */
    // uint8_t getInitState(void);

    // /**
    //  * @fn smHumanSwitch
    //  * @brief 控制人力存在功能的开关
    //  * @param sw 0 打开 1 关闭
    //  * @return 返回控制状态
    //  * @retval 0 打开成功
    //  * @retval 1 打开失败
    // */
    // uint8_t smHumanSwitch(uint8_t sw);

    /**
     * @fn smHumanData
     * @brief 查询在睡眠模式下人体相关的内容
     * @param hm 获取数据内容选择
    */
    uint16_t smHumanData(esmHuman hm);

    /**
     * @fn smHumanLocation
     * @brief 获取人体方位数据
     * @param x X 坐标
     * @param y y 坐标
     * @param z Z 坐标
    */
    void smHumanLocation(int16_t *x, int16_t *y, int16_t *z);

    // /**
    //  * @fn smHeartRateSwitch
    //  * @brief 心率检测开关
    //  * @param sw 开关 1 打开 0 关闭
    //  * @return 返回控制状态
    //  * @retval 1 打开
    //  * @retval 0 关闭
    // */
    // uint8_t  smHeartRateSwitch(uint8_t sw);

    // /**
    //  * @fn getHeartRateSwitch
    //  * @brief 获取心率开关状态
    //  * @return 返回心率状态
    //  * @retval 1 打开
    //  * @retval 0 关闭
    // */
    // uint8_t getHeartRateSwitch(void);

    /**
     * @fn gitHeartRate
     * @brief 获取心率
     * @return 返回心率
    */
    uint8_t gitHeartRate(void);

    // /**
    //  * @fn smBreatheSwitch
    //  * @brief 呼吸检测开关
    //  * @param sw 开关控制 0 关闭 1 打开
    //  * @return 返回控制状态
    //  * @retval 0 关闭
    //  * @retval 1 打开
    // */
    // uint8_t smBreatheSwitch(uint8_t sw);

    // /**
    //  * @fn getBreatheSwitch
    //  * @brief 获取呼吸开关状态
    //  * @return 返回呼吸开关状态
    //  * @retval 0 关闭
    //  * @retval 1 打开
    // */
    // uint8_t getBreatheSwitch(void);

    /**
     * @fn getBreatheState
     * @brief 获取呼吸检测信息
     * @return 返回呼吸信息
     * @retval 1 正常
     * @retval 2 获取过快
     * @retval 3 获取过慢
     * @retval 4 无
    */
    uint8_t getBreatheState(void);

    /**
     * @fn getBreatheValue
     * @brief 获取呼吸数值
     * @return 返回呼吸数值
    */
    uint8_t getBreatheValue(void);

    // /**
    //  * @fn smSleepSwitch
    //  * @brief 睡眠检测功能开关
    //  * @param sw 开关控制 0 关 1 开
    //  * @return 返回控制状态
    //  * @retval 0 关闭
    //  * @return 1 打开
    // */
    // uint8_t smSleepSwitch(uint8_t sw);

    /**
     * @fn getSleepSwitch
     * @brief 获取睡眠相关数据
     * @param sl 需要获取的数据
     * @return 返回获取的数据
    */
    uint16_t smSleepData(eSmSleep sl);

    /**
     * @fn getSleepComposite
     * @brief 睡眠综合状态查询
     * @return 返回综合查询数据
    */
    sSleepComposite getSleepComposite(void);

    /**
     * @fn getSleepStatistics
     * @brief 睡眠统计状态查询
     * @return 返回睡眠统计数据
    */
    sSleepStatistics getSleepStatistics(void);

    /**
     * @fn configSleep
     * @brief 配置睡眠模式功能
     * @param sl 功能选择
     * @param data 配置数据
     * @return 返回设置状态
    */
    uint8_t configSleep(eSmSleepConfig sl,uint8_t data);

    /**
     * @fn installAngle
     * @brief 用于跌倒模式中雷达角度安装设置
     * @param x x 角度
     * @param y y 角度
     * @param z z 角度
    */
    void dmInstallAngle(int16_t x, int16_t y, int16_t z);

    /**
     * @fn dmGetInstallAngle
     * @brief 获取雷达安装角度
     * @param x x 角度
     * @param y y 角度
     * @param z z 角度
    */
    void dmGetInstallAngle(int16_t *x, int16_t *y, int16_t *z);

    /**
     * @fn dmInstallHeight
     * @brief 设置雷达安装高度
     * @param he 安装高度
    */
    void dmInstallHeight(uint16_t he);

    /**
     * @fn dmGetInstallHeight
     * @brief 获取安装高度
     * @return 返回获取的安装高度
    */
    uint16_t dmGetInstallHeight(void);

    /**
     * @fn autoMeasureHeight
     * @brief 获取自动测高数据
     * @return 返回自动测高数据
    */
    uint16_t dmAutoMeasureHeight(void);

    // /**
    //  * @fn dmHumanSwitch
    //  * @brief 跌倒模式下的人体存在开关
    //  * @param sw 开关数据 0 开，1 关
    // */
    // void dmHumanSwitch(uint8_t sw);

    /**
     * @fn dmHumanData
     * @brief 在跌倒模式下获取人体相关数据
    */
    uint16_t dmHumanData(eDmHuman dh);
    
    /**
     * @fn track
     * @brief 轨迹点查询
     * @param x x 坐标
     * @param y y 坐标
    */
    void track(uint16_t *x, uint16_t *y);

    /**
     * @fn trackFrequency
     * @brief 获取轨迹点上报频率
     * @return 返回轨迹点上报频率
    */
    uint32_t trackFrequency(void);

    /**
     * @fn unmannedTime
     * @brief 无人时间查询
    */
    uint32_t unmannedTime(void);

    // /**
    //  * @fn fallSwitch
    //  * @brief 跌倒模式开关
    //  * @param sw 控制跌倒模式 0 关 1 打开
    // */
    // void fallSwitch(uint8_t sw);

    /**
     * @fn getFallData
     * @brief 获取跌倒检测功能数据
     * @param dm 数据选择
     * @return 返回获取的数据
    */
    uint16_t getFallData(eDmFall dm);

    /**
     * @fn getFallTime
     * @brief 获取跌倒时长
     * @return 返回跌倒时长
    */
    uint32_t getFallTime(void);

    /**
     * @fn staticResidencyTime
     * @brief 驻留时长查询
     * @return 返回驻留时长
    */
    uint32_t staticResidencyTime(void);

    
    /**
     * @fn accumulatedHeightDuration
     * @brief 高度累计时间查询
     * @return 返回高度累计时间数据
    */
    uint32_t accumulatedHeightDuration(void);

    /**
     * @fn dmHumanConfig
     * @brief 配置跌倒模式下人体配置
     * @param con 配置选择
     * @param da 配置数据
     * @return 返回配置状态
     * @retval 1 配置失败
     * @retval 0 配置成功
    */
    uint8_t dmHumanConfig(eDmHumanConfig con,uint16_t data);

    /**
     * @fn unattendedTimeConfig
     * @brief 设置在跌倒模式下无人时间查询
     * @brief time 设置时间
     * @return 返回设置状态
     * @retval 0 成功
     * @retval 1 失败
    */
    uint8_t unattendedTimeConfig(uint32_t time);
    /**
     * @fn dmFallConfig
     * 
    */
    uint8_t dmFallConfig(eDmFallConfig con, uint32_t data);

private:
    /**
     * @fn getData
     * @brief 发送命令并获取数据
     * @param con 控制字
     * @param cmd 命令字
     * @param len 数据长度
     * @param senData 发送数据
     * @param retData 返回数据
     * @return 返回通信状态
     * @retval 0 通信正常
     * @retval 1 超时
     * @retval 2 通信异常
    */
    uint8_t getData(uint8_t con, uint8_t cmd, uint16_t len, uint8_t *senData, uint8_t *retData);
    uint8_t sumData(uint8_t len, uint8_t* buf);
    Stream *_s = NULL;
};

#endif
