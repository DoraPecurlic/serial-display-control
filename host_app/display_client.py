from serial_protocol import SerialProtocol

class DisplayClient:

    MAX_TEXT_LENGTH = 15

    def __init__(self, protocol: SerialProtocol) -> None: #kompozicija, has-a veza jer objekt display clienta ima objekt serial connectiona
        self._protocol = protocol

    def show_text(self, text: str) -> None:
        self._validate_text(text)
        self._protocol.send_text(text)

    def _validate_text(self, text: str) -> None:
        if len(text) > self.MAX_TEXT_LENGTH:
            raise ValueError(f"Text can contain maximum {self.MAX_TEXT_LENGTH} characters.")
        if not all(32 <= ord(characters) <= 126 for characters in text):
            raise ValueError("Only ASCII characters are  supported")