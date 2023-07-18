@ECHO off

CLS
REM ECHO ### CHANGE_IP TO 192.168.1.220 ###



:start
GOTO check_admin


:check_admin
net session > nul 2>&1
IF %errorlevel% neq 0 (
	GOTO end_notadmin
) ELSE (
	GOTO get_ipv4
)


:get_ipv4
SETLOCAL enabledelayedexpansion
FOR /f "tokens=2 delims=:" %%a IN ('ipconfig ^| findstr /c:"IPv4 Address"') DO SET "ip=%%a"
SET IPV4_ADDR=%ip:~1%

IF "%IPV4_ADDR%"=="192.168.1.220" (
	ECHO ### CHANGE IP TO AUTOMATIC ###
	GOTO set_dhcp
) ELSE (
	ECHO ### CHANGE IP TO 192.168.1.220 ###
	GOTO set_static
)


:set_dhcp
netsh interface ipv4 set address name="Wi-Fi" source=dhcp > nul 2>&1
netsh interface ipv4 set dnsservers name="Wi-Fi" source=dhcp > nul 2>&1
goto end_dhcp


:set_static
netsh interface ipv4 set address name="Wi-Fi" static 192.168.1.220 255.255.255.0 192.168.1.1 > nul 2>&1
netsh interface ipv4 add dnsserver name="Wi-Fi" address=8.8.8.8 index=1 validate=no > nul 2>&1
netsh interface ipv4 add dnsserver name="Wi-Fi" address=8.8.4.4 index=2 validate=no > nul 2>&1
goto end_static


:end_dhcp
ECHO IPv4 changed to automatic.
ECHO Subnet Mask changed to automatic.
ECHO Default Gateway changed to automatic.
ECHO DNS-1 changed to DHCP.
ECHO DNS-2 changed to DHCP.
GOTO end


:end_static
ECHO IPv4 changed to 192.168.1.220
ECHO DNS changed to 8.8.8.8
ECHO DNS changed to 8.8.4.4
GOTO end


:end_notadmin
ECHO This script must have administrator privileges.


:end
PAUSE
ENDLOCAL