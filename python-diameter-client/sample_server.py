"""
Sample Diameter Server, which can be used for testing purposes.
Generates a Diameter Server with the default(local) config,
and then starts the server, making it available
for incoming connections and requests handling.
"""

from diameter_server import *

if __name__ == "__main__":
    """
    Main method for the Sample Diameter Server.

    Instantiates a Diameter Server, and then starts it.
    """

    # Generating a Diameter server and starting it
    server = DiameterServer("10.65.6.251", 3869, 4096, 5, "gy.test.localhost", "localhost")
    server.start()
