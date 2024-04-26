Welcome to the BrainVision AmplifierSDK

SDK programming functionality is documented in the C:\Vision\Amplifier SDK\Docs folder and by example applications in the folder C:\Vision\Amplifier SDK\Samples. Inside you will find two projects. One is called BasicExample and demonstrates the basic functions of the SDK in a command line app. The other is called PropertyBrowesr and this demonstrates a complete GUI (based on MFC widgets) built around the setup of actiCHamp or LiveAmp.

In order to use this SDK, your project must include the file C:\Vision\Amplifier SDK\SDK.h and reference the files ending in .lib in the folder C:\Vision\Amplifier SDK\Bin\Win32 or C:\Vision\Amplifier SDK\Bin\x64.

After compiling, your application will need to reference all the files ending in .dll and .bit for the appropriate architecture found in C:\Vision\Amplifier SDK\Bin. This can be done by either copying the folders into the same directory as your application or else making use of system environment variables.

For licensing information please see the enclosed software license included in this distribution: C:\Vision\Amplifier SDK\LicensingTerms_BrainVision_Amplifier-SDK.pdf. A copy of the license is also available online:
https://www.brainproducts.com/downloads.php?kid=34.

Release Notes:

Version 1.1.0.2

-New Features:
--SetChannelLabels method added to SDK

-Bug Fixes:
--re-start recording bug fixed
--send triggers using SetProperty

-Miscellaneous:
--Triggers example showing how to handle input and output triggering
