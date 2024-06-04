# -*- coding:utf-8 -*-
'''!
 @file basics.ino
 @brief 这是人体毫米波雷达的基础使用例程
 @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 @license     The MIT License (MIT)
 @author [tangjie](jie.tang@dfrobot.com)
 @version  V1.0
 @date  2024-06-03
 @url https://github.com/DFRobot/DFRobot_HumanDetection
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time

from DFRobot_HumanDetection import *

hu = DFRobot_HumanDetection()

def setup():
    while hu.begin() != 0:
        print("init error!!!\n")
        time.sleep(1)
    print("init success\n")
    while (hu.config_work_mode(SleepMode) != 0):
       print("init error\n")
       time.sleep(1)
    print("init success")
    work_mode = hu.get_workmode()
    if work_mode == 1:
       print("跌倒模式\n")
    elif work_mode == 2:
       print("睡眠模式\n")
    else:
       print("读取错误\n")
    hu.config_LED_light(HPLed, 1)
    led_mode = hu.get_LED_light_state(HPLed)
    if led_mode == 0:
       print("关\n")
    elif led_mode == 1:
       print("开\n")
    else:
       print("读取错误\n")



  
def loop():
    print("存在信息：")
    hu_data = hu.sm_human_data(eHumanPresence)
    if hu_data == 0:
       print("无人存在\n")
    elif hu_data == 1:
       print("有人存在\n")
    else:
       print("读取错误\n")
    print("运动信息：")
    hu_data = hu.sm_human_data(eHumanMovement)
    if hu_data == 0:
       print("无\n")
    elif hu_data == 1:
       print("静止\n")
    elif hu_data == 2:
       print("活跃\n")
    else:
       print("读取错误\n")
     

if __name__ == "__main__":
  setup()
  while True:
    loop()