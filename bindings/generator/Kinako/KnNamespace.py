import json
from pathlib import Path

from .KnGenerator import KnGetAttribute
from ._KnMember import _KnMember
from .KnType import KINAI_TYPES

class KnEnum(_KnMember):
	"""
	Enum representation.
	"""
	def __init__(self, member: dict):
		super().__init__(member)
		KINAI_TYPES.add(self.name)

		# print(self.__c__())

	def __c__(self) -> str:
		return f'typedef enum Kn{self.name}\n{{\n}} Kn{self.name};'

class KnTypedef(_KnMember):
	"""
	Typedef representation.
	"""
	def __init__(self, member: dict):
		super().__init__(member)
		KINAI_TYPES.add(self.name)

		print(self.__c__())

	def __c__(self) -> str:
		return f'typedef {self.type.__c__()} Kn{self.name};'

class KnNamespace:
	"""
	Namespace representation.
	"""
	def __init__(self, compound: dict):
		self.__kind = compound.get('@kind')
		self.__refid = compound.get('@refid')
		self.__members: list[dict] = KnGetAttribute(compound, 'member')
		self.name = compound.get('name')

		self.enums: list[KnEnum] = []
		self.typedefs: list[KnTypedef] = []

		ref_path = Path(f'output/json/{self.__refid}.json')
		with open(ref_path) as file:
			json_data = json.load(file)
			compounddef: dict = json_data['doxygen']['compounddef']
			if compounddef is None:
				return 
			sectiondef: list[dict] = KnGetAttribute(compounddef, 'sectiondef')
			if sectiondef is None:
				return 
			
			for section in sectiondef:
				section_kind = section.get('@kind')
				memberdef: list[dict] = KnGetAttribute(section, 'memberdef')
				if section_kind == 'enum':
					for member in memberdef:
						self.enums.append(KnEnum(member))
				elif section_kind == 'typedef':
					for member in memberdef:
						self.enums.append(KnTypedef(member))

	def __c__(self) -> str:
		c: list[str] = []
		for enum in self.enums:
			if enum.name is not None:
				c.append(f'{enum.__c__()}')
		return '\n'.join(c)
