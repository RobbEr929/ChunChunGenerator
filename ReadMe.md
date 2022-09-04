﻿﻿## Overview
A small tool based on Qt for implementing named camel case conversion.
The project is built based on Qt5.12.10_msvc2017_64 + VS2022

## Version
### V 0.0.5

**Todo**: update code notes

### V 0.0.4

1. Implement `UpperCamelCase`, `LowerCamelCase`, `all upper`, `all lower`, `add underscore`, `add prefix`, `add suffix`, `underline tolerance (do not delete underline)` and other strings transform;
2. `Focus and Paste`: When selected, each time you enter the application, the content of the clipboard will be directly copied to the input box;
3. `Multi-line input`: You can select multiple lines of input to generate multiple results at one time;
4. `Complete and copy`: When selected, the generated string will be automatically copied to the clipboard;
5. `Click and copy`: When this and multi-line input are selected, directly clicking on a result will directly copy the item to the clipboard;
6. `Top window`, `Minimize to tray` and other functions;
7. `Virtual focus fade out`: When the mouse is not in the software, the software is translucent, and the transparency can be set by yourself;
8. `Multi-theme support`: Including light and dark themes (Supported by [QDarkStyleSheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet), MIT LICENSE);
9. `Multilingual support`: Simplified Chinese and English are currently supported;
10. `Shortcut key bindings`: All operations can be bound to shortcut keys, which will be available when you use them next time (Supported by [QHotkey](https://github.com/Skycoder42/QHotkey), BSD LICENSE);
10.  `Update help`: when the local file exists, view the local help, if it does not exist, use the browser to view the network help;

## use

### Generator

- Input box: Enter the string to be converted into it;
- Output box: The converted string will be displayed in this box;
- Small hump button: When selected, the content of the input box will be converted into a small hump style;
- Big camel case button: When selected, the content of the input box will be converted into a big camel case style;
- All lowercase button: When selected, the content of the input box will be converted to all lowercase;
- All caps button: When selected, the content of the input box will be converted to all caps;
- Capitalize the first word button: When selected, the content of the input box will be converted into the capitalization style of the first word;
- Add underline button: When selected, an underline will be added to the input box as a separation;
- Underline Allowed: When selected, the underline of the content in the input box will not be deleted (deleted by default);
- Add prefix: will add a prefix to the content of the input box after it has been converted;
- Add suffix: After the content of the input box is converted, a suffix will be added to it;
- Generate button: will perform a response action according to the selected button;

### Option

#### general

- Paste when get focus: When selected, when you click Apply, the content of the clipboard will be automatically pasted into the input box;
- Copy to clipboard when work over: After selecting, when the text is generated, the generated text will be automatically copied to the clipboard;
- Minimize to tray when close: When selected, clicking close will minimize to tray instead of exiting;
- Window top hint : When selected, it will be the top window;
- Multiline input: After selecting, the input and output boxes will become multi-line, and multiple texts can be operated at the same time;
- Copy to clipboard when click output view: It can only be selected after multiple lines of text are selected. After selecting, when an item of the generated text is clicked, the item will be copied to the clipboard;

#### individuation

- Defocus transparency: You can condition the transparency when the mouse is not in the application, the range is 10%-100%;
- Theme: You can switch between light and dark themes, which will take effect immediately;
- Language: You can switch between Chinese and English languages, and it will take effect after restarting;

#### shortcut keys

- Local shortcut keys: You can bind all buttons in the generation interface except the generation button. When in the application, you can directly use the shortcut keys to switch the generation format;
- Global shortcut keys: `Generate`, `Show or hide` and `Exit` operations can be bound;
  - Generate: It can be generated with one key according to the current option, such as the binding key `Ctrl+G`, you can use the following operations to quickly modify the name of the target string
  - When `Automatically copy to clipboard when finished` is selected in the general options, hold down `Ctrl`, press `C`, `G`, `v`, you can directly modify the style with one click;
  - Show or hide : You can quickly show or hide applications;
  - Exit : exit directly;
- Save settings : After exiting normally, the shortcut keys are still saved the next time you enter;

### about

- Application and copyright information : application icon, name, version info and copyright;
- Help : when the local help file exists, open the local help file, when it does not exist, open the network help file through the browser;

## License

[MPL 2.0](https://www.mozilla.org/en-US/MPL/2.0/)