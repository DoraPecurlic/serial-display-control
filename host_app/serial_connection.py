import serial
import time

class SerialConnection:
    def __init__(self, port: str, baud_rate: int = 115200, timeout: float = 1.0) -> None: #konstrukzot
        self._port = port
        self._baud_rate = baud_rate
        self._timeout = timeout
        self._serial: serial.Serial | None = None

    @property
    def is_connected(self) -> bool:
        return self._serial is not None and self._serial.is_open


    def connect(self) -> None:
        if self.is_connected:
            return

        try:
            self._serial = serial.Serial(
                port = self._port,
                baudrate =self._baud_rate,
                parity = serial.PARITY_NONE,
                stopbits = serial.STOPBITS_ONE,
                bytesize = serial.EIGHTBITS,
                timeout = self._timeout
            ) #8n1 format
            
        except serial.SerialException as error:
            self._serial = None

            raise ConnectionError(f"Could not connect to serial port: {self._port}.") from error

    
    def disconnect(self) -> None:
        if self._serial is None:
            return

        self._serial.close()
        self._serial = None

    def send_line(self, message: str) -> None:
        if self.is_connected == False:
            raise ConnectionError("Serial Connection is not opened.")
        
        message_to_display = message + "\r"
        message_to_display_encoded = message_to_display.encode("ascii") # stm ocekuje bajtove a ne string pa mu se pretvori sve u bajtove, utf-8 podrzava i palatale

        for byte in message_to_display_encoded:
            self._serial.write(bytes([byte]))
            self._serial.flush()
            time.sleep(0.01)

        