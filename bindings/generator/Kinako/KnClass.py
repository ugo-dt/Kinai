import json
from pathlib import Path

from ._KnMember import _KnMember
from .KnFunction import KnFunction
from .KnGenerator import KnGetAttribute


class KnClass:
	"""
	Class representation.
	"""
	def __init__(self, compound: dict):
		self.__kind: str = compound.get('@kind')
		self.__refid: str = compound.get('@refid')
		self.__members: list[dict] = KnGetAttribute(compound, 'member')
		self.name: str = compound.get('name')

		self.functions: list[KnFunction] = []
		self.variables: list[_KnMember] = []

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
				if section_kind == 'public-func' or section_kind == 'public-static-func':
					memberdef: list[dict] = KnGetAttribute(section, 'memberdef')
					for member in memberdef:
						self.functions.append(KnFunction(member))

	def __c__(self) -> str:
		prefix = f'{self.name.replace('Kinai::', 'Kn')}_'
		c: list[str] = []
		for func in self.functions:
			c.append(f'{func.__c__(prefix=prefix)}')
		return '\n'.join(c)
