from ._KnMember import _KnMember
from .KnType import KnType


class KnParameter:
	def __init__(self, param: dict):
		self.declname: str = param.get('declname')
		self.type: KnType = KnType(param.get('type'))

	def __c__(self):
		return f'{self.type.__c__()} {self.declname}'
		
class KnFunction(_KnMember):
	def __init__(self, memberdef: dict):
		super().__init__(memberdef)
		
		self.args: list[KnParameter] = []
		if self.param is not None:
			for p in self.param:
				self.args.append(KnParameter(p))
			

	def __c__(self, prefix: str = '', suffix: str = '') -> str:
		name = self.name.replace('::', '_').replace('~', 'Destroy').replace('operator==', 'equals')
		args = [arg.__c__() for arg in self.args]

		print(prefix)

		return f'{self.type.__c__()} {prefix}{name}{suffix}({", ".join(args)});'
