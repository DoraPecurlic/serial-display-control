from serial_connection import SerialConnection
import time 

SERIAL_PORT = "COM7"

def main() -> None:
    connection = SerialConnection(port = SERIAL_PORT)

    try:
        connection.connect()
        time.sleep(2)
        print(f"Connected to port {SERIAL_PORT} at baudrate 115200.")

        connection.send_line("HelloFromDora123456789")
        print("Message sent successfully")

    except ConnectionError as error:
        print(error)
    finally:
        if connection.is_connected:
            connection.disconnect()
            print("Serial connection closed.")

if __name__ == "__main__":
    main()