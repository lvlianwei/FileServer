#!/bin/bash

cd ../../../
out/host/linux-x86/bin/aidl -v -oframeworks/service/miracastservice frameworks/service/miracastservice/aidl/IWFDService.aidl
cd frameworks/service/miracastservice
