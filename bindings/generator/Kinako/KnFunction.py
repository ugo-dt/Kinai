from ._KnMember import _KnMember
from .KnType import KnType


class KnParameter:
	def __init__(self, param: dict):
		self.declname: str = param.get('declname', '')
		self.type: KnType = KnType(param.get('type', ''))

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

		return f'{self.type.__c__()} {prefix}{name}{suffix}({", ".join(args)});'

	def __cpp__(self, prefix: str = '', suffix: str = '', namespace: str = ''):
		destructor: bool = '~' in self.name

		name = self.name.replace('::', '_').replace('~', 'Destroy').replace('operator==', 'equals')
		args = [arg.__c__() for arg in self.args]
		passed_args = [arg.split(' ')[-1] for arg in args]

		for i in range(len(passed_args)):
			if self.args[i].type.compound:
				if '&' in self.args[i].type.text: # type: ignore
					passed_args[i] = '*' + passed_args[i]
			else:
				if '&' in self.args[i].type.type: # type: ignore
					passed_args[i] = '*' + passed_args[i]
		
		args.insert(0, f'{prefix.removesuffix('_')} *self')

		kn_class_name = prefix.removesuffix('_')
		class_name = kn_class_name.removeprefix('Kn')
		if name == class_name:
			return f'{kn_class_name}* {prefix}{name}{suffix}({", ".join(args)})\n{{\n    return new {namespace}({", ".join(passed_args)});\n}}\n'
		if destructor:
			passed_args.insert(0, 'self')
			return f'void {prefix}{name}{suffix}({", ".join(args)})\n{{\n    delete ({", ".join(passed_args)});\n}}\n'
		
		return f'{self.type.__c__()} {prefix}{name}{suffix}({", ".join(args)})\n{{\n    return (({namespace}*)self)->{name}({", ".join(passed_args)});\n}}\n'