from application_controller import ApplicationController

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

            self._app_controller.handle_input(user_input)
            

    def _is_exit_command(self, text: str) -> bool:
        return text.strip().lower() == self.EXIT_COMMAND

    def _send_text(self, text:str) -> None:
        try:
            self._display.show_text(text)
            print("Text sent to display.")
        except ValueError as error:
            print(f"Invalid text: {error}")

            