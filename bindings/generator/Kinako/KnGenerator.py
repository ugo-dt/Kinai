from io import TextIOWrapper
from pathlib import Path


def KnGetAttribute(d: dict, key: str) -> list[dict] | None:
	value = d.get(key)
	return [value] if isinstance(value, dict) else value

class KnGenerator:
	def __init__(self, json_dir: Path, output_file: TextIOWrapper):
		self.json_dir = json_dir

		self.__output_file = output_file

	def write_from_file(self, file_path: Path):
		with open(file_path) as file:
			self.__output_file.write(file.read())

	def writeline(self, text: str):
		self.__output_file.write(f'{text}\n')
