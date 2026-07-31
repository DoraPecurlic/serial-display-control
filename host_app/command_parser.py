from command import CommandType, ParsedCommand

class CommandParser:
    COMMAND_PREFIX = ":"
    CLEAR_COMMAND = "clear"
    COMMANDS = {
        "clear": CommandType.CLEAR,
        "scroll left": CommandType.SCROLL_LEFT,
        "scroll right": CommandType.SCROLL_RIGHT,
        "stop": CommandType.STOP,
    }

    def parse(self, user_input: str) -> ParsedCommand:
        if not user_input.strip():
            raise ValueError("Input cannot be empty")

        if not user_input.startswith(self.COMMAND_PREFIX):
            return ParsedCommand(command_type = CommandType.SHOW_TEXT, text = user_input)

        command_name = user_input[1:].strip().lower()

        if not command_name:
            raise ValueError("Command cannot be empty")

        cmd_type = self.COMMANDS.get(command_name)

        if cmd_type is None:
            raise ValueError(f"Unknown command: {command_name}")

        return ParsedCommand(command_type=cmd_type) 