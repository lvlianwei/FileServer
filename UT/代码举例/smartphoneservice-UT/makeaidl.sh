#!/bin/bash

cd ../../../
out/host/linux-x86/bin/aidl -v -oframeworks/service/smartphoneservice frameworks/service/smartphoneservice/aidl/ISMTService.aidl
cd frameworks/service/smartphoneservice
