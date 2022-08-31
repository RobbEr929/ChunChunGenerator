## Overview
A small tool based on Qt for implementing named camel case conversion.
The project is built based on Qt5.12.10_msvc2017_64 + VS2022
## Version
### V0.0.4
**Todo**: update notes
### V 0.0.3
1. Implement `big hump`, `small hump`, `all uppercase`, `all lowercase`, `add underscore`, `add prefix`, `add suffix`, `underline tolerance (do not delete underscore)` and other strings transform;
2. `Focus and Paste`: When selected, each time you enter the application, the content of the clipboard will be directly copied to the input box;
3. `Multi-line input`: You can select multiple lines of input to generate multiple results at one time;
4. `Complete and copy`: When selected, the generated string will be automatically copied to the clipboard;
5. `Click and copy`: When this and multi-line input are selected, directly clicking on a result will directly copy the item to the clipboard;
6. `Top window`, `Minimize to tray` and other functions;
7. `Virtual focus fade out`: When the mouse is not in the software, the software is translucent, and the transparency can be set by yourself;
8. `Multi-theme support`: Including light and dark themes (Supported by [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet), MIT LICENSE);
9. `Multilingual support`: Simplified Chinese and English are currently supported;
10. `Shortcut key bindings`: All operations can be bound to shortcut keys, which will be available when you use them next time (Supported by [QHotkey](https://github.com/Skycoder42/QHotkey), BSD LICENSE).
## Lisence
[MPL 2.0](https://www.mozilla.org/en-US/MPL/2.0/)