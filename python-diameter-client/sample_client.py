#!/usr/bin/env python

"""
Sample Diameter Client, which can be used for testing purposes.
Generates a client instance, starts it, establishing the server connection
and then sends the specified Diameter Requests and interprets the response.
"""

from time import sleep
from diameter_client import *
from diameter_server import *

def send_req(client):
    # Generating a standard Diameter request
    generic_request = client.generate_generic_request(
        diameter_base.cmd_codes['Capability-Exchange'])

    cer_header = generic_request['header']
    cer_avps = generic_request['avps']

    # Appending the CER specific AVPs
    cer_avps.append(encodeAVP('Host-IP-Address', '10.65.6.249'))
    cer_avps.append(encodeAVP('Session-Id', 'ee136d75e131a132f558'))
    cer_avps.append(encodeAVP('Product-Name', diameter_base.standard_avp_values['Product-Name']))
    cer_avps.append(encodeAVP('Vendor-Id', diameter_base.standard_avp_values['Vendor-Id']))
    cer_avps.append(encodeAVP('Auth-Application-Id', DIAMETER_APPLICATION_CREDIT_CONTROL))
    cer_avps.append(encodeAVP('Service-Context-Id', '32252@3gpp.org'))
    cer_avps.append(encodeAVP('CC-Request-Type', DI_CC_REQUEST_TYPE_INITIAL_REQUEST)) #Initial Request
    cer_avps.append(encodeAVP('CC-Request-Number', 1)) #Initial Request
    cer_avps.append(encodeAVP('Subscription-Id', [
        encodeAVP('Subscription-Id-Type', DI_SUBSCRIPTION_ID_TYPE_END_USER_E164),
        encodeAVP('Subscription-Id-Data', '2342600064591')
    ]))
    cer_avps.append(encodeAVP('Multiple-Services-Indicator', DI_MULTIPLE_SERVICES_INDICATOR_MULTIPLE_SERVICES_SUPPORTED))
    cer_avps.append(encodeAVP('Multiple-Services-Credit-Control', [
        encodeAVP('Rating-Group', 100),
    ]))

    # returning a dictionary of the received AVPs
    # print("\n"+str(cer_header) + "  ==  " + str(cer_avps))
    cer_header.appId = 4
    avps_dict = client.send_diameter_request(cer_header, cer_avps, client.connection)
    return avps_dict

if __name__ == '__main__':
    """
    The main method for the client,
    which simulates basic interaction with the server.
    """

    # Starting the client
    client = DiameterClient('10.65.6.251', 3868, "gy.test.localhost", "localhost", "swift.wispgate.io", "wispgate.io")
    client.start()

    # Sending the CER message
    cea_avps = client.send_cer()
    print('\nCEA response:')
    print(cea_avps)
    print('\n')

    sleep(2)
    # Sending the  message
    dwa_avps = send_req(client)
    print('\nCEA response:')
    print(dwa_avps)
    print('\n')
    #sleep(2)

    # server = DiameterServer("127.0.0.1", 3869)
    # server.start()

    # while True:
    #     # Sending the  message
    #     dwa_avps = client.send_dwr()
    #     print('\nCEA response:')
    #     print(dwa_avps)
    #     print('\n')
    #     sleep(3)

    # Sending the invalid message
    # invalid_msg_avps = client.send_invalid_message()
    # print('\nInvalid message response:')
    # print(invalid_msg_avps)

