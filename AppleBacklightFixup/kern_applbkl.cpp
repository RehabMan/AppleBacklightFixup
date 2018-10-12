//
//  kern_applbkl.cpp
//  AppleBacklightFixup
//
//  Copyright © 2018 hieplpvip. All rights reserved.
//

#include <Headers/kern_api.hpp>
#include <Headers/kern_util.hpp>
#include "kern_applbkl.hpp"

static const char *kextId { "com.apple.driver.AppleBacklight" };
static const char *kextPath[] {
    "/System/Library/Extensions/AppleBacklight.kext/Contents/MacOS/AppleBacklight" };

static KernelPatcher::KextInfo kext { kextId, kextPath, 1, {true, true}, {}, KernelPatcher::KextInfo::Unloaded };

bool APPLBKL::init() {
	LiluAPI::Error error = lilu.onKextLoad(&kext, 1,
	[](void *user, KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
		static_cast<APPLBKL *>(user)->processKext(patcher, index, address, size);
    }, this);
	
	if (error != LiluAPI::Error::NoError) {
		SYSLOG("applbkl", "failed to register onPatcherLoad method %d", error);
		return false;
	}
	
	return true;
}

void APPLBKL::deinit() {}

void APPLBKL::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
    if (progressState != ProcessingState::EverythingDone) {
        if (kext.loadIndex == index) {
            DBGLOG("applbkl", "found %s", kext.id);
            const uint8_t find[]    = { 0x46, 0x25, 0x75, 0x54, 0x25, 0x30, 0x34, 0x78, 0x00 };
            const uint8_t replace[] = { 0x46, 0x25, 0x75, 0x54, 0x78, 0x78, 0x78, 0x78, 0x00 };
            KernelPatcher::LookupPatch patch = {&kext, find, replace, sizeof(find), 0};
            //if (patcher.compatibleKernel(KernelVersion::Sierra, KernelVersion::Mojave))
            {
                DBGLOG("applbkl", "applying patch");
                patcher.applyLookupPatch(&patch);
            }
            DBGLOG("applbkl", "AppleBacklight patch was applied");
            progressState |= ProcessingState::AppleBacklightPatched;
        }
    }
    
    // Ignore all the errors for other processors
    patcher.clearError();
}
