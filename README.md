AppleBacklightFixup
===================

Lilu plugin for enabling support for backlight using RehabMan's patches

### Downloads

RehabMan pre-built is on bitbucket: https://bitbucket.org/RehabMan/applebacklightfixup/downloads/

### Features
- No need Clover patch and `AppleBacklightInjector.kext`
- Work in Recovery and Installation

### Instruction
- Install this kext using your favorite method (Clover, /L/E, etc.) and put `SSDT-PNLF.aml` to `/EFI/CLOVER/ACPI/patched`

### Boot-args
- `-applbkloff` disables kext loading
- `-applbkldbg` turns on debugging output
- `-applbklbeta` enables loading on unsupported osx

### Downloads
Available on the [releases](https://github.com/hieplpvip/AppleBacklightFixup/releases) page.

#### Credits
- [Apple](https://www.apple.com) for macOS  
- [vit9696](https://github.com/vit9696) for [Lilu](https://github.com/acidanthera/Lilu)
- [RehabMan](https://www.tonymacx86.com/members/rehabman.429483/) for [the patch](https://www.tonymacx86.com/threads/guide-laptop-backlight-control-using-applebacklightinjector-kext.218222/)
- [hieplpvip](https://github.com/hieplpvip/) for writing the software and maintaining it
