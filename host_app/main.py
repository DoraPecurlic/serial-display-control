from serial_connection import SerialConnection
from display_client import DisplayClient
from console_app import ConsoleApp
from serial_protocol import SerialProtocol, ProtocolError


import time 

SERIAL_PORT = "COM7"

def main() -> None:
    connection = SerialConnection(port = SERIAL_PORT)
    protocol = SerialProtocol(connection)
    display_client = DisplayClient(protocol)
    console_app = ConsoleApp(display_client)

    try:
        connection.connect()
        time.sleep(2)
        print(f"Connected to port {SERIAL_PORT} at baudrate 115200.")

        console_app.run()

    except (ConnectionError, ValueError, ProtocolError) as error:
        print(f"Communication error: {error}")
    except KeyboardInterrupt:
        print("\n Application stopped by User.")
    finally:
        if connection.is_connected:
            connection.disconnect()
            print("Serial connection closed.")

if __name__ == "__main__":
    main()