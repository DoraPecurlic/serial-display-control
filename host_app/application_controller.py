from command import CommandType
from command_parser import CommandParser
from display_client import DisplayClient


class ApplicationController:
    def __init__(self,command_parser:CommandParser, display_client:DisplayClient)->None:
        self._command_parser = command_parser
        self._display_client = display_client

    def handle_input(self, user_input: str) -> None:
        command = self._command_parser.parse(user_input)

        if command.command_type == CommandType.SHOW_TEXT:
            if command.text is None:
                raise ValueError("Text is missing.")
            
            self._display_client.show_text(command.text)
            return
        
        if command.command_type == CommandType.CLEAR:
            self._display_client.clear()
            return
        
        if command.command_type == CommandType.SCROLL_LEFT:
            self._display_client.scroll_left()
            return
        
        if command.command_type == CommandType.SCROLL_RIGHT:
            self._display_client.scroll_right()
            return
        
        raise ValueError("Unsupported command.")