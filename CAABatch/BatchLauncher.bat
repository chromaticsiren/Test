echo off
echo =======================================================================
echo 	                    Batch Execution
echo =======================================================================
set CurrentFolder=%cd%

set InstallationFolder= "C:\\Program Files\\Dassault Systemes\\B419"
set Repository=         "PLM1"
set ServerName=         "gczc51035d4e.logon.ds.ge.com"
set ServerPort=         "8070"
set ServerRootURI=      "internal"

rem    Copy this address in an Internet browser: https://ve4al630dsy.ux.dsone.3ds.com/3DSpace/common/emxNavigator.jsp
set LoginTicket="Mjg2N0ZBNTM5RUY2NDdBOTkyNzdGMkMyQTAyQTZBMDl8OTk5OTAxMDAxfDk5OTkwMTAwMXx8fDB8"

%InstallationFolder%\\win_b64\\code\\bin\\CATSTART.exe -run "%CurrentFolder%\win_b64\code\bin\CAABatch %Repository% %ServerName% %ServerPort% %ServerRootURI% %LoginTicket% "
