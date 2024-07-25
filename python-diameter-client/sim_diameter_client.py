import binascii
import logging
import sys
from time import sleep
from diameter import ProtocolConstants, Message, AVP, AVP_Unsigned32, AVP_UTF8String
from diameter.node import SimpleSyncClient, Capability, NodeSettings, Peer

peer = "10.65.6.251"
port = 3868
host_id = "gy.test.swiftng.com"
realm = "swiftng.com"

# Capabilities-Exchange-Request(257)[R---], Length=276, Hop-By-Hop-Id=0x00136def, End-to-End=0x00136def, 
# { Origin-Host(264)[-M]="gy.ugw02.swiftng.com" }, 
# { Origin-Realm(296)[-M]="swiftng.com" }, 
# { Host-IP-Address(257)[-M]=10.200.21.74 }, 
# { Vendor-Id(266)[-M]=10415 (0x28af) }, 
# { Product-Name(269)[--]="UGWV9" }, 
# { Inband-Security-Id(299)[-M]='NO_INBAND_SECURITY' (0 (0x0)) }, 
# { Auth-Application-Id(258)[-M]=4 (0x4) }, 
# { Vendor-Specific-Application-Id(260)[-M]={ Vendor-Id(266)[-M]=10415 (0x28af) }, { Auth-Application-Id(258)[-M]=16777223 (0x1000007) } }, 
# { Vendor-Specific-Application-Id(260)[-M]={ Vendor-Id(266)[-M]=10415 (0x28af) }, { Auth-Application-Id(258)[-M]=16777238 (0x1000016) } }, 
# { Vendor-Specific-Application-Id(260)[-M]={ Vendor-Id(266)[-M]=10415 (0x28af) }, { Auth-Application-Id(258)[-M]=16777266 (0x1000032) } }, 
# { Vendor-Specific-Application-Id(260)[-M]={ Vendor-Id(266)[-M]=10415 (0x28af) }, { Auth-Application-Id(258)[-M]=16777272 (0x1000038) } }, 
# { Firmware-Revision(267)[--]=0 (0x0) }

# Capabilities-Exchange-Request(257)[R---], Length=192, Hop-By-Hop-Id=0xf94ae7c6, End-to-End=0xf41d71e9, 
# { Origin-Host(264)[-M]="gy.test.swiftng.com" }, 
# { Origin-Realm(296)[-M]="wispgate.io" }, 
# { Host-IP-Address(257)[-M]=10.65.6.249 }, 
# { Vendor-Id(266)[-M]=10415 (0x28af) }, 
# { Product-Name(269)[--]="cc_test_client" }, 
# { Origin-State-Id(278)[-M]=1721691969 (0x669eef41) }, 
# { Auth-Application-Id(258)[-M]=0 (0x0) }, 
# { Auth-Application-Id(258)[-M]=4 (0x4) }, 
# { Acct-Application-Id(259)[-M]=0 (0x0) }, 
# { Acct-Application-Id(259)[-M]=4 (0x4) }, 
# { Firmware-Revision(267)[--]=1 (0x1) }


cap = Capability()
cap.addAuthApp(ProtocolConstants.DIAMETER_APPLICATION_COMMON)
cap.addAcctApp(ProtocolConstants.DIAMETER_APPLICATION_COMMON)

cap.addAuthApp(ProtocolConstants.DIAMETER_APPLICATION_CREDIT_CONTROL)
cap.addAcctApp(ProtocolConstants.DIAMETER_APPLICATION_CREDIT_CONTROL)

cap.addVendorAuthApp(10415, 4)

settings = NodeSettings(host_id, realm, 10415, cap, 3869, "cc_test_client", 1)

ssc = SimpleSyncClient(settings,[Peer(peer,port)])
ssc.node.logger.setLevel(level=logging.INFO)
ssc.start()
ssc.waitForConnection(timeout=5)

req = Message()
# < Diameter Header: 272, REQ, PXY >
req.hdr.command_code = ProtocolConstants.DIAMETER_COMMAND_CC
req.hdr.application_id = ProtocolConstants.DIAMETER_APPLICATION_CREDIT_CONTROL
req.hdr.setRequest(True)
#req.hdr.setProxiable(True)

# < Session-Id >
req.append(AVP(ProtocolConstants.DI_SESSION_ID,ssc.node.makeNewSessionId()))

# { Origin-Host }
# { Origin-Realm }
ssc.node.addOurHostAndRealm(req)

# { Destination-Realm }
req.append(AVP_UTF8String(ProtocolConstants.DI_DESTINATION_HOST,"swift.wispgate.io"))
# { Destination-Realm }
req.append(AVP_UTF8String(ProtocolConstants.DI_DESTINATION_REALM,"wispgate.io"))
# { Auth-Application-Id }
req.append(AVP_Unsigned32(ProtocolConstants.DI_AUTH_APPLICATION_ID, ProtocolConstants.DIAMETER_APPLICATION_CREDIT_CONTROL)) # a lie but a minor one
# { Acc-Application-Id }
req.append(AVP_Unsigned32(ProtocolConstants.DI_ACCT_APPLICATION_ID, ProtocolConstants.DIAMETER_APPLICATION_CREDIT_CONTROL)) # a lie but a minor one
# { Service-Context-Id }
req.append(AVP_UTF8String(ProtocolConstants.DI_SERVICE_CONTEXT_ID,"cc_test@example.net"))
# { CC-Request-Type }
req.append(AVP_Unsigned32(ProtocolConstants.DI_CC_REQUEST_TYPE,ProtocolConstants.DI_CC_REQUEST_TYPE_INITIAL_REQUEST))
# { CC-Request-Number }
req.append(AVP_Unsigned32(ProtocolConstants.DI_CC_REQUEST_NUMBER,5009))
# { Inband-Security-Id }
req.append(AVP_Unsigned32(ProtocolConstants.DI_INBAND_SECURITY_ID,ProtocolConstants.DI_INBAND_SECURITY_ID_NO_INBAND_SECURITY))

# [ Destination-Host ]
# [ User-Name ]
req2 = Message()
req2.append(AVP_UTF8String(ProtocolConstants.DI_SUBSCRIPTION_ID_DATA,"2349056090009"))
req2.append(AVP_Unsigned32(ProtocolConstants.DI_SUBSCRIPTION_ID_TYPE,ProtocolConstants.DI_SUBSCRIPTION_ID_TYPE_END_USER_IMSI))
req.append(AVP(ProtocolConstants.DI_SUBSCRIPTION_ID, req2))

# setMandatory_RFC3588(req)
# setMandatory_RFC4006(req)
while True:
    sleep(2)
    print("Request data:", req.find(ProtocolConstants.DI_INBAND_SECURITY_ID))
    res = ssc.sendRequest(req)
    #res = None    
    print("Response data:", str(res))

    if res is None:
        print("__NO RESPONSE__")
    else:
        for avp in res.avp:
            print("avp:", str(avp))

        raw_code = res.find(ProtocolConstants.DI_RESULT_CODE).payload
        code = int(binascii.b2a_hex(raw_code).decode('utf-8'), 16)
        if code == ProtocolConstants.DIAMETER_RESULT_SUCCESS:
            print("SUCCESS")

        session_id = res.find(ProtocolConstants.DI_SESSION_ID).payload.decode('utf-8')
        origin_host = res.find(ProtocolConstants.DI_ORIGIN_HOST).payload.decode('utf-8')
        origin_realm = res.find(ProtocolConstants.DI_ORIGIN_REALM).payload.decode('utf-8')

        print("Result Code %s session_id %s origin host %s origin_realm %s" % (code, session_id, origin_host, origin_realm))
    sleep(5)