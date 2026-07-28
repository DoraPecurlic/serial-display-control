from display_client import DisplayClient

class ConsoleApp:
    EXIT_COMMAND = "exit"

    def __init__(self, display: DisplayClient) -> None:
        self._display = display

    def run(self) -> None:

        while True:
            text = input("Enter text or type 'exit' to quit: ")

            if self._is_exit_command(text):
                print("Closing application.")
                break

            self._send_text(text)
            

    def _is_exit_command(self, text: str) -> bool:
        return text.strip().lower() == self.EXIT_COMMAND

    def _send_text(self, text:str) -> None:
        try:
            self._display.show_text(text)
            print("Text sent to display.")
        except ValueError as error:
            print(f"Invalid text: {error}")

            