from dataclasses import dataclass
from enum import Enum, auto
from typing import Optional

class CommandType(Enum):
    SHOW_TEXT = auto()
    CLEAR = auto()
    SCROLL_LEFT = auto()
    SCROLL_RIGHT = auto()

@dataclass
class ParsedCommand:
    command_type: CommandType
    text: Optional[str] = None