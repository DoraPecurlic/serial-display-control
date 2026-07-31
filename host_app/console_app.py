from application_controller import ApplicationController
from serial_protocol import ProtocolError

class ConsoleApp:
    EXIT_COMMAND = "exit"

    def __init__(self, app_controller: ApplicationController) -> None:
        self._app_controller = app_controller

    def run(self) -> None:
        print(
            f"Enter text, a command starting with ':', "
            f"or '{self.EXIT_COMMAND}' to quit."
        )

        while True:
            user_input = input("> ")

            if self._is_exit_command(user_input):
                print("Closing application.")
                break

            try:
                self._app_controller.handle_input(user_input)

            except ValueError as error:
                print(f"Invalid input: {error}")

            except ProtocolError as error:
                print(f"Device error: {error}")

            except TimeoutError as error:
                print(f"Communication timeout: {error}")

            

    def _is_exit_command(self, text: str) -> bool:
        return text.strip().lower() == self.EXIT_COMMAND

    

            