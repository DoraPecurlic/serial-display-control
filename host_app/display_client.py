from serial_protocol import SerialProtocol

class DisplayClient:

    MAX_TEXT_LENGTH = 15

    CLEAR_COMMAND = "CLEAR"
    SCROLL_LEFT_COMMAND = "SCROLL_LEFT"
    SCROLL_RIGHT_COMMAND = "SCROLL_RIGHT"
    STOP_COMMAND = "STOP"
    BLINK_COMMAND = "BLINK"

    def __init__(self, protocol: SerialProtocol) -> None: #kompozicija, has-a veza jer objekt display clienta ima objekt serial connectiona
        self._protocol = protocol

    def show_text(self, text: str) -> None:
        self._validate_text(text)
        self._protocol.send_text(text)

    def clear(self) -> None:
        self._protocol.send_command(self.CLEAR_COMMAND)

    def scroll_left(self) -> None:
        self._protocol.send_command(self.SCROLL_LEFT_COMMAND)

    def scroll_right(self) -> None:
        self._protocol.send_command(self.SCROLL_RIGHT_COMMAND)

    def stop(self) -> None:
        self._protocol.send_command(self.STOP_COMMAND)

    def blink(self) -> None:
            self._protocol.send_command(self.BLINK_COMMAND)
    
    def _validate_text(self, text: str) -> None:
        if len(text) > self.MAX_TEXT_LENGTH:
            raise ValueError(f"Text can contain maximum {self.MAX_TEXT_LENGTH} characters.")
        if not all(32 <= ord(characters) <= 126 for characters in text):
            raise ValueError("Only ASCII characters are  supported")