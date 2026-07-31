from command import CommandType, ParsedCommand

class ComandParser:
    COMMAND_PREFIX = ":"
    CLEAR_COMMAND = "clear"

    def parse(self, user_input: str) -> ParsedCommand:
        if not user_input.strip():
            raise ValueError("Input cannot be empty")

        if not user_input.startswith(self.COMMAND_PREFIX):
            return ParsedCommand(command_type = CommandType.SHOW_TEXT, text = user_input)

        command_name = user_input[1:].strip().lower()

        if not command_name:
            raise ValueError("Command cannot be empty")
        if command_name == self.CLEAR_COMMAND:
            return ParsedCommand(command_type = CommandType.CLEAR)

        raise ValueError(f"Unknown command: {command_name}")