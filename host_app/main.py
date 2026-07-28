from serial_connection import SerialConnection
from display_client import DisplayClient
from console_app import ConsoleApp
import time 

SERIAL_PORT = "COM7"

def main() -> None:
    connection = SerialConnection(port = SERIAL_PORT)
    display_client = DisplayClient(connection)
    console_app = ConsoleApp(display_client)

    try:
        connection.connect()
        time.sleep(2)
        print(f"Connected to port {SERIAL_PORT} at baudrate 115200.")

        console_app.run()

    except (ConnectionError, ValueError) as error:
        print(error)
    except KeyboardInterrupt:
        print("\n Application stopped by User.")
    finally:
        if connection.is_connected:
            connection.disconnect()
            print("Serial connection closed.")

if __name__ == "__main__":
    main()