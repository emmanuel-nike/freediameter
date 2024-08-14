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

host = '10.200.20.38'
username = 'WISPGATE'
password = 'Sw1ft@321'

imsi = '621260010212956' #'863456789102228'
msisdn = '2342601212956@msisdn'
isdn = '2342601212956'

def send_request(req_data):
    req_headers = {
        'Content-Type': "text/xml; charset=utf-8", 
        'Content-Length': "%d" % len(req_data), 
        'SOAPAction': 'Notification', 
        #'User-Agent': 'Jakarta Commons-HttpClient/3.1', 
        'Host': '{}:8001'.format(host)
    }
    response = requests.post("http://{}:8001".format(host), data=req_data, headers=req_headers, allow_redirects=False, timeout=100)
    
    if response.status_code == 200:
        parsed = xmltodict.parse(response.text)
        return {'response': parsed['SOAP-ENV:Envelope']['SOAP-ENV:Body'], 'status': response.status_code}
    else: 
        print(response.headers, response.status_code)
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

#ADD SUB: HLRSN =2, IMSI="435670998956956", ISDN="9876534345", CARDTYPE=USIM, TS=TS11&TS21;
#RMV SUB: ISDN="13623456789", RMVKI=TRUE;
#MOD OPTGPRS: IMSI="621260010212998", PROV=ADDPDPCNTX, APN_TYPE=EPS_APN, APNTPLID=25, DEFAULTCFGFLAG=TRUE, EPS_QOSTPLID=0, PDPTYPE=IPV4, ADDIND=DYNAMIC, VPLMN=TRUE, CHARGE=PREPAID;

# res = send_request(login_data)
# if res['status'] == 200:
#     result = res['response']['LGIResponse']['Result']
#     if int(result['ResultCode']) == 0:
#         print(result['ResultDesc'])
#     else:
#         print(result)

# res = send_request(logout_data)
# if res['status'] == 200:
#     print(res)
res = send_request(rem_sub_data)
if res['status'] == 200:
    result = res['response']['RMV_SUBResponse']['Result']
    print(result)

res = send_request(add_ki_data)
if res['status'] == 200:
    result = res['response']['ADD_KIResponse']['Result']
    print(result)

# res = send_request(rem_ki_data)
# if res['status'] == 200:
#     print(res)

# res = send_request(chk_ki_data)
# if res['status'] == 200:
#     result = res['response']['CHK_KIResponse']['Result']
#     print(res)

res = send_request(add_sub_data)
if res['status'] == 200:
    result = res['response']['ADD_SUBResponse']['Result']
    print(result)

res = send_request(mod_gprs_data)
if res['status'] == 200:
    result = res['response']['MOD_OPTGPRSResponse']['Result']
    print(result)


