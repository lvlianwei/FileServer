#!/bin/bash


adb push ../../../out/target/product/Gerda15s/system/bin/wfdService /system/bin
adb push ../../../out/target/product/Gerda15s/system/lib/libwfdServiceproxy.so /system/lib
adb push ../../../out/target/product/Gerda15s/system/lib/libwfdServicesub.so /system/lib
adb push ../../../out/target/product/Gerda15s/system/bin/tstWfdProxy /system/bin
