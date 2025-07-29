from .KnType import KnType
from .KnGenerator import KnGetAttribute


class _KnMember:
	def __init__(self, memberdef: dict):
		self.const: bool = True if memberdef.get('@const', '') == 'yes' else False
		self.explicit: bool = True if memberdef.get('@explicit', '') == 'yes' else False
		self.id: str = memberdef.get('@id', '')
		self.inline: bool = True if memberdef.get('@inline', '') == 'yes' else False
		self.kind: str = memberdef.get('@kind', '')
		self.prot: str = memberdef.get('@prot', '')
		self.static: bool = True if memberdef.get('@static', '') == 'yes' else False
		self.virt: str = memberdef.get('@virt', '')
		self.argsstring: str = memberdef.get('argsstring', '')
		self.description: str = memberdef.get('description', '')
		self.name: str = memberdef.get('name', '')
		self.param: list[dict] = KnGetAttribute(memberdef, 'param') or []
		self.qualifiedname: str = memberdef.get('qualifiedname', '')
		self.type = KnType(memberdef.get('type', ''))

		self.strong: bool = True if memberdef.get('@strong', '') == 'yes' else False
		self.briefdescription: str = memberdef.get('briefdescription', '')
		self.detaileddescription: str = memberdef.get('detaileddescription', '')
		self.enumvalue: list[dict] = KnGetAttribute(memberdef, 'enumvalue') or []
		self.inbodydescripton: str = memberdef.get('inbodydescription', '')
		self.location: dict = memberdef.get('location', '')

		# print(f'{self.name}')
