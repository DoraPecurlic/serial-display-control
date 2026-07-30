from serial_connection import SerialConnection

class ProtocolError(Exception):
    pass

class SerialProtocol:
    SUCCES_RESPONSE = "OK"
    TEXT_REQUEST_PREFIX = "TEXT:"
    ERROR_RESPONSE_PREFIX = "ERROR:"

    def __init__(self, connection: SerialConnection) -> None:
        self._connection = connection

    def send_text(self, text: str) -> None:
        request = self.TEXT_REQUEST_PREFIX + text
        self.send_request(request)

    def send_request(self, request: str) -> None:
        self._connection.send_line(request)
        response = self._connection.read_line()
        self._validate_response(response)   

    def _validate_response(self, response: str) -> None:
        if response != self.SUCCES_RESPONSE:
            raise ProtocolError(f"Unexpected response from STM32: {response}") 
        if response == self.SUCCES_RESPONSE:
            print("stm32 send OK!")
        if response.startswith(self.ERROR_RESPONSE_PREFIX):
            error_message = response[len(self.ERROR_RESPONSE_PREFIX):]

            raise ProtocolError(
                f"STM32 rejected the request: {error_message}"
            )