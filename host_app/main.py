from serial_connection import SerialConnection

SERIAL_PORT = "COM7"

def main() -> None:
    connection = SerialConnection(port = SERIAL_PORT)

    try:
        connection.connect()
        print(f"Connected to port {SERIAL_PORT} at baudrate 115200.")
    except ConnectionError as error:
        print(error)
    finally:
        if connection.is_connected:
            connection.disconnect()
            print("Serial connection closed.")

if __name__ == "__main__":
    main()