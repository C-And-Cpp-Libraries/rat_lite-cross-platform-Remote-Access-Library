#pragma once
#include <string>
#include <memory>
#include "Input.h"
#include "Logging.h"
#include "Shapes.h"
#include "ISocket.h"
#include "ICryptoLoader.h"
#include "INetworkHandlers.h"

namespace SL {
	namespace RAT {



#if defined(DEBUG)  || defined(_DEBUG) || !defined(NDEBUG)

		//THIS SHOULD ONLY BE USED IN DEBUG MODE FOR EASE OF TESTING!!!!
		//DO NOT USE THIS IN PRODUCTION!!
		const char public_cert[] = R"(-----BEGIN CERTIFICATE-----
MIIEaDCCAtCgAwIBAgIBADANBgkqhkiG9w0BAQ0FADA3MRowGAYDVQQKDBFUZXN0
IENvbXBhbnkgTmFtZTEZMBcGA1UEAwwQVGVzdCBDb21tb24gTmFtZTAeFw0xNjA1
MzAwMjA1MzRaFw0xNzA1MzAwMjA1MzRaMDcxGjAYBgNVBAoMEVRlc3QgQ29tcGFu
eSBOYW1lMRkwFwYDVQQDDBBUZXN0IENvbW1vbiBOYW1lMIIBojANBgkqhkiG9w0B
AQEFAAOCAY8AMIIBigKCAYEA1E7RvjjPxjo85frpN6lBOW5bK3ZXfr1lsx609001
xUXz7/aX9j+to8GkOqyGapfeidg2E6WMK4HiBCiqO9Zba3EDMEGoppQJ6ntR2zIZ
SYOZfnIWyZQesC5BaL2ha5h96PVC2vYsEAglqYzrc1dvxFx0EA2EArabFcW/l5nS
ztAACGPr/LCsDSMcbLzFO6SDSPCuRaOTUzbzz5mfcarFib6B35OHK/TvqCBH0/Ev
FfCgJL4IgsglvhN7TXht8f/s0NQtsFPFA3g4t7byrxPJKkKgVWhtxOUcKdkTKmqj
c+EsF+punJJ8egXdP4nJ74Corpx0BNHPHnkJUk8ptYrZiHRGU1UqjdA1VdT19Zdu
O7KBCTfL/TaXbVxrhZIRMmoOMZfxqznZ4tNiyOOPxbNOFr1Du13XFXrOrJBkm21t
5sN42hTfmQy6hv7squwidjcEWcsKpbKkbJV7CWEr3HZSZwvn679FWwrzEwJwE5sw
O2W8I3zay62KgEBAEHyNiKGbAgMBAAGjfzB9MA8GA1UdEwEB/wQFMAMBAf8wDgYD
VR0PAQH/BAQDAgEGMB0GA1UdDgQWBBQCXy9tA++sUxkDnnLhypnVqKqwWjARBglg
hkgBhvhCAQEEBAMCAgQwKAYJYIZIAYb4QgENBBsWGWV4YW1wbGUgY29tbWVudCBl
eHRlbnNpb24wDQYJKoZIhvcNAQENBQADggGBAE5wQrvWslZ1W3wlcgSEx4dhe7xJ
P8QcDR56FldEDL50VfcPPMkkm1b3t7OmhC+oo64MFRD/c/dNTtMMq4fWc4g3Laap
rOX6iTgXxfK4JpwFWf+dOazrEBThf3MhV7uQJZeuMr2WSJXCS5Lw9mTd8Q/nK5AB
BZDY0dCwTIGQA1a/p+PZ6ZJMt4GUJuy6rN7Qc8ihRrMx+lp3JUxgVDHJ7feZASNG
2pM/UsuDCvNagyr5A58n/gwdW164UNZHXb6WYoBhRh2Q13wBI2Ejuse8xlvL5vEV
WMUils+cKTzb7wo3fcu/llVcuFhr9z0CfbgK2aiylARJB3xwgPpyb6Qe3+q1foKw
fdu+Rwo59fmX4dsTkySs7ZTKC4VSChAM0ac2RxSCRvPcqkHxxezrk/t+XDL6wSsL
glN6yxU1w+vsYbiayCK4Pl9SHhd9yzx1Li5XYtTmjcIieTa+tmv9IR5cltMqCoSw
ZydqCFmG4VbNpR42y+zIk8vcpJ8Y3u5xQJV3Lg==
-----END CERTIFICATE-----)";

		//THIS SHOULD ONLY BE USED IN DEBUG MODE FOR EASE OF TESTING!!!!
		//DO NOT USE THIS IN PRODUCTION!!
		const char private_key[] = R"(-----BEGIN ENCRYPTED PRIVATE KEY-----
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
dHEcfRl35ANQC0j95KsdzTw/Cg==
-----END ENCRYPTED PRIVATE KEY-----)";
		//THIS SHOULD ONLY BE USED IN DEBUG MODE FOR EASE OF TESTING!!!!
		//DO NOT USE THIS IN PRODUCTION!!
		const std::string private_key_password = "Test pass";

#endif

		class ICryptoLoader;
		struct Client_Config {

			//both the viewer and web client communicate over web sockets.
			unsigned short HttpTLSPort = 8080;
			unsigned short WebSocketTLSLPort = 6001;
			unsigned int Read_Timeout = 5;//in seconds
			unsigned int Write_Timeout = 5;//in seconds
			bool Share_Clipboard = true;//share your clipboard?
			bool Scale_Image = false;

			std::shared_ptr<ICryptoLoader> Public_Certficate;
		};

		struct Server_Config : Client_Config {

			//this is where files are issued out for the webserver. If no path is specified, wwwroot in applications directory is chosen as a default
			std::string WWWRoot;

			int MousePositionCaptureRate = 50;// measured in ms
			int ScreenImageCaptureRate = 100;// measured in ms

											 //Image Settings
			bool SendGrayScaleImages = false;//this will improve bandwith usage
			int ImageCompressionSetting = 70;// this is [0, 100]    = [WORST, BEST]

			bool IgnoreIncomingMouseEvents = false;
			bool IgnoreIncomingKeyboardEvents = false;

			size_t MaxWebSocketThreads = 2;//
			int MaxNumConnections = 10;//

									   //CRYPTO SETTINGS
			std::shared_ptr<ICryptoLoader> Private_Key;
			std::string PasswordToPrivateKey;
		};
	}
}