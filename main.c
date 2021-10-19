#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psppower.h>

PSP_MODULE_INFO("psp-sys", 0, 1, 0);
 
int exit_callback(int arg1, int arg2, void* common){
	sceKernelExitGame();
	return 0;
}
 
int CallbackThread(SceSize args, void* argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
 
	return 0;
}
 
int SetupCallbacks(void) {
	int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if (thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}
int main() { 
    
    int battery_temp, battery_voltage, battery_charging, battery_remaining_time, battery_percentage; // battery variables
    int cpu_frequency = scePowerGetCpuClockFrequency();
    int bus_frequency = scePowerGetBusClockFrequency();
    struct SceCtrlData padData;

    SetupCallbacks();
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    pspDebugScreenClear();
    pspDebugScreenPrintf("\n--------- PSP SYSTEM SYSTEM INFO BY INTHECATSDREAMS ---------\n");
    
    if (scePowerIsBatteryExist() == 1) {
        battery_temp = scePowerGetBatteryTemp();
        battery_voltage = scePowerGetBatteryVolt();
        battery_charging = scePowerIsBatteryCharging();
        battery_remaining_time = scePowerGetBatteryLifeTime();
        battery_percentage = scePowerGetBatteryLifePercent();
    }

    if (scePowerIsBatteryExist() == 0){
        pspDebugScreenPrintf("No battery was detected\n");
    }
    else {
        pspDebugScreenPrintf("Battery temperature: %d C\n", battery_temp);
        pspDebugScreenPrintf("Battery voltage: %d v\n", battery_voltage);
        pspDebugScreenPrintf("Remaining battery time: %d minutes\n", battery_remaining_time);
        pspDebugScreenPrintf("Battery percentage: %d\n", battery_percentage);
    }
    pspDebugScreenPrintf("CPU Clock: %d Mhz\n", cpu_frequency);
    pspDebugScreenPrintf("BUS Clock: %d Mhz\n", bus_frequency);
    

    pspDebugScreenPrintf("\n\n\nPress START to refresh values.\n");
    
    

    while(1){
        sceCtrlReadBufferPositive(&padData,1);
 
        if(padData.Buttons & PSP_CTRL_START){
            pspDebugScreenPrintf("Refreshing values.");
            sceKernelDelayThread(2 * 100000);
            main();
        }

    }

}
