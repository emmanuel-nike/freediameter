#!/usr/bin/env python

"""
Sample Diameter Client, which can be used for testing purposes.
Generates a client instance, starts it, establishing the server connection
and then sends the specified Diameter Requests and interprets the response.
"""

from time import sleep
from diameter_client import *
from diameter_server import *
from diameter_responses import *

def send_req(client):
    # Generating a standard Diameter request
    # Creating the Diameter Message object to base the request on
    diameter_request = diameter_base.DiameterMessage()
    diameter_request.command_code = diameter_base.cmd_codes['Credit-Control']
    #diameter_request.application_Id = 4
    diameter_request.avps['Origin-Host'] = "swift.wispgate.io"
    diameter_request.avps['Origin-Realm'] = "wispgate.io"
    # diameter_request.avps['Destination-Host'] = self.destination_host
    # diameter_request.avps['Destination-Realm'] = self.destination_realm

    # Generating a standard Diameter request
    generic_request = generate_generic_diameter_message(
        diameter_request, "swift.wispgate.io", "wispgate.io")
    
    

    cer_header = generic_request['header']
    cer_avps = generic_request['avps']

    # Appending the CER specific AVPs
    # cer_avps.append(encodeAVP('Host-IP-Address', '10.65.6.249'))
    
    cer_avps.append(encodeAVP('Product-Name', diameter_base.standard_avp_values['Product-Name']))
    cer_avps.append(encodeAVP('Vendor-Id', diameter_base.standard_avp_values['Vendor-Id']))
    cer_avps.append(encodeAVP('Auth-Application-Id', DIAMETER_APPLICATION_CREDIT_CONTROL))
    cer_avps.append(encodeAVP('Service-Context-Id', '32252@3gpp.org'))
    cer_avps.append(encodeAVP('CC-Request-Type', DI_CC_REQUEST_TYPE_TERMINATION_REQUEST)) #Initial Request
    cer_avps.append(encodeAVP('CC-Request-Number', 4)) #Initial Request
    cer_avps.append(encodeAVP('Subscription-Id', [
        encodeAVP('Subscription-Id-Type', DI_SUBSCRIPTION_ID_TYPE_END_USER_E164),
        encodeAVP('Subscription-Id-Data', '2342601212997')
    ]))
    cer_avps.append(encodeAVP('Subscription-Id', [
        encodeAVP('Subscription-Id-Type', DI_SUBSCRIPTION_ID_TYPE_END_USER_IMSI),
        encodeAVP('Subscription-Id-Data', '45677892342601212997')
    ]))
    cer_avps.append(encodeAVP('Multiple-Services-Indicator', DI_MULTIPLE_SERVICES_INDICATOR_MULTIPLE_SERVICES_SUPPORTED))
    cer_avps.append(encodeAVP('Multiple-Services-Credit-Control', [
        encodeAVP('Used-Service-Unit', [
            encodeAVP('CC-Time', 200),
            encodeAVP('CC-Total-Octets', 4096),
            encodeAVP('CC-Input-Octets', 2048),
            encodeAVP('CC-Output-Octets', 2048),
        ]),
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
    client = DiameterClient('10.65.6.251', 3868, "gy.swift.wg.io", "wg.io", "swift.wispgate.io", "wispgate.io")
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

