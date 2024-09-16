#!/usr/bin/env python

# <soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
#     <soapenv:Body>
#         <ADD_KI>
#             <HLRSN>1</HLRSN>
#             <IMSI>{}</IMSI>
#             <OPERTYPE>ADD</OPERTYPE>
#             <KIVALUE>11111111111111111111111111111111</KIVALUE>
#             <CARDTYPE>SIM</CARDTYPE>
#             <ALG>COMP128_1</ALG>
#         </ADD_KI>
#     </soapenv:Body>
# </soapenv:Envelope>

import requests
import xmltodict
import base64

#host = '10.200.17.43'
host = '10.200.17.44'
username = 'WISPGATE'
password = 'Sw1ft@321'

imsi = '621260010212956' #'863456789102228'
msisdn = '2342601212956@msisdn'
isdn = '2342601212956'

def encode_auth():
    string = username+':'+password
    base64_bytes = base64.b64encode(string.encode("utf-8"))
    return base64_bytes.decode("utf-8")

def send_request(req_data):
    req_headers = {
        'Content-Type': "text/xml; charset=utf-8", 
        'Content-Length': "%d" % len(req_data), 
        'SOAPAction': 'Notification', 
        #'User-Agent': 'Jakarta Commons-HttpClient/3.1', 
        'Host': '{}:8080'.format(host),
    }
    #print(req_headers)
    
    #response = requests.get("http://{}:8080/axis/services/AdminService?wsdl".format(host), data=req_data, headers=req_headers, allow_redirects=False, timeout=100)
    response = requests.post("http://{}:8001/axis/services/ScfPccSoapServiceEndpointPort".format(host), data=req_data, headers=req_headers, allow_redirects=False, timeout=100)
    
    if response.status_code == 200:
        print(response.text)
        parsed = xmltodict.parse(response.text)
        return {'response': parsed['SOAP-ENV:Envelope']['SOAP-ENV:Body'], 'status': response.status_code}
    else: 
        print(response.headers, response.status_code)
        print(response.text)
    return {'response': response.text, 'status': response.status_code}



login_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><LGI><OPNAME>{}</OPNAME><PWD>{}</PWD></LGI></soapenv:Body></soapenv:Envelope>""".format(username, password)
logout_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><LGO></LGO></soapenv:Body></soapenv:Envelope>"""
add_ki_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><ADD_KI><HLRSN>1</HLRSN><IMSI>{}</IMSI><OPERTYPE>ADD</OPERTYPE><KIVALUE>11111111111111111111111111111111</KIVALUE>
<CARDTYPE>SIM</CARDTYPE><ALG>COMP128_1</ALG></ADD_KI></soapenv:Body></soapenv:Envelope>""".format(imsi)
rem_ki_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><RMV_KI><IMSI>{}</IMSI></RMV_KI></soapenv:Body></soapenv:Envelope>""".format(imsi)
chk_ki_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><CHK_KI><IMSI>{}</IMSI></CHK_KI></soapenv:Body></soapenv:Envelope>""".format(imsi)

add_sub_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><ADD_SUB><IMSI>{}</IMSI><ISDN>{}</ISDN><CARDTYPE>SIM</CARDTYPE><EPS>TRUE</EPS>
<AMBRMAXUL>1000000000</AMBRMAXUL><AMBRMAXDL>1000000000</AMBRMAXDL></ADD_SUB></soapenv:Body></soapenv:Envelope>""".format(imsi, isdn)
rem_sub_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><RMV_SUB><IMSI>{}</IMSI><RMVKI>TRUE</RMVKI></RMV_SUB></soapenv:Body></soapenv:Envelope>""".format(imsi)
mod_gprs_data = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><MOD_OPTGPRS><IMSI>{}</IMSI><PROV>ADDPDPCNTX</PROV><APN_TYPE>EPS_APN</APN_TYPE>
<APNTPLID>25</APNTPLID><DEFAULTCFGFLAG>TRUE</DEFAULTCFGFLAG><EPS_QOSTPLID>0</EPS_QOSTPLID><PDPTYPE>IPV4</PDPTYPE>
<ADDIND>DYNAMIC</ADDIND><VPLMN>TRUE</VPLMN><CHARGE>PREPAID</CHARGE></MOD_OPTGPRS></soapenv:Body></soapenv:Envelope>""".format(imsi)

add_psub_data_old = """<?xml version="1.0"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
<soapenv:Body><Notification><get><USRIDENTIFIER>{}</USRIDENTIFIER><USRMSISDN>{}</USRMSISDN><USRSTATE>Normal</USRSTATE>
</get></Notification></soapenv:Body></soapenv:Envelope>""".format(imsi, isdn)

add_psub_data = """<?xml version="1.0" encoding="UTF-8"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:rm="rm:soap">
<soapenv:Header/><soapenv:Body><rm:ADD_PSUB><USRIDENTIFIER>{}</USRIDENTIFIER><USRMSISDN>{}</USRMSISDN><USRSTATE>1</USRSTATE>
<USRPAIDTYPE>2147483646</USRPAIDTYPE><USRSTATION>1</USRSTATION><USRCONTACTMETHOD>SMS</USRCONTACTMETHOD></rm:ADD_PSUB></soapenv:Body></soapenv:Envelope>""".format(imsi, isdn)

rmv_psub_data = """<?xml version="1.0" encoding="UTF-8"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:rm="rm:soap">
<soapenv:Header/><soapenv:Body><rm:RMV_PSUB><USRIDENTIFIER>{}</USRIDENTIFIER><USRMSISDN>{}</USRMSISDN></rm:RMV_PSUB></soapenv:Body></soapenv:Envelope>""".format(imsi, isdn)

add_psrv_data = """<?xml version="1.0" encoding="UTF-8"?><soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:rm="rm:soap">
<soapenv:Header/><soapenv:Body><rm:ADD_PSRV><USRIDENTIFIER>{}</USRIDENTIFIER><SRVNAME>bras_5mbps_all_day</SRVNAME></rm:ADD_PSRV></soapenv:Body></soapenv:Envelope>""".format(imsi, isdn)




res = send_request(login_data)
if res['status'] == 200:
    result = res['response']['LGIResponse']['Result']
    if int(result['ResultCode']) == 0:
        print(result['ResultDesc'])
    else:
        print(result)

# res = send_request(logout_data)
# if res['status'] == 200:
#     print(res)
# res = send_request(rem_sub_data)
# if res['status'] == 200:
#     result = res['response']['RMV_SUBResponse']['Result']
#     print(result)

res = send_request(add_psub_data)
if res['status'] == 200:
    #result = res['response']['ADD_KIResponse']['Result']
    print(res)

res = send_request(add_psrv_data)
if res['status'] == 200:
    #result = res['response']['ADD_KIResponse']['Result']
    print(res)

# res = send_request(rem_ki_data)
# if res['status'] == 200:
#     print(res)

# res = send_request(chk_ki_data)
# if res['status'] == 200:
#     result = res['response']['CHK_KIResponse']['Result']
#     print(res)

# res = send_request(add_sub_data)
# if res['status'] == 200:
#     result = res['response']['ADD_SUBResponse']['Result']
#     print(result)

# res = send_request(mod_gprs_data)
# if res['status'] == 200:
#     result = res['response']['MOD_OPTGPRSResponse']['Result']
#     print(result)


